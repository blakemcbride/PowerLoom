//  -*- Mode: C++ -*-

// read.cc

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

TokenizerTable* newTokenizerTable() {
  { TokenizerTable* self = NULL;

    self = new TokenizerTable();
    self->legalEofStates = NULL;
    self->stateNames = NULL;
    self->uniqueStateNames = NULL;
    self->transitions = NULL;
    return (self);
  }
}

Surrogate* TokenizerTable::primaryType() {
  { TokenizerTable* self = this;

    return (SGT_READ_STELLA_TOKENIZER_TABLE);
  }
}

Object* accessTokenizerTableSlotValue(TokenizerTable* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_READ_STELLA_TRANSITIONS) {
    if (setvalueP) {
      self->transitions = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->transitions);
    }
  }
  else if (slotname == SYM_READ_STELLA_UNIQUE_STATE_NAMES) {
    if (setvalueP) {
      self->uniqueStateNames = ((Vector*)(value));
    }
    else {
      value = self->uniqueStateNames;
    }
  }
  else if (slotname == SYM_READ_STELLA_STATE_NAMES) {
    if (setvalueP) {
      self->stateNames = ((Vector*)(value));
    }
    else {
      value = self->stateNames;
    }
  }
  else if (slotname == SYM_READ_STELLA_LEGAL_EOF_STATES) {
    if (setvalueP) {
      self->legalEofStates = ((Vector*)(value));
    }
    else {
      value = self->legalEofStates;
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

int oMAX_TOKENIZER_STATESo = 64;

int oMAX_TOKENIZER_CHARACTERSo = 256;

TokenizerTable* parseTokenizerDefinition(Cons* definition) {
  { Vector* transitiontable = stella::newVector(oMAX_TOKENIZER_STATESo);
    char* transitions = native_make_mutable_string(oMAX_TOKENIZER_CHARACTERSo, NULL_CHARACTER);
    Vector* uniquestatenames = stella::newVector(oMAX_TOKENIZER_STATESo);
    Vector* statenames = stella::newVector(oMAX_TOKENIZER_STATESo);
    Vector* legaleofstates = stella::newVector(oMAX_TOKENIZER_STATESo);
    GeneralizedSymbol* fromstatename = NULL;
    int fromstateid = NULL_INTEGER;
    GeneralizedSymbol* tostatename = NULL;
    GeneralizedSymbol* tostatealias = NULL;
    int tostateid = NULL_INTEGER;
    int freestateid = 2;
    Object* characterspec = NULL;
    Cons* characterset = NULL;
    List* allcharactersets = newList();
    int statemodifiers = 0;
    boolean errorsP = false;
    TokenizerTable* table = newTokenizerTable();

    (uniquestatenames->theArray)[0] = KWD_READ_ERROR;
    (statenames->theArray)[0] = KWD_READ_ERROR;
    (uniquestatenames->theArray)[1] = KWD_READ_START;
    (statenames->theArray)[1] = KWD_READ_START;
    { Cons* statedefinition = NULL;
      Cons* iter000 = definition;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        statedefinition = ((Cons*)(iter000->value));
        if (!(legalTokenizerFromStateP(statedefinition->value))) {
          *(STANDARD_WARNING->nativeStream) << "Warning: " << "Illegal from state: " << "`" << statedefinition->value << "'" << std::endl;
          errorsP = true;
          continue;
        }
        fromstatename = ((GeneralizedSymbol*)(statedefinition->value));
        statedefinition = statedefinition->rest;
        fromstateid = uniquestatenames->position(fromstatename, 0);
        if (fromstateid == NULL_INTEGER) {
          if (freestateid == oMAX_TOKENIZER_STATESo) {
            *(STANDARD_WARNING->nativeStream) << "Warning: " << "Too many tokenizer states; maximum is " << "`" << oMAX_TOKENIZER_STATESo << "'" << std::endl;
            errorsP = true;
            break;
          }
          (uniquestatenames->theArray)[freestateid] = fromstatename;
          (statenames->theArray)[freestateid] = fromstatename;
          fromstateid = freestateid;
          freestateid = freestateid + 1;
        }
        allcharactersets->clear();
        { int i = NULL_INTEGER;
          int iter001 = 0;
          int upperBound000 = oMAX_TOKENIZER_CHARACTERSo - 1;

          for  (; iter001 <= upperBound000; 
                iter001 = iter001 + 1) {
            i = iter001;
            transitions[i] = ((char) 0);
          }
        }
        while (!(statedefinition == NIL)) {
          if (tokenizerIncludeSpecP(statedefinition->value)) {
            if (!(legalTokenizerFromStateP(statedefinition->rest->value))) {
              *(STANDARD_WARNING->nativeStream) << "Warning: " << "Illegal include specification for state " << "`" << fromstatename << "'" << std::endl;
              errorsP = true;
              break;
            }
            statedefinition = copyConsList(statedefinition);
            { Cons* statedef = NULL;
              Cons* iter002 = definition;

              for (; !(iter002 == NIL); iter002 = iter002->rest) {
                statedef = ((Cons*)(iter002->value));
                if (eqlP(statedef->value, statedefinition->rest->value)) {
                  statedefinition->firstSetter(statedef->rest->value);
                  statedefinition->rest = copyConsList(statedef->rest->rest)->concatenate(statedefinition->rest->rest, 0);
                  break;
                }
              }
            }
            continue;
          }
          statemodifiers = parseTokenizerStateModifiers(statedefinition->value);
          if (statemodifiers > 0) {
            statedefinition = statedefinition->rest;
          }
          characterspec = statedefinition->value;
          statedefinition = statedefinition->rest;
          if (!(((boolean)(characterspec)))) {
            *(STANDARD_WARNING->nativeStream) << "Warning: " << "Illegal definition of " << "`" << fromstatename << "'" << " state" << std::endl;
            errorsP = true;
            break;
          }
          if (!(legalTokenizerToStateP(statedefinition->value))) {
            *(STANDARD_WARNING->nativeStream) << "Warning: " << "Illegal to state " << "`" << statedefinition->value << "'" << " for state " << "`" << fromstatename << "'" << std::endl;
            errorsP = true;
            break;
          }
          if (characterspec == KWD_READ_EOF) {
            (legaleofstates->theArray)[fromstateid] = TRUE_WRAPPER;
            statedefinition = statedefinition->rest;
            continue;
          }
          tostatename = tokenizerToStateName(statedefinition->value);
          tostatealias = tokenizerToStateAlias(statedefinition->value);
          statedefinition = statedefinition->rest;
          tostateid = uniquestatenames->position(tostatename, 0);
          if (tostateid == NULL_INTEGER) {
            if (freestateid == oMAX_TOKENIZER_STATESo) {
              *(STANDARD_WARNING->nativeStream) << "Warning: " << "Too many tokenizer states; maximum is " << "`" << oMAX_TOKENIZER_STATESo << "'" << std::endl;
              errorsP = true;
              break;
            }
            (uniquestatenames->theArray)[freestateid] = tostatename;
            (statenames->theArray)[freestateid] = tostatealias;
            tostateid = freestateid;
            freestateid = freestateid + 1;
          }
          if ((!(((GeneralizedSymbol*)((statenames->theArray)[tostateid])) == tostatealias)) &&
              ((boolean)(((GeneralizedSymbol*)((statenames->theArray)[tostateid]))))) {
            *(STANDARD_WARNING->nativeStream) << "Warning: " << "Illegal redefinition of alias " << "`" << tostatealias << "'" << " for state " << "`" << tostatename << "'" << " in state " << "`" << fromstatename << "'" << std::endl;
            errorsP = true;
          }
          characterset = parseTokenizerCharacterSpec(characterspec, allcharactersets);
          if (!((boolean)(characterset))) {
            *(STANDARD_WARNING->nativeStream) << "Warning: " << "Illegal character specification " << "`" << characterspec << "'" << " for state " << "`" << fromstatename << "'" << std::endl;
            errorsP = true;
            continue;
          }
          allcharactersets->push(characterset);
          { CharacterWrapper* chaR = NULL;
            Cons* iter003 = characterset;

            for (; !(iter003 == NIL); iter003 = iter003->rest) {
              chaR = ((CharacterWrapper*)(iter003->value));
              transitions[((int)(unsigned char) (chaR->wrapperValue))] = ((char) ((((statemodifiers << 6)) | tostateid)));
            }
          }
        }
        (transitiontable->theArray)[fromstateid] = (wrapMutableString(transitions));
        transitions = native_make_mutable_string(oMAX_TOKENIZER_CHARACTERSo, NULL_CHARACTER);
      }
    }
    { int i = NULL_INTEGER;
      int iter004 = 0;
      int upperBound001 = freestateid - 1;

      for  (; iter004 <= upperBound001; 
            iter004 = iter004 + 1) {
        i = iter004;
        if (!((boolean)(((MutableStringWrapper*)((transitiontable->theArray)[i]))))) {
          *(STANDARD_WARNING->nativeStream) << "Warning: " << "State " << "`" << ((GeneralizedSymbol*)((uniquestatenames->theArray)[i])) << "'" << " is undefined" << std::endl;
          errorsP = true;
        }
      }
    }
    if (errorsP) {
      return (NULL);
    }
    transitions = native_make_mutable_string((freestateid * oMAX_TOKENIZER_CHARACTERSo), NULL_CHARACTER);
    { int i = NULL_INTEGER;
      int iter005 = 0;
      int upperBound002 = freestateid - 1;

      for  (; iter005 <= upperBound002; 
            iter005 = iter005 + 1) {
        i = iter005;
        { int j = NULL_INTEGER;
          int iter006 = 0;
          int upperBound003 = oMAX_TOKENIZER_CHARACTERSo - 1;
          int k = NULL_INTEGER;
          int iter007 = oMAX_TOKENIZER_CHARACTERSo * i;

          for  (; iter006 <= upperBound003; 
                iter006 = iter006 + 1,
                iter007 = iter007 + 1) {
            j = iter006;
            k = iter007;
            transitions[k] = ((((MutableStringWrapper*)((transitiontable->theArray)[i]))->wrapperValue)[j]);
          }
        }
      }
    }
    table->transitions = transitions;
    table->uniqueStateNames = stella::newVector(freestateid);
    table->stateNames = stella::newVector(freestateid);
    { int i = NULL_INTEGER;
      int iter008 = 0;
      int upperBound004 = freestateid - 1;

      for  (; iter008 <= upperBound004; 
            iter008 = iter008 + 1) {
        i = iter008;
        (table->uniqueStateNames->theArray)[i] = (((GeneralizedSymbol*)((uniquestatenames->theArray)[i])));
        (table->stateNames->theArray)[i] = (((GeneralizedSymbol*)((statenames->theArray)[i])));
      }
    }
    table->legalEofStates = stella::newVector(freestateid);
    { int i = NULL_INTEGER;
      int iter009 = 0;
      int upperBound005 = freestateid - 1;

      for  (; iter009 <= upperBound005; 
            iter009 = iter009 + 1) {
        i = iter009;
        (table->legalEofStates->theArray)[i] = (((!((boolean)(((BooleanWrapper*)((legaleofstates->theArray)[i]))))) ? FALSE_WRAPPER : ((BooleanWrapper*)((legaleofstates->theArray)[i]))));
      }
    }
    return (table);
  }
}

boolean legalTokenizerStateP(Object* x) {
  return (keywordP(x) ||
      symbolP(x));
}

boolean legalTokenizerFromStateP(Object* x) {
  return (legalTokenizerStateP(x));
}

boolean legalTokenizerToStateP(Object* x) {
  return (legalTokenizerStateP(x) ||
      (consP(x) &&
       (legalTokenizerStateP(((Cons*)(x))->value) &&
        legalTokenizerStateP(((Cons*)(x))->rest->value))));
}

GeneralizedSymbol* tokenizerToStateName(Object* state) {
  if (consP(state)) {
    return (((GeneralizedSymbol*)(((Cons*)(state))->value)));
  }
  else {
    return (((GeneralizedSymbol*)(state)));
  }
}

GeneralizedSymbol* tokenizerToStateAlias(Object* state) {
  if (consP(state)) {
    return (((GeneralizedSymbol*)(((Cons*)(state))->rest->value)));
  }
  else {
    return (((GeneralizedSymbol*)(state)));
  }
}

int parseTokenizerStateModifiers(Object* modifier) {
  if (subtypeOfP(safePrimaryType(modifier), SGT_READ_STELLA_GENERALIZED_SYMBOL)) {
    { Object* modifier000 = modifier;
      GeneralizedSymbol* modifier = ((GeneralizedSymbol*)(modifier000));

      { const char* testValue000 = modifier->symbolName;

        if (stringEqlP(testValue000, "*")) {
          return (2);
        }
        else if (stringEqlP(testValue000, "!") ||
            (stringEqlP(testValue000, "*!") ||
             stringEqlP(testValue000, "!*"))) {
          return (3);
        }
        else {
          return (0);
        }
      }
    }
  }
  else {
    return (0);
  }
}

boolean tokenizerIncludeSpecP(Object* x) {
  return (isaP(x, SGT_READ_STELLA_GENERALIZED_SYMBOL) &&
      stringEqlP(((GeneralizedSymbol*)(x))->symbolName, "INCLUDE"));
}

Cons* parseTokenizerCharacterSpec(Object* characterspec, List* allcharactersets) {
  { Cons* charset = NIL;
    Cons* complementset = NIL;
    Cons* parsedspec = NULL;

    { Surrogate* testValue000 = safePrimaryType(characterspec);

      if (subtypeOfStringP(testValue000)) {
        { Object* characterspec000 = characterspec;
          StringWrapper* characterspec = ((StringWrapper*)(characterspec000));

          { char chaR = NULL_CHARACTER;
            const char* vector000 = characterspec->wrapperValue;
            int index000 = 0;
            int length000 = strlen(vector000);
            Cons* collect000 = NULL;

            for  (; index000 < length000; 
                  index000 = index000 + 1) {
              chaR = vector000[index000];
              if (!((boolean)(collect000))) {
                {
                  collect000 = cons(wrapCharacter(chaR), NIL);
                  if (charset == NIL) {
                    charset = collect000;
                  }
                  else {
                    addConsToEndOfConsList(charset, collect000);
                  }
                }
              }
              else {
                {
                  collect000->rest = cons(wrapCharacter(chaR), NIL);
                  collect000 = collect000->rest;
                }
              }
            }
          }
        }
      }
      else if (subtypeOfCharacterP(testValue000)) {
        { Object* characterspec001 = characterspec;
          CharacterWrapper* characterspec = ((CharacterWrapper*)(characterspec001));

          charset = cons(characterspec, charset);
        }
      }
      else if (testValue000 == SGT_READ_STELLA_CONS) {
        { Object* characterspec002 = characterspec;
          Cons* characterspec = ((Cons*)(characterspec002));

          { Object* spec = NULL;
            Cons* iter000 = characterspec;

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              spec = iter000->value;
              parsedspec = parseTokenizerCharacterSpec(spec, NIL_LIST);
              if (!((boolean)(parsedspec))) {
                return (NULL);
              }
              { CharacterWrapper* chaR = NULL;
                Cons* iter001 = parsedspec;
                Cons* collect001 = NULL;

                for  (; !(iter001 == NIL); 
                      iter001 = iter001->rest) {
                  chaR = ((CharacterWrapper*)(iter001->value));
                  if (!((boolean)(collect001))) {
                    {
                      collect001 = cons(chaR, NIL);
                      if (charset == NIL) {
                        charset = collect001;
                      }
                      else {
                        addConsToEndOfConsList(charset, collect001);
                      }
                    }
                  }
                  else {
                    {
                      collect001->rest = cons(chaR, NIL);
                      collect001 = collect001->rest;
                    }
                  }
                }
              }
            }
          }
        }
      }
      else if (subtypeOfP(testValue000, SGT_READ_STELLA_GENERALIZED_SYMBOL)) {
        { Object* characterspec003 = characterspec;
          GeneralizedSymbol* characterspec = ((GeneralizedSymbol*)(characterspec003));

          { const char* testValue001 = characterspec->symbolName;

            if (stringEqlP(testValue001, "ANY")) {
              { int i = NULL_INTEGER;
                int iter002 = 0;
                int upperBound000 = oMAX_TOKENIZER_CHARACTERSo - 1;
                Cons* collect002 = NULL;

                for  (; iter002 <= upperBound000; 
                      iter002 = iter002 + 1) {
                  i = iter002;
                  if (!((boolean)(collect002))) {
                    {
                      collect002 = cons(wrapCharacter((char) i), NIL);
                      if (charset == NIL) {
                        charset = collect002;
                      }
                      else {
                        addConsToEndOfConsList(charset, collect002);
                      }
                    }
                  }
                  else {
                    {
                      collect002->rest = cons(wrapCharacter((char) i), NIL);
                      collect002 = collect002->rest;
                    }
                  }
                }
              }
            }
            else if (stringEqlP(testValue001, "OTHERWISE")) {
              { Cons* set = NULL;
                Cons* iter003 = allcharactersets->theConsList;

                for (; !(iter003 == NIL); iter003 = iter003->rest) {
                  set = ((Cons*)(iter003->value));
                  { CharacterWrapper* chaR = NULL;
                    Cons* iter004 = set;
                    Cons* collect003 = NULL;

                    for  (; !(iter004 == NIL); 
                          iter004 = iter004->rest) {
                      chaR = ((CharacterWrapper*)(iter004->value));
                      if (!((boolean)(collect003))) {
                        {
                          collect003 = cons(chaR, NIL);
                          if (charset == NIL) {
                            charset = collect003;
                          }
                          else {
                            addConsToEndOfConsList(charset, collect003);
                          }
                        }
                      }
                      else {
                        {
                          collect003->rest = cons(chaR, NIL);
                          collect003 = collect003->rest;
                        }
                      }
                    }
                  }
                }
              }
              { int i = NULL_INTEGER;
                int iter005 = 0;
                int upperBound001 = oMAX_TOKENIZER_CHARACTERSo - 1;
                Cons* collect004 = NULL;

                for  (; iter005 <= upperBound001; 
                      iter005 = iter005 + 1) {
                  i = iter005;
                  if (!charset->memberP(wrapCharacter((char) i))) {
                    if (!((boolean)(collect004))) {
                      {
                        collect004 = cons(wrapCharacter((char) i), NIL);
                        if (complementset == NIL) {
                          complementset = collect004;
                        }
                        else {
                          addConsToEndOfConsList(complementset, collect004);
                        }
                      }
                    }
                    else {
                      {
                        collect004->rest = cons(wrapCharacter((char) i), NIL);
                        collect004 = collect004->rest;
                      }
                    }
                  }
                }
              }
              charset = complementset;
            }
            else {
              return (NULL);
            }
          }
        }
      }
      else {
        return (NULL);
      }
    }
    return (charset);
  }
}

const char* stringifyTokenizerTable(TokenizerTable* table) {
  { OutputStringStream* result = newOutputStringStream();
    int acode = (int)(unsigned char) 'A';
    const char* transitions = table->transitions;
    char* encodedtransitions = native_make_mutable_string((2 * oMAX_TOKENIZER_STATESo * oMAX_TOKENIZER_CHARACTERSo), NULL_CHARACTER);
    int j = -1;
    Vector* uniquestatenames = table->uniqueStateNames;
    Vector* statenames = table->stateNames;
    Vector* eofstates = table->legalEofStates;
    const char* separator = "|";

    *(result->nativeStream) << (2 * oMAX_TOKENIZER_STATESo * oMAX_TOKENIZER_CHARACTERSo) << separator;
    { int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = (oMAX_TOKENIZER_STATESo * oMAX_TOKENIZER_CHARACTERSo) - 1;

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        i = iter000;
        encodedtransitions[(j = j + 1)] = ((char) ((((int)(unsigned char) (transitions[i])) & 15) + acode));
        encodedtransitions[(j = j + 1)] = ((char) ((((int)(unsigned char) (transitions[i])) >> 4) + acode));
      }
    }
    *(result->nativeStream) << encodedtransitions << separator;
    *(result->nativeStream) << uniquestatenames->length() << separator;
    { GeneralizedSymbol* state = NULL;
      Vector* vector000 = uniquestatenames;
      int index000 = 0;
      int length000 = vector000->length();

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        state = ((GeneralizedSymbol*)((vector000->theArray)[index000]));
        *(result->nativeStream) << state->symbolName << separator;
      }
    }
    *(result->nativeStream) << statenames->length() << separator;
    { GeneralizedSymbol* state = NULL;
      Vector* vector001 = statenames;
      int index001 = 0;
      int length001 = vector001->length();

      for  (; index001 < length001; 
            index001 = index001 + 1) {
        state = ((GeneralizedSymbol*)((vector001->theArray)[index001]));
        *(result->nativeStream) << state->symbolName << separator;
      }
    }
    *(result->nativeStream) << eofstates->length() << separator;
    { BooleanWrapper* state = NULL;
      Vector* vector002 = eofstates;
      int index002 = 0;
      int length002 = vector002->length();

      for  (; index002 < length002; 
            index002 = index002 + 1) {
        state = ((BooleanWrapper*)((vector002->theArray)[index002]));
        *(result->nativeStream) << ((coerceWrappedBooleanToBoolean(state) ? "T" : "F"));
      }
    }
    *(result->nativeStream) << separator;
    return (result->theStringReader());
  }
}

TokenizerTable* unstringifyTokenizerTable(const char* table) {
  { TokenizerTable* result = newTokenizerTable();
    int acode = (int)(unsigned char) 'A';
    const char* line = NULL;
    int count = 0;
    char* transitions = NULL;
    char separator = '|';
    int start = 0;
    int end = 0;

    end = stringPosition(table, separator, start);
    line = stringSubsequence(table, start, end);
    start = end + 1;
    count = ((int)(stringToInteger(line)));
    end = stringPosition(table, separator, start);
    line = stringSubsequence(table, start, end);
    start = end + 1;
    transitions = native_make_mutable_string((((int)(count / 2.0))), NULL_CHARACTER);
    { int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = ((int)((count / 2.0) - 1));

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        i = iter000;
        transitions[i] = ((char) ((((int)(unsigned char) (line[(2 * i)]) - acode) | ((((int)(unsigned char) (line[((2 * i) + 1)]) - acode) << 4)))));
      }
    }
    result->transitions = transitions;
    end = stringPosition(table, separator, start);
    line = stringSubsequence(table, start, end);
    start = end + 1;
    count = ((int)(stringToInteger(line)));
    result->uniqueStateNames = stella::newVector(count);
    { int i = NULL_INTEGER;
      int iter001 = 0;
      int upperBound001 = count - 1;

      for  (; iter001 <= upperBound001; 
            iter001 = iter001 + 1) {
        i = iter001;
        end = stringPosition(table, separator, start);
        line = stringSubsequence(table, start, end);
        start = end + 1;
        (result->uniqueStateNames->theArray)[i] = (internKeyword(line));
      }
    }
    end = stringPosition(table, separator, start);
    line = stringSubsequence(table, start, end);
    start = end + 1;
    count = ((int)(stringToInteger(line)));
    result->stateNames = stella::newVector(count);
    { int i = NULL_INTEGER;
      int iter002 = 0;
      int upperBound002 = count - 1;

      for  (; iter002 <= upperBound002; 
            iter002 = iter002 + 1) {
        i = iter002;
        end = stringPosition(table, separator, start);
        line = stringSubsequence(table, start, end);
        start = end + 1;
        (result->stateNames->theArray)[i] = (internKeyword(line));
      }
    }
    end = stringPosition(table, separator, start);
    line = stringSubsequence(table, start, end);
    start = end + 1;
    count = ((int)(stringToInteger(line)));
    end = stringPosition(table, separator, start);
    line = stringSubsequence(table, start, end);
    start = end + 1;
    result->legalEofStates = stella::newVector(count);
    { int i = NULL_INTEGER;
      int iter003 = 0;
      int upperBound003 = count - 1;

      for  (; iter003 <= upperBound003; 
            iter003 = iter003 + 1) {
        i = iter003;
        switch (line[i]) {
          case 'T': 
            (result->legalEofStates->theArray)[i] = TRUE_WRAPPER;
            break;
          case 'F': 
            (result->legalEofStates->theArray)[i] = FALSE_WRAPPER;
            break;
          default:
            { OutputStringStream* stream000 = newOutputStringStream();

              *(stream000->nativeStream) << "`" << line[i] << "'" << " is not a valid case option";
              throw *newStellaException(stream000->theStringReader());
            }
            break;
        }
      }
    }
    return (result);
  }
}

char* makeTokenizerByteArray(int size) {
  return (new (PointerFreeGC) char[size]);
}

char* stringToTokenizerByteArray(const char* string) {
  return (mutableStringCopy(string));
}

const char* tokenizerByteArrayToString(char* bytes) {
  return (((const char*)bytes));
}

char tokenizerByteArrayByteArrayNth(char* buffer, int position) {
  return (buffer[position]);
}

char tokenizerByteArrayByteArrayNthSetter(char* buffer, char ch, int position) {
  return (buffer[position] = ch);
}

int nativeByteArrayReadSequence(char* buffer, std::istream* stream, int start, int end) {
  { int n = 0;

    if (stream->eof()) return start;
    stream->read(buffer + start, end - start);
    n = stream->gcount();
    return (n + start);
  }
}

int tokenizerByteArrayReadSequence(char* buffer, InputStream* stream, int start, int end) {
  { TokenizerStreamState* state = stream->tokenizerState;
    int cursor = state->cursor;
    int internalEnd = state->end;
    int internalSize = state->bufferSize;
    OutputStream* echostream = stream->echoStream;

    if (cursor == internalEnd) {
      if (readIntoTokenizerBuffer(stream, state, -1)) {
        return (0);
      }
      cursor = state->cursor;
      internalEnd = state->end;
      if (cursor == internalSize) {
        cursor = 0;
      }
    }
    { int readSize = stella::integerMin(end - start, internalEnd - cursor);
      int originalStart = start;
      char* internalBuffer = state->buffer;

      { int i = NULL_INTEGER;
        int iter000 = 1;
        int upperBound000 = readSize;
        boolean unboundedP000 = upperBound000 == NULL_INTEGER;

        for  (; unboundedP000 ||
                  (iter000 <= upperBound000); 
              iter000 = iter000 + 1) {
          i = iter000;
          i = i;
          buffer[start] = (internalBuffer[cursor]);
          start = start + 1;
          cursor = cursor + 1;
        }
      }
      if (((boolean)(echostream))) {
        byteArrayWriteSequence(buffer, echostream->nativeStream, originalStart, end);
      }
      state->cursor = cursor;
      return (readSize);
    }
  }
}

int byteArrayReadSequence(char* buffer, InputStream* stream, int start, int end) {
  // Read from `stream' filling `buffer' between `start' and `end' (depending
  // on how many characters are available).
  // Return the actual end pointer to the input read into `buffer'.  EOF is
  // indicated by the return value being equal to start.
  if (((boolean)(stream->tokenizerState))) {
    return (tokenizerByteArrayReadSequence(buffer, stream, start, end));
  }
  else {
    return (nativeByteArrayReadSequence(buffer, stream->nativeStream, start, end));
  }
}

void nativeByteArrayWriteSequence(char* buffer, std::ostream* stream, int start, int end) {
  stream->write(buffer + start, end - start);
}

void byteArrayWriteSequence(char* buffer, std::ostream* stream, int start, int end) {
  // Write from `buffer' to `stream', using data in the buffer starting at position
  // `start' stopping just before `end'.
  nativeByteArrayWriteSequence(buffer, stream, start, end);
}

int oTOKENIZER_INITIAL_BUFFER_SIZEo = 2048;

void ensureTokenizerBufferSize(TokenizerStreamState* state, int currenttokenstart, int requiredspace) {
  { int size = state->bufferSize;
    int newsize = size;
    int end = ((state->end) % size);
    int freespace = ((currenttokenstart == -1) ? size : (((end <= currenttokenstart) ? (currenttokenstart - end) : (currenttokenstart + (size - end)))));
    char* buffer = state->buffer;
    char* newbuffer = buffer;

    while (freespace < requiredspace) {
      freespace = freespace + newsize;
      newsize = newsize * 2;
    }
    if (newsize > size) {
      newbuffer = new (PointerFreeGC) char[newsize];
      if (currenttokenstart < 0) {
        state->cursor = 0;
        state->end = newsize;
      }
      else if (end > currenttokenstart) {
        { int i = NULL_INTEGER;
          int iter000 = currenttokenstart;
          int upperBound000 = end - 1;

          for  (; iter000 <= upperBound000; 
                iter000 = iter000 + 1) {
            i = iter000;
            newbuffer[i] = (buffer[i]);
          }
        }
      }
      else {
        { int i = NULL_INTEGER;
          int iter001 = currenttokenstart;
          int upperBound001 = size - 1;

          for  (; iter001 <= upperBound001; 
                iter001 = iter001 + 1) {
            i = iter001;
            newbuffer[i] = (buffer[i]);
          }
        }
        { int i = NULL_INTEGER;
          int iter002 = 0;
          int upperBound002 = end - 1;
          int j = NULL_INTEGER;
          int iter003 = size;

          for  (; iter002 <= upperBound002; 
                iter002 = iter002 + 1,
                iter003 = iter003 + 1) {
            i = iter002;
            j = iter003;
            newbuffer[j] = (buffer[i]);
          }
        }
        state->end = size + end;
        state->cursor = state->end;
      }
      state->buffer = newbuffer;
      state->bufferSize = newsize;
    }
  }
}

boolean readIntoTokenizerBuffer(InputStream* stream, TokenizerStreamState* state, int currenttokenstart) {
  { int requiredspace = ((state->bufferSize < oTOKENIZER_INITIAL_BUFFER_SIZEo) ? 1 : (oTOKENIZER_INITIAL_BUFFER_SIZEo >> 1));
    char inputchar = NULL_CHARACTER;
    const char* inputline = NULL;
    boolean eofP = false;

    if (!(stream->bufferingScheme == KWD_READ_BLOCK)) {
      try {
        stream->tokenizerState = NULL;
        { Keyword* testValue000 = stream->bufferingScheme;

          if (testValue000 == KWD_READ_LINE) {
            inputline = nativeReadLine(stream);
            if (inputline == NULL) {
              inputline = "";
              eofP = true;
            }
            inputline = stringConcatenate(inputline, EOL_STRING);
          }
          else if (testValue000 == KWD_READ_CHARACTER) {
            inputchar = readCharacter(stream, eofP);
            if (eofP) {
              inputline = "";
            }
            else {
              inputline = makeString(1, inputchar);
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
catch (...) {
        stream->tokenizerState = state;
        throw;
      }
      stream->tokenizerState = state;
      requiredspace = strlen(inputline);
    }
    ensureTokenizerBufferSize(state, currenttokenstart, requiredspace);
    { std::istream* nativestream = stream->nativeStream;
      char* buffer = state->buffer;
      int size = state->bufferSize;
      int end = state->end;
      int start = -1;

      if (end == size) {
        end = 0;
      }
      if (currenttokenstart < 0) {
        start = 0;
        end = size;
        state->cursor = 0;
      }
      else if (end <= currenttokenstart) {
        start = end;
        end = currenttokenstart;
      }
      else if (end > currenttokenstart) {
        start = end;
        end = size;
      }
      if (inputline != NULL) {
        end = start;
        { char ch = NULL_CHARACTER;
          const char* vector000 = inputline;
          int index000 = 0;
          int length000 = strlen(vector000);

          for  (; index000 < length000; 
                index000 = index000 + 1) {
            ch = vector000[index000];
            buffer[end] = ch;
            end = end + 1;
            if (end == size) {
              end = 0;
            }
          }
        }
      }
      else {
        end = nativeByteArrayReadSequence(buffer, nativestream, start, end);
      }
      state->end = end;
      return (eofP ||
          (start == end));
    }
  }
}

char readCharacterFromTokenizerBuffer(InputStream* stream, boolean& _Return1) {
  { TokenizerStreamState* state = stream->tokenizerState;
    int cursor = state->cursor;
    int end = state->end;
    int size = state->bufferSize;
    OutputStream* echostream = stream->echoStream;
    char ch = NULL_CHARACTER;

    if (cursor == end) {
      if (readIntoTokenizerBuffer(stream, state, -1)) {
        _Return1 = true;
        return (NULL_CHARACTER);
      }
      cursor = state->cursor;
      if (cursor == size) {
        cursor = 0;
      }
    }
    ch = (state->buffer)[cursor];
    if (((boolean)(echostream))) {
      *(echostream->nativeStream) << ch;
    }
    state->cursor = cursor + 1;
    _Return1 = false;
    return (ch);
  }
}

void unreadCharacterFromTokenizerBuffer(char chaR, InputStream* stream) {
  { TokenizerStreamState* state = stream->tokenizerState;
    int cursor = state->cursor;

    if (cursor == 0) {
      cursor = state->bufferSize - 1;
    }
    else {
      cursor = cursor - 1;
    }
    if (!(chaR == (state->buffer)[cursor])) {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "Unread character " << "`" << chaR << "'" << " does not match last character read";
        throw *newStellaException(stream000->theStringReader());
      }
    }
    state->cursor = cursor;
  }
}

const char* readLineFromTokenizerBuffer(InputStream* stream) {
  { OutputStringStream* buffer = newOutputStringStream();
    const char* line = NULL;
    char ch = NULL_CHARACTER;
    char ch2 = NULL_CHARACTER;
    boolean eofP = false;
    char newline = EOL_STRING[0];

    for (;;) {
      ch = readCharacterFromTokenizerBuffer(stream, eofP);
      if (eofP) {
        line = buffer->theStringReader();
        if (strlen(line) == 0) {
          line = NULL;
        }
        else {
          eofP = false;
        }
        break;
      }
      if (ch == newline) {
        if (strlen(EOL_STRING) == 2) {
          ch2 = readCharacterFromTokenizerBuffer(stream, eofP);
          if (eofP) {
            line = buffer->theStringReader();
            if (strlen(line) == 0) {
              line = NULL;
            }
            else {
              eofP = false;
            }
            break;
          }
          if (!(ch2 == EOL_STRING[1])) {
            *(buffer->nativeStream) << ch << ch2;
            continue;
          }
        }
        line = buffer->theStringReader();
        break;
      }
      *(buffer->nativeStream) << ch;
    }
    return (line);
  }
}

TokenizerToken* newTokenizerToken() {
  { TokenizerToken* self = NULL;

    self = new TokenizerToken();
    self->next = NULL;
    self->content = NULL;
    self->type = NULL;
    return (self);
  }
}

Surrogate* TokenizerToken::primaryType() {
  { TokenizerToken* self = this;

    return (SGT_READ_STELLA_TOKENIZER_TOKEN);
  }
}

Object* accessTokenizerTokenSlotValue(TokenizerToken* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_READ_STELLA_TYPE) {
    if (setvalueP) {
      self->type = ((Keyword*)(value));
    }
    else {
      value = self->type;
    }
  }
  else if (slotname == SYM_READ_STELLA_CONTENT) {
    if (setvalueP) {
      self->content = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->content);
    }
  }
  else if (slotname == SYM_READ_STELLA_NEXT) {
    if (setvalueP) {
      self->next = ((TokenizerToken*)(value));
    }
    else {
      value = self->next;
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

TokenizerStreamState* newTokenizerStreamState() {
  { TokenizerStreamState* self = NULL;

    self = new TokenizerStreamState();
    self->tokenList = NULL;
    self->stateDictionary = NULL;
    self->table = NULL;
    self->state = 1;
    self->end = oTOKENIZER_INITIAL_BUFFER_SIZEo;
    self->cursor = oTOKENIZER_INITIAL_BUFFER_SIZEo;
    self->bufferSize = oTOKENIZER_INITIAL_BUFFER_SIZEo;
    self->buffer = new (PointerFreeGC) char[oTOKENIZER_INITIAL_BUFFER_SIZEo];
    return (self);
  }
}

Surrogate* TokenizerStreamState::primaryType() {
  { TokenizerStreamState* self = this;

    return (SGT_READ_STELLA_TOKENIZER_STREAM_STATE);
  }
}

Object* accessTokenizerStreamStateSlotValue(TokenizerStreamState* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_READ_STELLA_BUFFER_SIZE) {
    if (setvalueP) {
      self->bufferSize = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->bufferSize);
    }
  }
  else if (slotname == SYM_READ_STELLA_CURSOR) {
    if (setvalueP) {
      self->cursor = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->cursor);
    }
  }
  else if (slotname == SYM_READ_STELLA_END) {
    if (setvalueP) {
      self->end = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->end);
    }
  }
  else if (slotname == SYM_READ_STELLA_STATE) {
    if (setvalueP) {
      self->state = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->state);
    }
  }
  else if (slotname == SYM_READ_STELLA_TABLE) {
    if (setvalueP) {
      self->table = ((TokenizerTable*)(value));
    }
    else {
      value = self->table;
    }
  }
  else if (slotname == SYM_READ_STELLA_STATE_DICTIONARY) {
    if (setvalueP) {
      self->stateDictionary = ((Dictionary*)(value));
    }
    else {
      value = self->stateDictionary;
    }
  }
  else if (slotname == SYM_READ_STELLA_TOKEN_LIST) {
    if (setvalueP) {
      self->tokenList = ((TokenizerToken*)(value));
    }
    else {
      value = self->tokenList;
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

int TokenizerStreamState::bufferedInputLength() {
  { TokenizerStreamState* state = this;

    { int cursor = state->cursor;
      int end = state->end;

      if (end >= cursor) {
        return (end - cursor);
      }
      else {
        return ((state->bufferSize - cursor) + end);
      }
    }
  }
}

void TokenizerStreamState::clear() {
  { TokenizerStreamState* state = this;

    state->cursor = 0;
    state->end = 0;
  }
}

void TokenizerStreamState::reset() {
  { TokenizerStreamState* state = this;

    state->state = 1;
    state->stateDictionary = NULL;
  }
}

int TokenizerStreamState::getSavedState(TokenizerTable* table) {
  { TokenizerStreamState* stateObject = this;

    if (!((boolean)(stateObject->table))) {
      stateObject->table = table;
      return (stateObject->state);
    }
    else if (stateObject->table == table) {
      return (stateObject->state);
    }
    else {
      if (!((boolean)(stateObject->stateDictionary))) {
        stateObject->stateDictionary = newKeyValueList();
      }
      stateObject->stateDictionary->insertAt(stateObject->table, wrapInteger(stateObject->state));
      { IntegerWrapper* savedState = ((IntegerWrapper*)(stateObject->stateDictionary->lookup(table)));

        if (((boolean)(savedState))) {
          return (savedState->wrapperValue);
        }
        else {
          return (1);
        }
      }
    }
  }
}

DEFINE_STELLA_SPECIAL(oWITHTOKENIZERINPUTTYPEo, Surrogate* , NULL);

Object* withTokenizer(Object* table, Object* input, Cons* body) {
  { StandardObject* dummy1;
    StandardObject* dummy2;
    StandardObject* dummy3;

    { Object* inputtree = NULL;
      StandardObject* inputtype = NULL;

      inputtree = walkATree(input, inputtype);
      if (!(subTypeSpecOfP(inputtype, SGT_READ_STELLA_INPUT_STREAM) ||
          subTypeSpecOfP(inputtype, SGT_READ_STELLA_STRING))) {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationError();
          if (!(suppressWarningsP())) {
            printErrorContext(">> ERROR: ", STANDARD_ERROR);
            *(STANDARD_ERROR->nativeStream) << std::endl << " " << "with-tokenizer: Can't handle input of type " << "`" << deUglifyParseTree(inputtype) << "'" << "." << std::endl;
          }
        }
        return (walkDontCallMeTree(body, SGT_READ_STELLA_VOID, dummy1));
      }
      { boolean stringP = subTypeSpecOfP(inputtype, SGT_READ_STELLA_STRING) ||
            subTypeSpecOfP(inputtype, SGT_READ_STELLA_MUTABLE_STRING);
        Cons* expansion = listO(4, SYM_READ_STELLA_LET, listO(6, listO(3, SYM_READ_STELLA_TOK_TABLE_, table, NIL), listO(3, SYM_READ_STELLA_TOK_TRANSITIONS_, listO(3, SYM_READ_STELLA_TRANSITIONS, SYM_READ_STELLA_TOK_TABLE_, NIL), NIL), listO(3, SYM_READ_STELLA_TOK_STATENAMES_, listO(3, SYM_READ_STELLA_THE_ARRAY, listO(3, SYM_READ_STELLA_STATE_NAMES, SYM_READ_STELLA_TOK_TABLE_, NIL), NIL), NIL), listO(3, SYM_READ_STELLA_TOK_TOKENSTART_, wrapInteger(-1), NIL), listO(3, SYM_READ_STELLA_TOK_ENDOFTOKENSp_, SYM_READ_STELLA_FALSE, NIL), ((stringP ? listO(8, listO(4, SYM_READ_STELLA_TOK_STREAMSTATE_, SYM_READ_STELLA_TOKENIZER_STREAM_STATE, SYM_READ_STELLA_NULL, NIL), listO(3, SYM_READ_STELLA_TOK_BUFFER_, listO(3, SYM_READ_STELLA_STRING_TO_TOKENIZER_BYTE_ARRAY, input, NIL), NIL), listO(3, SYM_READ_STELLA_TOK_STATE_, wrapInteger(1), NIL), listO(3, SYM_READ_STELLA_TOK_NEXTSTATE_, SYM_READ_STELLA_TOK_STATE_, NIL), listO(3, SYM_READ_STELLA_TOK_CURSOR_, wrapInteger(0), NIL), listO(3, SYM_READ_STELLA_TOK_SIZE_, listO(3, SYM_READ_STELLA_LENGTH, input, NIL), NIL), listO(3, SYM_READ_STELLA_TOK_END_, SYM_READ_STELLA_TOK_SIZE_, NIL), NIL) : listO(11, listO(3, SYM_READ_STELLA_TOK_INPUTSTREAM_, sysTree(inputtree, inputtype, dummy2), NIL), listO(3, SYM_READ_STELLA_TOK_ECHOSTREAM_, listO(3, SYM_READ_STELLA_ECHO_STREAM, SYM_READ_STELLA_TOK_INPUTSTREAM_, NIL), NIL), listO(3, SYM_READ_STELLA_TOK_STREAMSTATE_, listO(5, SYM_READ_STELLA_CHOOSE, listO(3, SYM_READ_STELLA_NULLp, listO(3, SYM_READ_STELLA_TOKENIZER_STATE, SYM_READ_STELLA_TOK_INPUTSTREAM_, NIL), NIL), listO(4, SYM_READ_STELLA_SETF, listO(3, SYM_READ_STELLA_TOKENIZER_STATE, SYM_READ_STELLA_TOK_INPUTSTREAM_, NIL), listO(3, SYM_READ_STELLA_NEW, SYM_READ_STELLA_TOKENIZER_STREAM_STATE, NIL), NIL), listO(3, SYM_READ_STELLA_TOKENIZER_STATE, SYM_READ_STELLA_TOK_INPUTSTREAM_, NIL), NIL), NIL), listO(3, SYM_READ_STELLA_TOK_BUFFER_, listO(3, SYM_READ_STELLA_BUFFER, SYM_READ_STELLA_TOK_STREAMSTATE_, NIL), NIL), listO(3, SYM_READ_STELLA_TOK_SIZE_, listO(3, SYM_READ_STELLA_BUFFER_SIZE, SYM_READ_STELLA_TOK_STREAMSTATE_, NIL), NIL), listO(3, SYM_READ_STELLA_TOK_STATE_, listO(4, SYM_READ_STELLA_GET_SAVED_STATE, SYM_READ_STELLA_TOK_STREAMSTATE_, SYM_READ_STELLA_TOK_TABLE_, NIL), NIL), listO(3, SYM_READ_STELLA_TOK_NEXTSTATE_, SYM_READ_STELLA_TOK_STATE_, NIL), listO(3, SYM_READ_STELLA_TOK_CURSOR_, listO(3, SYM_READ_STELLA_CURSOR, SYM_READ_STELLA_TOK_STREAMSTATE_, NIL), NIL), listO(3, SYM_READ_STELLA_TOK_END_, listO(3, SYM_READ_STELLA_END, SYM_READ_STELLA_TOK_STREAMSTATE_, NIL), NIL), listO(3, SYM_READ_STELLA_TOK_CHECKPOINT_, listO(5, SYM_READ_STELLA_CHOOSE, listO(4, SYM_READ_STELLA_le, SYM_READ_STELLA_TOK_CURSOR_, SYM_READ_STELLA_TOK_END_, NIL), SYM_READ_STELLA_TOK_END_, SYM_READ_STELLA_TOK_SIZE_, NIL), NIL), NIL)))->concatenate(NIL, 0)), listO(4, SYM_READ_STELLA_IGNORE, SYM_READ_STELLA_TOK_STATENAMES_, SYM_READ_STELLA_TOK_ENDOFTOKENSp_, NIL), ((stringP ? cons(listO(3, SYM_READ_STELLA_IGNORE, SYM_READ_STELLA_TOK_STREAMSTATE_, NIL), NIL) : NIL))->concatenate(body->concatenate(NIL, 0), 0));

        { 
          BIND_STELLA_SPECIAL(oWITHTOKENIZERINPUTTYPEo, Surrogate*, ((Surrogate*)(inputtype)));
          return (walkATree(((Cons*)(copyConsTree(expansion))), dummy3));
        }
      }
    }
  }
}

boolean withTokenizerStringInputP() {
  return (oWITHTOKENIZERINPUTTYPEo == SGT_READ_STELLA_STRING);
}

boolean insideWithTokenizerP() {
  return (((boolean)(oWITHTOKENIZERINPUTTYPEo)));
}

Object* endOfTokensP() {
  if (!insideWithTokenizerP()) {
    { 
      BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
      signalTranslationError();
      if (!(suppressWarningsP())) {
        printErrorContext(">> ERROR: ", STANDARD_ERROR);
        *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Encountered `end-of-tokens?' outside of `with-tokenizer' macro." << "." << std::endl;
      }
    }
    return (cons(SYM_READ_STELLA_END_OF_TOKENSp, NIL));
  }
  return (SYM_READ_STELLA_TOK_ENDOFTOKENSp_);
}

Object* getTokenText(Cons* options) {
  if (!insideWithTokenizerP()) {
    { 
      BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
      signalTranslationError();
      if (!(suppressWarningsP())) {
        printErrorContext(">> ERROR: ", STANDARD_ERROR);
        *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Encountered `get-token-text' outside of `with-tokenizer' macro." << "." << std::endl;
      }
    }
    return (cons(SYM_READ_STELLA_GET_TOKEN_TEXT, NIL));
  }
  { Object* upcaseP = options->value;
    Object* start = options->rest->value;
    Object* end = options->rest->rest->value;

    if (upcaseP == SYM_READ_STELLA_FALSE) {
      upcaseP = NULL;
    }
    if (eqlP(start, ZERO_WRAPPER)) {
      start = NULL;
    }
    return (listO(4, SYM_READ_STELLA_GET_TOKEN_TEXT_INTERNAL, SYM_READ_STELLA_TOK_BUFFER_, ((!((boolean)(start))) ? ((StandardObject*)(SYM_READ_STELLA_TOK_TOKENSTART_)) : ((StandardObject*)(listO(4, SYM_READ_STELLA_i, SYM_READ_STELLA_TOK_TOKENSTART_, start, NIL)))), cons(((!((boolean)(end))) ? ((StandardObject*)(SYM_READ_STELLA_TOK_CURSOR_)) : ((StandardObject*)((integerP(end) ? (((((IntegerWrapper*)(end))->wrapperValue < 0) ? listO(4, SYM_READ_STELLA_i, SYM_READ_STELLA_TOK_CURSOR_, end, NIL) : listO(4, SYM_READ_STELLA_i, SYM_READ_STELLA_TOK_TOKENSTART_, end, NIL))) : listO(5, SYM_READ_STELLA_CHOOSE, listO(3, SYM_READ_STELLA_l, end, cons(wrapInteger(0), NIL)), listO(4, SYM_READ_STELLA_i, SYM_READ_STELLA_TOK_CURSOR_, end, NIL), listO(4, SYM_READ_STELLA_i, SYM_READ_STELLA_TOK_TOKENSTART_, end, NIL), NIL))))), listO(3, SYM_READ_STELLA_TOK_SIZE_, (((boolean)(upcaseP)) ? upcaseP : SYM_READ_STELLA_FALSE), NIL))));
  }
}

const char* getTokenTextInternal(char* buffer, int start, int end, int size, boolean upcaseP) {
  if (start >= size) {
    start = start - size;
  }
  else if (start < 0) {
    start = size + start;
  }
  if (end > size) {
    end = end - size;
  }
  else if (end < 0) {
    end = size + end;
  }
  { int length = end - start;
    char* result = NULL;
    int cursor = 0;
    int auxend = end;

    if (length < 0) {
      length = length + size;
      auxend = size;
    }
    result = makeRawMutableString(length);
    if (upcaseP) {
      for (;;) {
        while (start < auxend) {
          result[cursor] = (oCHARACTER_UPCASE_TABLEo[((int)(unsigned char) (buffer[start]))]);
          cursor = cursor + 1;
          start = start + 1;
        }
        if (auxend == end) {
          break;
        }
        start = 0;
        auxend = end;
      }
    }
    else {
      for (;;) {
        while (start < auxend) {
          result[cursor] = (buffer[start]);
          cursor = cursor + 1;
          start = start + 1;
        }
        if (auxend == end) {
          break;
        }
        start = 0;
        auxend = end;
      }
    }
    return (result);
  }
}

Object* copyTokenText(Object* buffer, Cons* options) {
  if (!insideWithTokenizerP()) {
    { 
      BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
      signalTranslationError();
      if (!(suppressWarningsP())) {
        printErrorContext(">> ERROR: ", STANDARD_ERROR);
        *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Encountered `copy-token-text' outside of `with-tokenizer' macro." << "." << std::endl;
      }
    }
    return (cons(SYM_READ_STELLA_GET_TOKEN_TEXT, NIL));
  }
  { Object* upcaseP = options->value;
    Object* start = options->rest->value;
    Object* end = options->rest->rest->value;

    if (upcaseP == SYM_READ_STELLA_FALSE) {
      upcaseP = NULL;
    }
    if (eqlP(start, ZERO_WRAPPER)) {
      start = NULL;
    }
    return (listO(4, SYM_READ_STELLA_COPY_TOKEN_TEXT_INTERNAL, SYM_READ_STELLA_TOK_BUFFER_, ((!((boolean)(start))) ? ((StandardObject*)(SYM_READ_STELLA_TOK_TOKENSTART_)) : ((StandardObject*)(listO(4, SYM_READ_STELLA_i, SYM_READ_STELLA_TOK_TOKENSTART_, start, NIL)))), cons(((!((boolean)(end))) ? ((StandardObject*)(SYM_READ_STELLA_TOK_CURSOR_)) : ((StandardObject*)((integerP(end) ? (((((IntegerWrapper*)(end))->wrapperValue < 0) ? listO(4, SYM_READ_STELLA_i, SYM_READ_STELLA_TOK_CURSOR_, end, NIL) : listO(4, SYM_READ_STELLA_i, SYM_READ_STELLA_TOK_TOKENSTART_, end, NIL))) : listO(5, SYM_READ_STELLA_CHOOSE, listO(3, SYM_READ_STELLA_l, end, cons(wrapInteger(0), NIL)), listO(4, SYM_READ_STELLA_i, SYM_READ_STELLA_TOK_CURSOR_, end, NIL), listO(4, SYM_READ_STELLA_i, SYM_READ_STELLA_TOK_TOKENSTART_, end, NIL), NIL))))), listO(3, SYM_READ_STELLA_TOK_SIZE_, (((boolean)(upcaseP)) ? upcaseP : SYM_READ_STELLA_FALSE), cons(buffer, NIL)))));
  }
}

int copyTokenTextInternal(char* buffer, int start, int end, int size, boolean upcaseP, BufferedString* resultbuffer) {
  if (start >= size) {
    start = start - size;
  }
  else if (start < 0) {
    start = size + start;
  }
  if (end > size) {
    end = end - size;
  }
  else if (end < 0) {
    end = size + end;
  }
  { int length = end - start;
    int auxend = end;
    char* result = resultbuffer->buffer;
    int cursor = resultbuffer->fillPointer;

    if (length < 0) {
      length = length + size;
      auxend = size;
    }
    if ((cursor + length) > resultbuffer->bufferSize) {
      result = resultbuffer->ensureFreeSpace(length);
    }
    if (upcaseP) {
      for (;;) {
        while (start < auxend) {
          result[cursor] = (oCHARACTER_UPCASE_TABLEo[((int)(unsigned char) (buffer[start]))]);
          cursor = cursor + 1;
          start = start + 1;
        }
        if (auxend == end) {
          break;
        }
        start = 0;
        auxend = end;
      }
    }
    else {
      for (;;) {
        while (start < auxend) {
          result[cursor] = (buffer[start]);
          cursor = cursor + 1;
          start = start + 1;
        }
        if (auxend == end) {
          break;
        }
        start = 0;
        auxend = end;
      }
    }
    resultbuffer->fillPointer = cursor;
    return (cursor);
  }
}

Object* getTokenType() {
  if (!insideWithTokenizerP()) {
    { 
      BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
      signalTranslationError();
      if (!(suppressWarningsP())) {
        printErrorContext(">> ERROR: ", STANDARD_ERROR);
        *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Encountered `get-token-type' outside of `with-tokenizer' macro." << "." << std::endl;
      }
    }
    return (cons(SYM_READ_STELLA_GET_TOKEN_TYPE, NIL));
  }
  return (listO(4, SYM_READ_STELLA_NTH, SYM_READ_STELLA_TOK_STATENAMES_, SYM_READ_STELLA_TOK_STATE_, NIL));
}

Object* saveTokenizerStreamState() {
  return (listO(6, SYM_READ_STELLA_WHEN, listO(3, SYM_READ_STELLA_DEFINEDp, SYM_READ_STELLA_TOK_STREAMSTATE_, NIL), listO(4, SYM_READ_STELLA_SETF, listO(3, SYM_READ_STELLA_CURSOR, SYM_READ_STELLA_TOK_STREAMSTATE_, NIL), SYM_READ_STELLA_TOK_CURSOR_, NIL), listO(4, SYM_READ_STELLA_SETF, listO(3, SYM_READ_STELLA_TABLE, SYM_READ_STELLA_TOK_STREAMSTATE_, NIL), SYM_READ_STELLA_TOK_TABLE_, NIL), listO(4, SYM_READ_STELLA_SETF, listO(3, SYM_READ_STELLA_STATE, SYM_READ_STELLA_TOK_STREAMSTATE_, NIL), SYM_READ_STELLA_TOK_STATE_, NIL), NIL));
}

Object* restoreTokenizerStreamState() {
  return (listO(6, SYM_READ_STELLA_WHEN, listO(3, SYM_READ_STELLA_DEFINEDp, SYM_READ_STELLA_TOK_STREAMSTATE_, NIL), listO(4, SYM_READ_STELLA_SETQ, SYM_READ_STELLA_TOK_CURSOR_, listO(3, SYM_READ_STELLA_CURSOR, SYM_READ_STELLA_TOK_STREAMSTATE_, NIL), NIL), listO(4, SYM_READ_STELLA_SETQ, SYM_READ_STELLA_TOK_TABLE_, listO(3, SYM_READ_STELLA_TABLE, SYM_READ_STELLA_TOK_STREAMSTATE_, NIL), NIL), listO(4, SYM_READ_STELLA_SETQ, SYM_READ_STELLA_TOK_STATE_, listO(3, SYM_READ_STELLA_STATE, SYM_READ_STELLA_TOK_STREAMSTATE_, NIL), NIL), NIL));
}

boolean oTRACE_GET_NEXT_TOKENpo = false;

Object* getNextToken(Cons* options) {
  if (!insideWithTokenizerP()) {
    { 
      BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
      signalTranslationError();
      if (!(suppressWarningsP())) {
        printErrorContext(">> ERROR: ", STANDARD_ERROR);
        *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Encountered `get-next-token' outside of `with-tokenizer' macro." << "." << std::endl;
      }
    }
    return (cons(SYM_READ_STELLA_GET_NEXT_TOKEN, NIL));
  }
  { Object* savestreamstateP = options->value;
    Cons* savestreamstatetree = cons(cons(SYM_READ_STELLA_SAVE_TOKENIZER_STREAM_STATE, NIL), NIL);

    if ((!((boolean)(savestreamstateP))) ||
        (savestreamstateP == SYM_READ_STELLA_TRUE)) {
    }
    else if (savestreamstateP == SYM_READ_STELLA_FALSE) {
      savestreamstatetree = NIL;
    }
    else {
      savestreamstatetree = cons(listO(3, SYM_READ_STELLA_WHEN, savestreamstateP, savestreamstatetree->concatenate(NIL, 0)), NIL);
    }
    return (listO(4, SYM_READ_STELLA_PROGN, listO(4, SYM_READ_STELLA_SETQ, SYM_READ_STELLA_TOK_TOKENSTART_, wrapInteger(-1), NIL), listO(3, SYM_READ_STELLA_LOOP, (withTokenizerStringInputP() ? listO(5, SYM_READ_STELLA_WHEN, listO(4, SYM_READ_STELLA_e, SYM_READ_STELLA_TOK_CURSOR_, SYM_READ_STELLA_TOK_END_, NIL), listO(5, SYM_READ_STELLA_COND, listO(3, listO(4, SYM_READ_STELLA_e, SYM_READ_STELLA_TOK_NEXTSTATE_, wrapInteger(-1), NIL), listO(4, SYM_READ_STELLA_SETQ, SYM_READ_STELLA_TOK_ENDOFTOKENSp_, SYM_READ_STELLA_TRUE, NIL), NIL), listO(4, listO(4, SYM_READ_STELLA_NTH, listO(3, SYM_READ_STELLA_LEGAL_EOF_STATES, SYM_READ_STELLA_TOK_TABLE_, NIL), SYM_READ_STELLA_TOK_STATE_, NIL), listO(4, SYM_READ_STELLA_SETQ, SYM_READ_STELLA_TOK_NEXTSTATE_, wrapInteger(-1), NIL), listO(4, SYM_READ_STELLA_WHEN, listO(4, SYM_READ_STELLA_e, SYM_READ_STELLA_TOK_TOKENSTART_, wrapInteger(-1), NIL), listO(4, SYM_READ_STELLA_SETQ, SYM_READ_STELLA_TOK_ENDOFTOKENSp_, SYM_READ_STELLA_TRUE, NIL), NIL), NIL), listO(4, SYM_READ_STELLA_OTHERWISE, listO(4, SYM_READ_STELLA_SETQ, SYM_READ_STELLA_TOK_STATE_, wrapInteger(0), NIL), listO(4, SYM_READ_STELLA_SETQ, SYM_READ_STELLA_TOK_NEXTSTATE_, wrapInteger(-1), NIL), NIL), NIL), cons(SYM_READ_STELLA_BREAK, NIL), NIL) : listO(4, SYM_READ_STELLA_WHEN, listO(4, SYM_READ_STELLA_e, SYM_READ_STELLA_TOK_CURSOR_, SYM_READ_STELLA_TOK_CHECKPOINT_, NIL), listO(4, SYM_READ_STELLA_COND, listO(10, listO(4, SYM_READ_STELLA_e, SYM_READ_STELLA_TOK_CURSOR_, SYM_READ_STELLA_TOK_END_, NIL), listO(4, SYM_READ_STELLA_SETF, listO(3, SYM_READ_STELLA_CURSOR, SYM_READ_STELLA_TOK_STREAMSTATE_, NIL), SYM_READ_STELLA_TOK_CURSOR_, NIL), listO(4, SYM_READ_STELLA_SETQ, SYM_READ_STELLA_TOK_ENDOFTOKENSp_, listO(5, SYM_READ_STELLA_READ_INTO_TOKENIZER_BUFFER, SYM_READ_STELLA_TOK_INPUTSTREAM_, SYM_READ_STELLA_TOK_STREAMSTATE_, SYM_READ_STELLA_TOK_TOKENSTART_, NIL), NIL), listO(4, SYM_READ_STELLA_SETQ, SYM_READ_STELLA_TOK_BUFFER_, listO(3, SYM_READ_STELLA_BUFFER, SYM_READ_STELLA_TOK_STREAMSTATE_, NIL), NIL), listO(4, SYM_READ_STELLA_SETQ, SYM_READ_STELLA_TOK_SIZE_, listO(3, SYM_READ_STELLA_BUFFER_SIZE, SYM_READ_STELLA_TOK_STREAMSTATE_, NIL), NIL), listO(4, SYM_READ_STELLA_SETQ, SYM_READ_STELLA_TOK_CURSOR_, listO(4, SYM_READ_STELLA_MOD, listO(3, SYM_READ_STELLA_CURSOR, SYM_READ_STELLA_TOK_STREAMSTATE_, NIL), SYM_READ_STELLA_TOK_SIZE_, NIL), NIL), listO(4, SYM_READ_STELLA_SETQ, SYM_READ_STELLA_TOK_END_, listO(3, SYM_READ_STELLA_END, SYM_READ_STELLA_TOK_STREAMSTATE_, NIL), NIL), listO(6, SYM_READ_STELLA_WHEN, SYM_READ_STELLA_TOK_ENDOFTOKENSp_, listO(4, SYM_READ_STELLA_SETQ, SYM_READ_STELLA_TOK_CHECKPOINT_, SYM_READ_STELLA_TOK_CURSOR_, NIL), listO(5, SYM_READ_STELLA_COND, cons(listO(4, SYM_READ_STELLA_e, SYM_READ_STELLA_TOK_NEXTSTATE_, wrapInteger(-1), NIL), NIL), listO(4, listO(4, SYM_READ_STELLA_NTH, listO(3, SYM_READ_STELLA_LEGAL_EOF_STATES, SYM_READ_STELLA_TOK_TABLE_, NIL), SYM_READ_STELLA_TOK_STATE_, NIL), listO(4, SYM_READ_STELLA_SETQ, SYM_READ_STELLA_TOK_NEXTSTATE_, wrapInteger(-1), NIL), listO(4, SYM_READ_STELLA_UNLESS, listO(4, SYM_READ_STELLA_e, SYM_READ_STELLA_TOK_TOKENSTART_, wrapInteger(-1), NIL), listO(4, SYM_READ_STELLA_SETQ, SYM_READ_STELLA_TOK_ENDOFTOKENSp_, SYM_READ_STELLA_FALSE, NIL), NIL), NIL), listO(5, SYM_READ_STELLA_OTHERWISE, listO(4, SYM_READ_STELLA_SETQ, SYM_READ_STELLA_TOK_ENDOFTOKENSp_, SYM_READ_STELLA_FALSE, NIL), listO(4, SYM_READ_STELLA_SETQ, SYM_READ_STELLA_TOK_STATE_, wrapInteger(0), NIL), listO(4, SYM_READ_STELLA_SETQ, SYM_READ_STELLA_TOK_NEXTSTATE_, wrapInteger(-1), NIL), NIL), NIL), cons(SYM_READ_STELLA_BREAK, NIL), NIL), listO(5, SYM_READ_STELLA_IF, listO(4, SYM_READ_STELLA_ge, SYM_READ_STELLA_TOK_CURSOR_, SYM_READ_STELLA_TOK_END_, NIL), listO(4, SYM_READ_STELLA_SETQ, SYM_READ_STELLA_TOK_CHECKPOINT_, SYM_READ_STELLA_TOK_SIZE_, NIL), listO(4, SYM_READ_STELLA_SETQ, SYM_READ_STELLA_TOK_CHECKPOINT_, SYM_READ_STELLA_TOK_END_, NIL), NIL), NIL), listO(4, SYM_READ_STELLA_OTHERWISE, listO(4, SYM_READ_STELLA_SETQ, SYM_READ_STELLA_TOK_CHECKPOINT_, SYM_READ_STELLA_TOK_END_, NIL), listO(4, SYM_READ_STELLA_SETQ, SYM_READ_STELLA_TOK_CURSOR_, wrapInteger(0), NIL), NIL), NIL), NIL)), listO(5, listO(4, SYM_READ_STELLA_SETQ, SYM_READ_STELLA_TOK_NEXTSTATE_, listO(3, SYM_READ_STELLA_CHARACTER_CODE, listO(4, SYM_READ_STELLA_BYTE_ARRAY_NTH, SYM_READ_STELLA_TOK_BUFFER_, SYM_READ_STELLA_TOK_CURSOR_, NIL), NIL), NIL), listO(5, SYM_READ_STELLA_IF_OUTPUT_LANGUAGE, KWD_READ_COMMON_LISP, listO(4, SYM_READ_STELLA_WHEN, listO(4, SYM_READ_STELLA_g, SYM_READ_STELLA_TOK_NEXTSTATE_, wrapInteger(255), NIL), listO(4, SYM_READ_STELLA_SETQ, SYM_READ_STELLA_TOK_NEXTSTATE_, wrapInteger(255), NIL), NIL), SYM_READ_STELLA_NULL, NIL), listO(4, SYM_READ_STELLA_SETQ, SYM_READ_STELLA_TOK_NEXTSTATE_, listO(3, SYM_READ_STELLA_CHARACTER_CODE, listO(4, SYM_READ_STELLA_NTH, SYM_READ_STELLA_TOK_TRANSITIONS_, listO(4, SYM_READ_STELLA_LOGOR, listO(4, SYM_READ_STELLA_SHIFT_LEFT, SYM_READ_STELLA_TOK_STATE_, wrapInteger(8), NIL), SYM_READ_STELLA_TOK_NEXTSTATE_, NIL), NIL), NIL), NIL), listO(5, SYM_READ_STELLA_COND, listO(4, listO(4, SYM_READ_STELLA_e, listO(4, SYM_READ_STELLA_LOGAND, SYM_READ_STELLA_TOK_NEXTSTATE_, wrapInteger(128), NIL), wrapInteger(0), NIL), listO(4, SYM_READ_STELLA_SETQ, SYM_READ_STELLA_TOK_STATE_, SYM_READ_STELLA_TOK_NEXTSTATE_, NIL), listO(3, SYM_READ_STELLA_ii, SYM_READ_STELLA_TOK_CURSOR_, NIL), NIL), listO(5, listO(4, SYM_READ_STELLA_e, SYM_READ_STELLA_TOK_TOKENSTART_, wrapInteger(-1), NIL), listO(4, SYM_READ_STELLA_WHEN, listO(4, SYM_READ_STELLA_e, listO(4, SYM_READ_STELLA_LOGAND, SYM_READ_STELLA_TOK_NEXTSTATE_, wrapInteger(64), NIL), wrapInteger(0), NIL), listO(4, SYM_READ_STELLA_SETQ, SYM_READ_STELLA_TOK_TOKENSTART_, SYM_READ_STELLA_TOK_CURSOR_, NIL), NIL), listO(4, SYM_READ_STELLA_SETQ, SYM_READ_STELLA_TOK_STATE_, listO(4, SYM_READ_STELLA_LOGAND, SYM_READ_STELLA_TOK_NEXTSTATE_, wrapInteger(63), NIL), NIL), listO(3, SYM_READ_STELLA_ii, SYM_READ_STELLA_TOK_CURSOR_, NIL), NIL), listO(3, SYM_READ_STELLA_OTHERWISE, cons(SYM_READ_STELLA_BREAK, NIL), NIL), NIL), (((!withTokenizerStringInputP()) ? cons(listO(4, SYM_READ_STELLA_WHEN, listO(3, SYM_READ_STELLA_DEFINEDp, SYM_READ_STELLA_TOK_ECHOSTREAM_, NIL), listO(4, SYM_READ_STELLA_PRINT_STREAM, SYM_READ_STELLA_TOK_ECHOSTREAM_, listO(4, SYM_READ_STELLA_BYTE_ARRAY_NTH, SYM_READ_STELLA_TOK_BUFFER_, listO(3, SYM_READ_STELLA_1_, SYM_READ_STELLA_TOK_CURSOR_, NIL), NIL), NIL), NIL), NIL) : NIL))->concatenate(NIL, 0))), savestreamstatetree->concatenate(NIL, 0)));
  }
}

const char* unescapeTokenString(const char* token, char escapechar, boolean upcaseP) {
  { int nofescapes = 0;
    int cursor = 0;
    int cursor2 = 0;
    int size = strlen(token);
    char* result = NULL;
    boolean escapeP = false;

    while (cursor < size) {
      if (token[cursor] == escapechar) {
        nofescapes = nofescapes + 1;
        cursor = cursor + 1;
      }
      cursor = cursor + 1;
    }
    if (nofescapes == 0) {
      return (token);
    }
    result = makeRawMutableString(size - nofescapes);
    cursor = 0;
    while (cursor < size) {
      if ((token[cursor] == escapechar) &&
          (!escapeP)) {
        escapeP = true;
      }
      else if (upcaseP &&
          (!escapeP)) {
        result[cursor2] = (oCHARACTER_UPCASE_TABLEo[((int)(unsigned char) (token[cursor]))]);
        cursor2 = cursor2 + 1;
      }
      else {
        result[cursor2] = (token[cursor]);
        escapeP = false;
        cursor2 = cursor2 + 1;
      }
      cursor = cursor + 1;
    }
    return (result);
  }
}

StreamTokenizer* newStreamTokenizer(InputStream* stream, TokenizerTable* table) {
  { StreamTokenizer* self = NULL;

    self = new StreamTokenizer();
    self->stream = stream;
    self->table = table;
    self->firstIterationP = true;
    self->value = NULL;
    return (self);
  }
}

Surrogate* StreamTokenizer::primaryType() {
  { StreamTokenizer* self = this;

    return (SGT_READ_STELLA_STREAM_TOKENIZER);
  }
}

Object* accessStreamTokenizerSlotValue(StreamTokenizer* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_READ_STELLA_STREAM) {
    if (setvalueP) {
      self->stream = ((InputStream*)(value));
    }
    else {
      value = self->stream;
    }
  }
  else if (slotname == SYM_READ_STELLA_TABLE) {
    if (setvalueP) {
      self->table = ((TokenizerTable*)(value));
    }
    else {
      value = self->table;
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

boolean StreamTokenizer::nextP() {
  { StreamTokenizer* self = this;

    { TokenizerTable* tok_table_ = self->table;
      const char* tok_transitions_ = tok_table_->transitions;
      Object** tok_statenames_ = tok_table_->stateNames->theArray;
      int tok_tokenstart_ = -1;
      boolean tok_endoftokensP_ = false;
      InputStream* tok_inputstream_ = self->stream;
      OutputStream* tok_echostream_ = tok_inputstream_->echoStream;
      TokenizerStreamState* tok_streamstate_ = ((!((boolean)(tok_inputstream_->tokenizerState))) ? (tok_inputstream_->tokenizerState = newTokenizerStreamState()) : tok_inputstream_->tokenizerState);
      char* tok_buffer_ = tok_streamstate_->buffer;
      int tok_size_ = tok_streamstate_->bufferSize;
      int tok_state_ = tok_streamstate_->getSavedState(tok_table_);
      int tok_nextstate_ = tok_state_;
      int tok_cursor_ = tok_streamstate_->cursor;
      int tok_end_ = tok_streamstate_->end;
      int tok_checkpoint_ = ((tok_cursor_ <= tok_end_) ? tok_end_ : tok_size_);

      {
        tok_statenames_ = tok_statenames_;
        tok_endoftokensP_ = tok_endoftokensP_;
      }
      {
        tok_tokenstart_ = -1;
        for (;;) {
          if (tok_cursor_ == tok_checkpoint_) {
            if (tok_cursor_ == tok_end_) {
              tok_streamstate_->cursor = tok_cursor_;
              tok_endoftokensP_ = readIntoTokenizerBuffer(tok_inputstream_, tok_streamstate_, tok_tokenstart_);
              tok_buffer_ = tok_streamstate_->buffer;
              tok_size_ = tok_streamstate_->bufferSize;
              tok_cursor_ = integerMod(tok_streamstate_->cursor, tok_size_);
              tok_end_ = tok_streamstate_->end;
              if (tok_endoftokensP_) {
                tok_checkpoint_ = tok_cursor_;
                if (tok_nextstate_ == -1) {
                }
                else if (coerceWrappedBooleanToBoolean(((BooleanWrapper*)((tok_table_->legalEofStates->theArray)[tok_state_])))) {
                  tok_nextstate_ = -1;
                  if (!(tok_tokenstart_ == -1)) {
                    tok_endoftokensP_ = false;
                  }
                }
                else {
                  tok_endoftokensP_ = false;
                  tok_state_ = 0;
                  tok_nextstate_ = -1;
                }
                break;
              }
              if (tok_cursor_ >= tok_end_) {
                tok_checkpoint_ = tok_size_;
              }
              else {
                tok_checkpoint_ = tok_end_;
              }
            }
            else {
              tok_checkpoint_ = tok_end_;
              tok_cursor_ = 0;
            }
          }
          tok_nextstate_ = (int)(unsigned char) (tok_buffer_[tok_cursor_]);
          tok_nextstate_ = (int)(unsigned char) (tok_transitions_[((((tok_state_ << 8)) | tok_nextstate_))]);
          if ((tok_nextstate_ & 128) == 0) {
            tok_state_ = tok_nextstate_;
            tok_cursor_ = tok_cursor_ + 1;
          }
          else if (tok_tokenstart_ == -1) {
            if ((tok_nextstate_ & 64) == 0) {
              tok_tokenstart_ = tok_cursor_;
            }
            tok_state_ = (tok_nextstate_ & 63);
            tok_cursor_ = tok_cursor_ + 1;
          }
          else {
            break;
          }
          if (((boolean)(tok_echostream_))) {
            *(tok_echostream_->nativeStream) << tok_buffer_[(tok_cursor_ - 1)];
          }
        }
        if (((boolean)(tok_streamstate_))) {
          tok_streamstate_->cursor = tok_cursor_;
          tok_streamstate_->table = tok_table_;
          tok_streamstate_->state = tok_state_;
        }
      }
      if (tok_endoftokensP_) {
        self->value = NULL;
      }
      else {
        { TokenizerToken* self001 = newTokenizerToken();

          self001->type = ((Keyword*)(((GeneralizedSymbol*)(tok_statenames_[tok_state_]))));
          self001->content = getTokenTextInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, false);
          self->value = self001;
        }
      }
    }
    return (((boolean)(((TokenizerToken*)(self->value)))));
  }
}

Cons* oSTELLA_TOKENIZER_TABLE_DEFINITIONo = NULL;

TokenizerTable* oSTELLA_TOKENIZER_TABLEo = NULL;

Vector* oSTELLA_LOGICAL_STATE_NAMESo = NULL;

PropertyList* oSTELLA_LOGICAL_STATE_NAMES_TABLEo = NULL;

Object* withStellaTokenizer(Object* input, Cons* body) {
  return (listO(4, SYM_READ_STELLA_WITH_TOKENIZER, SYM_READ_STELLA_oSTELLA_TOKENIZER_TABLEo, input, cons(listO(3, SYM_READ_STELLA_LET, listO(3, listO(3, SYM_READ_STELLA_TOK_STELLALOGICALSTATENAMES_, listO(3, SYM_READ_STELLA_THE_ARRAY, SYM_READ_STELLA_oSTELLA_LOGICAL_STATE_NAMESo, NIL), NIL), listO(4, SYM_READ_STELLA_TOK_STELLALOGICALSTATENAME_, SYM_READ_STELLA_KEYWORD, SYM_READ_STELLA_NULL, NIL), NIL), body->concatenate(NIL, 0)), NIL)));
}

Object* getNextStellaToken(Cons* options) {
  return (listO(4, SYM_READ_STELLA_PROGN, cons(SYM_READ_STELLA_GET_NEXT_TOKEN, options->concatenate(NIL, 0)), listO(4, SYM_READ_STELLA_SETQ, SYM_READ_STELLA_TOK_STELLALOGICALSTATENAME_, listO(4, SYM_READ_STELLA_NTH, SYM_READ_STELLA_TOK_STELLALOGICALSTATENAMES_, SYM_READ_STELLA_TOK_STATE_, NIL), NIL), NIL));
}

Object* getStellaTokenType() {
  return (SYM_READ_STELLA_TOK_STELLALOGICALSTATENAME_);
}

Object* getQualifiedSymbolSeparatorPosition(Cons* escapemode) {
  { Object* escape = escapemode->value;

    if (!((boolean)(escape))) {
      escape = KWD_READ_NONE;
    }
    return (listO(7, SYM_READ_STELLA_GET_QUALIFIED_SYMBOL_SEPARATOR_POSITION_INTERNAL, SYM_READ_STELLA_TOK_BUFFER_, SYM_READ_STELLA_TOK_TOKENSTART_, SYM_READ_STELLA_TOK_CURSOR_, SYM_READ_STELLA_TOK_SIZE_, escape, NIL));
  }
}

int getQualifiedSymbolSeparatorPositionInternal(char* buffer, int tokenstart, int tokenend, int size, Keyword* escapemode) {
  { int cursor = tokenend - 1;
    int separatorposition = 0;
    int nofescapes = 0;
    boolean fullyescapedP = escapemode == KWD_READ_FULLY_ESCAPED;
    char targetchar = (fullyescapedP ? '|' : MODULE_SEPARATOR_CHARACTER);

    for (;;) {
      while (cursor >= 0) {
        if (buffer[cursor] == targetchar) {
          separatorposition = cursor;
          cursor = cursor - 1;
          if (cursor < 0) {
            cursor = size - 1;
          }
          nofescapes = 0;
          for (;;) {
            while ((cursor >= 0) &&
                (buffer[cursor] == '\\')) {
              nofescapes = nofescapes + 1;
              cursor = cursor - 1;
            }
            if ((cursor < 0) &&
                (buffer[0] == '\\')) {
              cursor = size - 1;
            }
            else {
              break;
            }
          }
          if (!(nofescapes % 2)) {
            if (fullyescapedP) {
              separatorposition = separatorposition - 1;
              if (separatorposition < 0) {
                separatorposition = separatorposition + size;
              }
              if (!(buffer[separatorposition] == MODULE_SEPARATOR_CHARACTER)) {
                separatorposition = separatorposition - 1;
              }
            }
            separatorposition = separatorposition - tokenstart;
            if (separatorposition < 0) {
              return (separatorposition + size);
            }
            else {
              return (separatorposition);
            }
          }
        }
        else {
          cursor = cursor - 1;
        }
      }
      cursor = size - 1;
    }
  }
}

Object* getTokenInteger() {
  // User-level macro to access the most recently parsed token as an integer.
  // This assumes correct signed integer syntax and only checks for overflows.
  if (!insideWithTokenizerP()) {
    { 
      BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
      signalTranslationError();
      if (!(suppressWarningsP())) {
        printErrorContext(">> ERROR: ", STANDARD_ERROR);
        *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Encountered `get-token-integer' outside of `with-tokenizer' macro." << "." << std::endl;
      }
    }
    return (cons(SYM_READ_STELLA_GET_TOKEN_INTEGER, NIL));
  }
  return (listO(6, SYM_READ_STELLA_GET_TOKEN_INTEGER_INTERNAL, SYM_READ_STELLA_TOK_BUFFER_, SYM_READ_STELLA_TOK_TOKENSTART_, SYM_READ_STELLA_TOK_CURSOR_, SYM_READ_STELLA_TOK_SIZE_, NIL));
}

int oGET_TOKEN_INTEGER_CHECKPOINTo = NULL_INTEGER;

int getTokenIntegerInternal(char* buffer, int start, int end, int size) {
  { long long int result = getTokenLongIntegerInternal(buffer, start, end, size);

    if ((result > MOST_POSITIVE_INTEGER) ||
        (result < MOST_NEGATIVE_INTEGER)) {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "get-token-integer: integer overflow: " << "`" << result << "'";
        throw *newStellaException(stream000->theStringReader());
      }
    }
    return (((int)(result)));
  }
}

Object* getTokenLongInteger() {
  // User-level macro to access the most recently parsed token as a long integer.
  // This assumes correct signed long-integer syntax and only checks for overflows.
  if (!insideWithTokenizerP()) {
    { 
      BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
      signalTranslationError();
      if (!(suppressWarningsP())) {
        printErrorContext(">> ERROR: ", STANDARD_ERROR);
        *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Encountered `get-token-long-integer' outside of `with-tokenizer' macro." << "." << std::endl;
      }
    }
    return (cons(SYM_READ_STELLA_GET_TOKEN_LONG_INTEGER, NIL));
  }
  return (listO(6, SYM_READ_STELLA_GET_TOKEN_LONG_INTEGER_INTERNAL, SYM_READ_STELLA_TOK_BUFFER_, SYM_READ_STELLA_TOK_TOKENSTART_, SYM_READ_STELLA_TOK_CURSOR_, SYM_READ_STELLA_TOK_SIZE_, NIL));
}

long long int oGET_TOKEN_LONG_INTEGER_CHECKPOINTo = NULL_LONG_INTEGER;

long long int getTokenLongIntegerInternal(char* buffer, int start, int end, int size) {
  { int length = end - start;
    int auxend = end;
    long long int result = 0l;
    boolean negativeP = false;
    int digit = 0;

    if (length < 0) {
      length = length + size;
      auxend = size;
    }
    switch (buffer[start]) {
      case '+': 
        start = start + 1;
        break;
      case '-': 
        start = start + 1;
        negativeP = true;
        break;
      default:
        break;
    }
    for (;;) {
      while (start < auxend) {
        digit = (int)(unsigned char) (buffer[start]) - (int)(unsigned char) '0';
        if ((result >= oGET_TOKEN_LONG_INTEGER_CHECKPOINTo) &&
            (((MOST_POSITIVE_LONG_INTEGER - digit) / (10l)) < result)) {
          throw *newStellaException("get-token-long-integer: long-integer overflow");
        }
        result = (result * 10) + digit;
        start = start + 1;
      }
      if (auxend == end) {
        break;
      }
      start = 0;
      auxend = end;
    }
    if (negativeP) {
      return (0 - result);
    }
    else {
      return (result);
    }
  }
}

Object* getTokenFloat() {
  // User-level macro to access the most recently parsed token as a float.
  // This assumes correct signed float syntax and only checks for overflows.
  // The main benefit for this is that it doesn't generate strings and wrappers.
  // Float parsing and conversion is generally hairy and we are probably not
  // covering all special cases here; but we are fast :-)
  if (!insideWithTokenizerP()) {
    { 
      BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
      signalTranslationError();
      if (!(suppressWarningsP())) {
        printErrorContext(">> ERROR: ", STANDARD_ERROR);
        *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Encountered `get-token-float' outside of `with-tokenizer' macro." << "." << std::endl;
      }
    }
    return (cons(SYM_READ_STELLA_GET_TOKEN_FLOAT, NIL));
  }
  return (listO(6, SYM_READ_STELLA_GET_TOKEN_FLOAT_INTERNAL, SYM_READ_STELLA_TOK_BUFFER_, SYM_READ_STELLA_TOK_TOKENSTART_, SYM_READ_STELLA_TOK_CURSOR_, SYM_READ_STELLA_TOK_SIZE_, NIL));
}

double getTokenFloatInternal(char* buffer, int start, int end, int size) {
  { int length = end - start;
    int auxend = end;
    long long int mantissa = 0l;
    int exponent = 0;
    double mantissasign = 1.0;
    double exponentsign = 1.0;
    boolean exponentP = false;
    boolean decimalsP = false;
    int decimals = 0;
    char ch = NULL_CHARACTER;
    int digit = 0;
    double result = 0.0;

    if (length < 0) {
      length = length + size;
      auxend = size;
    }
    for (;;) {
      while (start < auxend) {
        ch = buffer[start];
        switch (ch) {
          case '-': 
            if (exponentP) {
              exponentsign = -1.0;
            }
            else {
              mantissasign = -1.0;
            }
            break;
          case '+': 
            break;
          case '.': 
            decimalsP = true;
            break;
          case 'e': 
          case 'E': 
            exponentP = true;
            break;
          default:
            digit = (int)(unsigned char) ch - (int)(unsigned char) '0';
            if (exponentP) {
              exponent = (exponent * 10) + digit;
            }
            else {
              if (decimalsP) {
                decimals = decimals + 1;
              }
              mantissa = (mantissa * 10) + digit;
            }
            break;
        }
        start = start + 1;
      }
      if (auxend == end) {
        break;
      }
      start = 0;
      auxend = end;
    }
    result = ((double)(mantissa));
    exponent = ((int)((exponent * exponentsign) - decimals));
    if (!(exponent == 0)) {
      result = result * ::pow((10.0),(((double)(exponent))));
    }
    return (result * mantissasign);
  }
}

StellaToken* newStellaToken() {
  { StellaToken* self = NULL;

    self = new StellaToken();
    self->content = NULL;
    self->type = NULL;
    self->next = NULL;
    self->escapeMode = NULL;
    self->module = NULL;
    self->logicalTokenType = NULL;
    return (self);
  }
}

Surrogate* StellaToken::primaryType() {
  { StellaToken* self = this;

    return (SGT_READ_STELLA_STELLA_TOKEN);
  }
}

Object* accessStellaTokenSlotValue(StellaToken* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_READ_STELLA_LOGICAL_TOKEN_TYPE) {
    if (setvalueP) {
      self->logicalTokenType = ((Keyword*)(value));
    }
    else {
      value = self->logicalTokenType;
    }
  }
  else if (slotname == SYM_READ_STELLA_MODULE) {
    if (setvalueP) {
      self->module = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->module);
    }
  }
  else if (slotname == SYM_READ_STELLA_ESCAPE_MODE) {
    if (setvalueP) {
      self->escapeMode = ((Keyword*)(value));
    }
    else {
      value = self->escapeMode;
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

StellaToken* tokenizeSExpression(InputStream* stream, StellaToken* tokenlist) {
  { boolean upcaseP = !oMODULEo->caseSensitiveP;
    int parenbalance = 0;
    boolean endoffileP = true;
    boolean skipclosingquoteP = false;
    StellaToken* tokencursor = tokenlist;

    if (!((boolean)(tokenlist))) {
      tokenlist = newStellaToken();
      tokencursor = tokenlist;
    }
    { TokenizerTable* tok_table_ = oSTELLA_TOKENIZER_TABLEo;
      const char* tok_transitions_ = tok_table_->transitions;
      Object** tok_statenames_ = tok_table_->stateNames->theArray;
      int tok_tokenstart_ = -1;
      boolean tok_endoftokensP_ = false;
      InputStream* tok_inputstream_ = stream;
      OutputStream* tok_echostream_ = tok_inputstream_->echoStream;
      TokenizerStreamState* tok_streamstate_ = ((!((boolean)(tok_inputstream_->tokenizerState))) ? (tok_inputstream_->tokenizerState = newTokenizerStreamState()) : tok_inputstream_->tokenizerState);
      char* tok_buffer_ = tok_streamstate_->buffer;
      int tok_size_ = tok_streamstate_->bufferSize;
      int tok_state_ = tok_streamstate_->getSavedState(tok_table_);
      int tok_nextstate_ = tok_state_;
      int tok_cursor_ = tok_streamstate_->cursor;
      int tok_end_ = tok_streamstate_->end;
      int tok_checkpoint_ = ((tok_cursor_ <= tok_end_) ? tok_end_ : tok_size_);

      {
        tok_statenames_ = tok_statenames_;
        tok_endoftokensP_ = tok_endoftokensP_;
      }
      { Object** tok_stellalogicalstatenames_ = oSTELLA_LOGICAL_STATE_NAMESo->theArray;
        Keyword* tok_stellalogicalstatename_ = NULL;

        for (;;) {
          {
            {
              tok_tokenstart_ = -1;
              for (;;) {
                if (tok_cursor_ == tok_checkpoint_) {
                  if (tok_cursor_ == tok_end_) {
                    tok_streamstate_->cursor = tok_cursor_;
                    tok_endoftokensP_ = readIntoTokenizerBuffer(tok_inputstream_, tok_streamstate_, tok_tokenstart_);
                    tok_buffer_ = tok_streamstate_->buffer;
                    tok_size_ = tok_streamstate_->bufferSize;
                    tok_cursor_ = integerMod(tok_streamstate_->cursor, tok_size_);
                    tok_end_ = tok_streamstate_->end;
                    if (tok_endoftokensP_) {
                      tok_checkpoint_ = tok_cursor_;
                      if (tok_nextstate_ == -1) {
                      }
                      else if (coerceWrappedBooleanToBoolean(((BooleanWrapper*)((tok_table_->legalEofStates->theArray)[tok_state_])))) {
                        tok_nextstate_ = -1;
                        if (!(tok_tokenstart_ == -1)) {
                          tok_endoftokensP_ = false;
                        }
                      }
                      else {
                        tok_endoftokensP_ = false;
                        tok_state_ = 0;
                        tok_nextstate_ = -1;
                      }
                      break;
                    }
                    if (tok_cursor_ >= tok_end_) {
                      tok_checkpoint_ = tok_size_;
                    }
                    else {
                      tok_checkpoint_ = tok_end_;
                    }
                  }
                  else {
                    tok_checkpoint_ = tok_end_;
                    tok_cursor_ = 0;
                  }
                }
                tok_nextstate_ = (int)(unsigned char) (tok_buffer_[tok_cursor_]);
                tok_nextstate_ = (int)(unsigned char) (tok_transitions_[((((tok_state_ << 8)) | tok_nextstate_))]);
                if ((tok_nextstate_ & 128) == 0) {
                  tok_state_ = tok_nextstate_;
                  tok_cursor_ = tok_cursor_ + 1;
                }
                else if (tok_tokenstart_ == -1) {
                  if ((tok_nextstate_ & 64) == 0) {
                    tok_tokenstart_ = tok_cursor_;
                  }
                  tok_state_ = (tok_nextstate_ & 63);
                  tok_cursor_ = tok_cursor_ + 1;
                }
                else {
                  break;
                }
                if (((boolean)(tok_echostream_))) {
                  *(tok_echostream_->nativeStream) << tok_buffer_[(tok_cursor_ - 1)];
                }
              }
            }
            tok_stellalogicalstatename_ = ((Keyword*)(tok_stellalogicalstatenames_[tok_state_]));
          }
          if (tok_endoftokensP_) {
            if (parenbalance == 0) {
              break;
            }
            if (((boolean)(tok_streamstate_))) {
              tok_streamstate_->cursor = tok_cursor_;
              tok_streamstate_->table = tok_table_;
              tok_streamstate_->state = tok_state_;
            }
            throw *newReadException("Expression ended prematurely");
          }
          endoffileP = false;
          if (!(skipclosingquoteP)) {
            tokencursor->type = ((Keyword*)(((GeneralizedSymbol*)(tok_statenames_[tok_state_]))));
            tokencursor->logicalTokenType = tok_stellalogicalstatename_;
            tokencursor->module = NULL;
            tokencursor->escapeMode = NULL;
          }
          skipclosingquoteP = false;
          if (tok_stellalogicalstatename_ == KWD_READ_OPEN_PAREN) {
            parenbalance = parenbalance + 1;
            tokencursor->content = "(";
          }
          else if (tok_stellalogicalstatename_ == KWD_READ_CLOSE_PAREN) {
            parenbalance = parenbalance - 1;
            tokencursor->content = ")";
            if (parenbalance < 0) {
              if (((boolean)(tok_streamstate_))) {
                tok_streamstate_->cursor = tok_cursor_;
                tok_streamstate_->table = tok_table_;
                tok_streamstate_->state = tok_state_;
              }
              throw *newReadException("Extra right parenthesis encountered");
            }
          }
          else if (tok_stellalogicalstatename_ == KWD_READ_SYMBOL) {
            { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tok_statenames_[tok_state_]));

              if (testValue000 == KWD_READ_SYMBOL) {
                tokencursor->content = getTokenTextInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, upcaseP);
              }
              else if (testValue000 == KWD_READ_QUALIFIED_SYMBOL) {
                { int separatorpos = getQualifiedSymbolSeparatorPositionInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, KWD_READ_NONE);

                  tokencursor->content = getTokenTextInternal(tok_buffer_, tok_tokenstart_ + separatorpos + 1, tok_cursor_, tok_size_, upcaseP);
                  tokencursor->module = ((separatorpos == 0) ? "ROOT-MODULE" : getTokenTextInternal(tok_buffer_, tok_tokenstart_, ((separatorpos < 0) ? (tok_cursor_ + separatorpos) : (tok_tokenstart_ + separatorpos)), tok_size_, true));
                }
              }
              else if (testValue000 == KWD_READ_FULLY_ESCAPED_SYMBOL) {
                tokencursor->content = unescapeTokenString(getTokenTextInternal(tok_buffer_, tok_tokenstart_ + 1, tok_cursor_, tok_size_, false), '\\', false);
                tokencursor->escapeMode = KWD_READ_FULL;
                skipclosingquoteP = true;
              }
              else if (testValue000 == KWD_READ_QUALIFIED_FULLY_ESCAPED_SYMBOL) {
                { int separatorpos = getQualifiedSymbolSeparatorPositionInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, KWD_READ_FULLY_ESCAPED);

                  tokencursor->content = unescapeTokenString(getTokenTextInternal(tok_buffer_, tok_tokenstart_ + separatorpos + 2, tok_cursor_, tok_size_, false), '\\', false);
                  tokencursor->module = ((separatorpos == 0) ? "ROOT-MODULE" : getTokenTextInternal(tok_buffer_, tok_tokenstart_, ((separatorpos < 0) ? (tok_cursor_ + separatorpos) : (tok_tokenstart_ + separatorpos)), tok_size_, true));
                  tokencursor->escapeMode = KWD_READ_FULL;
                }
                skipclosingquoteP = true;
              }
              else if (testValue000 == KWD_READ_ESCAPED_SYMBOL) {
                tokencursor->content = unescapeTokenString(getTokenTextInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, false), '\\', upcaseP);
                tokencursor->escapeMode = KWD_READ_PARTIAL;
              }
              else if (testValue000 == KWD_READ_QUALIFIED_ESCAPED_SYMBOL) {
                { int separatorpos = getQualifiedSymbolSeparatorPositionInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, KWD_READ_ESCAPED);

                  tokencursor->content = unescapeTokenString(getTokenTextInternal(tok_buffer_, tok_tokenstart_ + separatorpos + 1, tok_cursor_, tok_size_, false), '\\', upcaseP);
                  tokencursor->module = ((separatorpos == 0) ? "ROOT-MODULE" : getTokenTextInternal(tok_buffer_, tok_tokenstart_, ((separatorpos < 0) ? (tok_cursor_ + separatorpos) : (tok_tokenstart_ + separatorpos)), tok_size_, true));
                  tokencursor->escapeMode = KWD_READ_PARTIAL;
                }
              }
              else if (testValue000 == KWD_READ_CL_SYMBOL) {
                tokencursor->content = getTokenTextInternal(tok_buffer_, tok_tokenstart_ + 3, tok_cursor_, tok_size_, true);
                tokencursor->module = "/COMMON-LISP";
              }
              else {
                { OutputStringStream* stream000 = newOutputStringStream();

                  *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
                  throw *newStellaException(stream000->theStringReader());
                }
              }
            }
          }
          else if (tok_stellalogicalstatename_ == KWD_READ_SURROGATE) {
            { GeneralizedSymbol* testValue001 = ((GeneralizedSymbol*)(tok_statenames_[tok_state_]));

              if (testValue001 == KWD_READ_SURROGATE) {
                tokencursor->content = getTokenTextInternal(tok_buffer_, tok_tokenstart_ + 1, tok_cursor_, tok_size_, upcaseP);
              }
              else if (testValue001 == KWD_READ_QUALIFIED_SURROGATE) {
                { int separatorpos = getQualifiedSymbolSeparatorPositionInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, KWD_READ_NONE);

                  tokencursor->content = getTokenTextInternal(tok_buffer_, tok_tokenstart_ + separatorpos + 2, tok_cursor_, tok_size_, upcaseP);
                  tokencursor->module = ((separatorpos == 0) ? "ROOT-MODULE" : getTokenTextInternal(tok_buffer_, tok_tokenstart_, ((separatorpos < 0) ? (tok_cursor_ + separatorpos) : (tok_tokenstart_ + separatorpos)), tok_size_, true));
                }
              }
              else if (testValue001 == KWD_READ_FULLY_ESCAPED_SURROGATE) {
                tokencursor->content = unescapeTokenString(getTokenTextInternal(tok_buffer_, tok_tokenstart_ + 2, tok_cursor_, tok_size_, false), '\\', false);
                tokencursor->escapeMode = KWD_READ_FULL;
                skipclosingquoteP = true;
              }
              else if (testValue001 == KWD_READ_QUALIFIED_FULLY_ESCAPED_SURROGATE) {
                { int separatorpos = getQualifiedSymbolSeparatorPositionInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, KWD_READ_FULLY_ESCAPED);

                  tokencursor->content = unescapeTokenString(getTokenTextInternal(tok_buffer_, tok_tokenstart_ + separatorpos + 3, tok_cursor_, tok_size_, false), '\\', false);
                  tokencursor->module = ((separatorpos == 0) ? "ROOT-MODULE" : getTokenTextInternal(tok_buffer_, tok_tokenstart_, ((separatorpos < 0) ? (tok_cursor_ + separatorpos) : (tok_tokenstart_ + separatorpos)), tok_size_, true));
                  tokencursor->escapeMode = KWD_READ_FULL;
                }
                skipclosingquoteP = true;
              }
              else if (testValue001 == KWD_READ_ESCAPED_SURROGATE) {
                tokencursor->content = unescapeTokenString(getTokenTextInternal(tok_buffer_, tok_tokenstart_ + 1, tok_cursor_, tok_size_, false), '\\', upcaseP);
                tokencursor->escapeMode = KWD_READ_PARTIAL;
              }
              else if (testValue001 == KWD_READ_QUALIFIED_ESCAPED_SURROGATE) {
                { int separatorpos = getQualifiedSymbolSeparatorPositionInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, KWD_READ_ESCAPED);

                  tokencursor->content = unescapeTokenString(getTokenTextInternal(tok_buffer_, tok_tokenstart_ + separatorpos + 2, tok_cursor_, tok_size_, false), '\\', upcaseP);
                  tokencursor->module = ((separatorpos == 0) ? "ROOT-MODULE" : getTokenTextInternal(tok_buffer_, tok_tokenstart_, ((separatorpos < 0) ? (tok_cursor_ + separatorpos) : (tok_tokenstart_ + separatorpos)), tok_size_, true));
                  tokencursor->escapeMode = KWD_READ_PARTIAL;
                }
              }
              else {
                { OutputStringStream* stream001 = newOutputStringStream();

                  *(stream001->nativeStream) << "`" << testValue001 << "'" << " is not a valid case option";
                  throw *newStellaException(stream001->theStringReader());
                }
              }
            }
          }
          else if (tok_stellalogicalstatename_ == KWD_READ_KEYWORD) {
            { GeneralizedSymbol* testValue002 = ((GeneralizedSymbol*)(tok_statenames_[tok_state_]));

              if (testValue002 == KWD_READ_KEYWORD) {
                tokencursor->content = getTokenTextInternal(tok_buffer_, tok_tokenstart_ + 1, tok_cursor_, tok_size_, true);
              }
              else if (testValue002 == KWD_READ_FULLY_ESCAPED_KEYWORD) {
                tokencursor->content = unescapeTokenString(getTokenTextInternal(tok_buffer_, tok_tokenstart_ + 2, tok_cursor_, tok_size_, false), '\\', false);
                tokencursor->escapeMode = KWD_READ_FULL;
                skipclosingquoteP = true;
              }
              else if (testValue002 == KWD_READ_ESCAPED_KEYWORD) {
                tokencursor->content = unescapeTokenString(getTokenTextInternal(tok_buffer_, tok_tokenstart_ + 1, tok_cursor_, tok_size_, false), '\\', true);
                tokencursor->escapeMode = KWD_READ_PARTIAL;
              }
              else {
                { OutputStringStream* stream002 = newOutputStringStream();

                  *(stream002->nativeStream) << "`" << testValue002 << "'" << " is not a valid case option";
                  throw *newStellaException(stream002->theStringReader());
                }
              }
            }
          }
          else if (tok_stellalogicalstatename_ == KWD_READ_STRING) {
            tokencursor->content = getTokenTextInternal(tok_buffer_, tok_tokenstart_ + 1, tok_cursor_, tok_size_, false);
            { GeneralizedSymbol* testValue003 = ((GeneralizedSymbol*)(tok_statenames_[tok_state_]));

              if (testValue003 == KWD_READ_STRING) {
              }
              else if (testValue003 == KWD_READ_ESCAPED_STRING) {
                tokencursor->content = unescapeTokenString(tokencursor->content, '\\', false);
                tokencursor->escapeMode = KWD_READ_PARTIAL;
              }
              else {
                { OutputStringStream* stream003 = newOutputStringStream();

                  *(stream003->nativeStream) << "`" << testValue003 << "'" << " is not a valid case option";
                  throw *newStellaException(stream003->theStringReader());
                }
              }
            }
            skipclosingquoteP = true;
          }
          else if ((tok_stellalogicalstatename_ == KWD_READ_INTEGER) ||
              (tok_stellalogicalstatename_ == KWD_READ_FLOAT)) {
            tokencursor->content = getTokenTextInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, false);
          }
          else if (tok_stellalogicalstatename_ == KWD_READ_CHARACTER) {
            { const char* name = getTokenTextInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, false);

              if (strlen(name) > 1) {
                name = stringUpcase(name);
              }
              tokencursor->content = name;
            }
          }
          else if ((tok_stellalogicalstatename_ == KWD_READ_SINGLE_QUOTE) ||
              ((tok_stellalogicalstatename_ == KWD_READ_BACK_QUOTE) ||
               ((tok_stellalogicalstatename_ == KWD_READ_COMMA) ||
                (tok_stellalogicalstatename_ == KWD_READ_COMMA_SPLICE)))) {
            tokencursor->content = getTokenTextInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, false);
            if (!((boolean)(((StellaToken*)(tokencursor->next))))) {
              tokencursor->next = newStellaToken();
            }
            tokencursor = ((StellaToken*)(tokencursor->next));
            continue;
          }
          else if (tok_stellalogicalstatename_ == KWD_READ_QUALIFIED_NAME) {
            { const char* token = getTokenTextInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, true);
              int length = strlen(token);

              if ((length >= 1) &&
                  ((token[(length - 1)] == '/') &&
                   ((length == 1) ||
                    (token[(length - 2)] == '/')))) {
                tokencursor->content = "/";
                tokencursor->type = KWD_READ_SYMBOL;
                tokencursor->logicalTokenType = KWD_READ_SYMBOL;
                if (length > 1) {
                  tokencursor->module = stringSubsequence(token, 0, length - 2);
                  tokencursor->type = KWD_READ_QUALIFIED_SYMBOL;
                }
              }
              else {
                tokencursor->content = token;
              }
            }
          }
          else if (tok_stellalogicalstatename_ == KWD_READ_CLOSE_BALANCED_QUOTE) {
          }
          else if (tok_stellalogicalstatename_ == KWD_READ_ERROR) {
            if (((boolean)(tok_streamstate_))) {
              tok_streamstate_->cursor = tok_cursor_;
              tok_streamstate_->table = tok_table_;
              tok_streamstate_->state = tok_state_;
            }
            { OutputStringStream* stream004 = newOutputStringStream();

              *(stream004->nativeStream) << "Illegal read syntax: " << "`" << getTokenTextInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, false) << "'";
              throw *newReadException(stream004->theStringReader());
            }
          }
          else {
            if (((boolean)(tok_streamstate_))) {
              tok_streamstate_->cursor = tok_cursor_;
              tok_streamstate_->table = tok_table_;
              tok_streamstate_->state = tok_state_;
            }
            { OutputStringStream* stream005 = newOutputStringStream();

              *(stream005->nativeStream) << "Illegal read syntax: " << "`" << getTokenTextInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, false) << "'" << " in state " << "`" << ((GeneralizedSymbol*)(tok_statenames_[tok_state_])) << "'";
              throw *newReadException(stream005->theStringReader());
            }
          }
          if (!(skipclosingquoteP)) {
            if (!((boolean)(((StellaToken*)(tokencursor->next))))) {
              tokencursor->next = newStellaToken();
            }
            tokencursor = ((StellaToken*)(tokencursor->next));
            if (parenbalance == 0) {
              break;
            }
          }
        }
        tokencursor->type = NULL;
        tokencursor->logicalTokenType = NULL;
        if (((boolean)(tok_streamstate_))) {
          tok_streamstate_->cursor = tok_cursor_;
          tok_streamstate_->table = tok_table_;
          tok_streamstate_->state = tok_state_;
        }
        if (endoffileP) {
          return (NULL);
        }
        else {
          return (tokenlist);
        }
      }
    }
  }
}

const char* parseStellaName(const char* name, boolean enablecaseconversionP, const char*& _Return1, Keyword*& _Return2) {
  // Parse the printed representation `name' of a STELLA symbol, surrogate or
  // keyword and return its symbol name, module name and type (which is either
  // :SYMBOL, :SURROGATE or :KEYWORD).  `name' can be qualified and must use the
  // exact same syntax and escape characters that would be used if it were to be
  // read by `read-s-expression-from-string' (or `unstringify').  If
  // `enableCaseConversion?' is TRUE, the returned symbol name will be upcased if
  // the current module is case-insensitive; otherwise, it will be returned as is.
  // Raises a read exception if `name' does not represent a symbol.
  // This function is available primarily for efficiency, since it is about
  // 10-15 times faster than `unstringify'.
  { const char* symbolname = NULL;
    const char* modulename = NULL;
    Keyword* symboltype = NULL;
    int separatorpos = 0;
    boolean upcaseP = enablecaseconversionP &&
        (!oMODULEo->caseSensitiveP);

    { TokenizerTable* tok_table_ = oSTELLA_TOKENIZER_TABLEo;
      const char* tok_transitions_ = tok_table_->transitions;
      Object** tok_statenames_ = tok_table_->stateNames->theArray;
      int tok_tokenstart_ = -1;
      boolean tok_endoftokensP_ = false;
      TokenizerStreamState* tok_streamstate_ = NULL;
      char* tok_buffer_ = mutableStringCopy(name);
      int tok_state_ = 1;
      int tok_nextstate_ = tok_state_;
      int tok_cursor_ = 0;
      int tok_size_ = strlen(name);
      int tok_end_ = tok_size_;

      {
        tok_statenames_ = tok_statenames_;
        tok_endoftokensP_ = tok_endoftokensP_;
      }
      tok_streamstate_ = tok_streamstate_;
      { Object** tok_stellalogicalstatenames_ = oSTELLA_LOGICAL_STATE_NAMESo->theArray;
        Keyword* tok_stellalogicalstatename_ = NULL;

        {
          {
            tok_tokenstart_ = -1;
            for (;;) {
              if (tok_cursor_ == tok_end_) {
                if (tok_nextstate_ == -1) {
                  tok_endoftokensP_ = true;
                }
                else if (coerceWrappedBooleanToBoolean(((BooleanWrapper*)((tok_table_->legalEofStates->theArray)[tok_state_])))) {
                  tok_nextstate_ = -1;
                  if (tok_tokenstart_ == -1) {
                    tok_endoftokensP_ = true;
                  }
                }
                else {
                  tok_state_ = 0;
                  tok_nextstate_ = -1;
                }
                break;
              }
              tok_nextstate_ = (int)(unsigned char) (tok_buffer_[tok_cursor_]);
              tok_nextstate_ = (int)(unsigned char) (tok_transitions_[((((tok_state_ << 8)) | tok_nextstate_))]);
              if ((tok_nextstate_ & 128) == 0) {
                tok_state_ = tok_nextstate_;
                tok_cursor_ = tok_cursor_ + 1;
              }
              else if (tok_tokenstart_ == -1) {
                if ((tok_nextstate_ & 64) == 0) {
                  tok_tokenstart_ = tok_cursor_;
                }
                tok_state_ = (tok_nextstate_ & 63);
                tok_cursor_ = tok_cursor_ + 1;
              }
              else {
                break;
              }
            }
          }
          tok_stellalogicalstatename_ = ((Keyword*)(tok_stellalogicalstatenames_[tok_state_]));
        }
        if (tok_endoftokensP_) {
          { const char* _Return0 = NULL;

            _Return1 = NULL;
            _Return2 = NULL;
            return (_Return0);
          }
        }
        if (tok_stellalogicalstatename_ == KWD_READ_SYMBOL) {
          { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tok_statenames_[tok_state_]));

            if (testValue000 == KWD_READ_SYMBOL) {
              symbolname = getTokenTextInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, upcaseP);
            }
            else if (testValue000 == KWD_READ_QUALIFIED_SYMBOL) {
              separatorpos = getQualifiedSymbolSeparatorPositionInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, KWD_READ_NONE);
              symbolname = getTokenTextInternal(tok_buffer_, tok_tokenstart_ + separatorpos + 1, tok_cursor_, tok_size_, upcaseP);
              modulename = ((separatorpos == 0) ? "ROOT-MODULE" : getTokenTextInternal(tok_buffer_, tok_tokenstart_, ((separatorpos < 0) ? (tok_cursor_ + separatorpos) : (tok_tokenstart_ + separatorpos)), tok_size_, true));
            }
            else if (testValue000 == KWD_READ_FULLY_ESCAPED_SYMBOL) {
              symbolname = unescapeTokenString(getTokenTextInternal(tok_buffer_, tok_tokenstart_ + 1, tok_cursor_, tok_size_, false), '\\', false);
            }
            else if (testValue000 == KWD_READ_QUALIFIED_FULLY_ESCAPED_SYMBOL) {
              separatorpos = getQualifiedSymbolSeparatorPositionInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, KWD_READ_FULLY_ESCAPED);
              symbolname = unescapeTokenString(getTokenTextInternal(tok_buffer_, tok_tokenstart_ + separatorpos + 2, tok_cursor_, tok_size_, false), '\\', false);
              modulename = ((separatorpos == 0) ? "ROOT-MODULE" : getTokenTextInternal(tok_buffer_, tok_tokenstart_, ((separatorpos < 0) ? (tok_cursor_ + separatorpos) : (tok_tokenstart_ + separatorpos)), tok_size_, true));
            }
            else if (testValue000 == KWD_READ_ESCAPED_SYMBOL) {
              symbolname = unescapeTokenString(getTokenTextInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, false), '\\', upcaseP);
            }
            else if (testValue000 == KWD_READ_QUALIFIED_ESCAPED_SYMBOL) {
              separatorpos = getQualifiedSymbolSeparatorPositionInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, KWD_READ_ESCAPED);
              symbolname = unescapeTokenString(getTokenTextInternal(tok_buffer_, tok_tokenstart_ + separatorpos + 1, tok_cursor_, tok_size_, false), '\\', upcaseP);
              modulename = ((separatorpos == 0) ? "ROOT-MODULE" : getTokenTextInternal(tok_buffer_, tok_tokenstart_, ((separatorpos < 0) ? (tok_cursor_ + separatorpos) : (tok_tokenstart_ + separatorpos)), tok_size_, true));
            }
            else if (testValue000 == KWD_READ_CL_SYMBOL) {
              symbolname = getTokenTextInternal(tok_buffer_, tok_tokenstart_ + 3, tok_cursor_, tok_size_, true);
              modulename = "/COMMON-LISP";
            }
            else {
              { OutputStringStream* stream000 = newOutputStringStream();

                *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
                throw *newStellaException(stream000->theStringReader());
              }
            }
          }
        }
        else if (tok_stellalogicalstatename_ == KWD_READ_SURROGATE) {
          { GeneralizedSymbol* testValue001 = ((GeneralizedSymbol*)(tok_statenames_[tok_state_]));

            if (testValue001 == KWD_READ_SURROGATE) {
              symbolname = getTokenTextInternal(tok_buffer_, tok_tokenstart_ + 1, tok_cursor_, tok_size_, upcaseP);
            }
            else if (testValue001 == KWD_READ_QUALIFIED_SURROGATE) {
              separatorpos = getQualifiedSymbolSeparatorPositionInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, KWD_READ_NONE);
              symbolname = getTokenTextInternal(tok_buffer_, tok_tokenstart_ + separatorpos + 2, tok_cursor_, tok_size_, upcaseP);
              modulename = ((separatorpos == 0) ? "ROOT-MODULE" : getTokenTextInternal(tok_buffer_, tok_tokenstart_, ((separatorpos < 0) ? (tok_cursor_ + separatorpos) : (tok_tokenstart_ + separatorpos)), tok_size_, true));
            }
            else if (testValue001 == KWD_READ_FULLY_ESCAPED_SURROGATE) {
              symbolname = unescapeTokenString(getTokenTextInternal(tok_buffer_, tok_tokenstart_ + 2, tok_cursor_, tok_size_, false), '\\', false);
            }
            else if (testValue001 == KWD_READ_QUALIFIED_FULLY_ESCAPED_SURROGATE) {
              separatorpos = getQualifiedSymbolSeparatorPositionInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, KWD_READ_FULLY_ESCAPED);
              symbolname = unescapeTokenString(getTokenTextInternal(tok_buffer_, tok_tokenstart_ + separatorpos + 3, tok_cursor_, tok_size_, false), '\\', false);
              modulename = ((separatorpos == 0) ? "ROOT-MODULE" : getTokenTextInternal(tok_buffer_, tok_tokenstart_, ((separatorpos < 0) ? (tok_cursor_ + separatorpos) : (tok_tokenstart_ + separatorpos)), tok_size_, true));
            }
            else if (testValue001 == KWD_READ_ESCAPED_SURROGATE) {
              symbolname = unescapeTokenString(getTokenTextInternal(tok_buffer_, tok_tokenstart_ + 1, tok_cursor_, tok_size_, false), '\\', upcaseP);
            }
            else if (testValue001 == KWD_READ_QUALIFIED_ESCAPED_SURROGATE) {
              separatorpos = getQualifiedSymbolSeparatorPositionInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, KWD_READ_ESCAPED);
              symbolname = unescapeTokenString(getTokenTextInternal(tok_buffer_, tok_tokenstart_ + separatorpos + 2, tok_cursor_, tok_size_, false), '\\', upcaseP);
              modulename = ((separatorpos == 0) ? "ROOT-MODULE" : getTokenTextInternal(tok_buffer_, tok_tokenstart_, ((separatorpos < 0) ? (tok_cursor_ + separatorpos) : (tok_tokenstart_ + separatorpos)), tok_size_, true));
            }
            else {
              { OutputStringStream* stream001 = newOutputStringStream();

                *(stream001->nativeStream) << "`" << testValue001 << "'" << " is not a valid case option";
                throw *newStellaException(stream001->theStringReader());
              }
            }
          }
        }
        else if (tok_stellalogicalstatename_ == KWD_READ_KEYWORD) {
          { GeneralizedSymbol* testValue002 = ((GeneralizedSymbol*)(tok_statenames_[tok_state_]));

            if (testValue002 == KWD_READ_KEYWORD) {
              symbolname = getTokenTextInternal(tok_buffer_, tok_tokenstart_ + 1, tok_cursor_, tok_size_, true);
            }
            else if (testValue002 == KWD_READ_FULLY_ESCAPED_KEYWORD) {
              symbolname = unescapeTokenString(getTokenTextInternal(tok_buffer_, tok_tokenstart_ + 2, tok_cursor_, tok_size_, false), '\\', false);
            }
            else if (testValue002 == KWD_READ_ESCAPED_KEYWORD) {
              symbolname = unescapeTokenString(getTokenTextInternal(tok_buffer_, tok_tokenstart_ + 1, tok_cursor_, tok_size_, false), '\\', true);
            }
            else {
              { OutputStringStream* stream002 = newOutputStringStream();

                *(stream002->nativeStream) << "`" << testValue002 << "'" << " is not a valid case option";
                throw *newStellaException(stream002->theStringReader());
              }
            }
          }
        }
        else if (tok_stellalogicalstatename_ == KWD_READ_QUALIFIED_NAME) {
          { const char* token = getTokenTextInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, true);
            int length = strlen(token);

            if ((length >= 1) &&
                ((token[(length - 1)] == '/') &&
                 ((length == 1) ||
                  (token[(length - 2)] == '/')))) {
              symbolname = "/";
              tok_stellalogicalstatename_ = KWD_READ_SYMBOL;
              if (length > 1) {
                modulename = stringSubsequence(token, 0, length - 2);
              }
            }
            else {
              { OutputStringStream* stream003 = newOutputStringStream();

                *(stream003->nativeStream) << "Illegal symbol syntax: " << "`" << getTokenTextInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, false) << "'" << " in state " << "`" << ((GeneralizedSymbol*)(tok_statenames_[tok_state_])) << "'";
                throw *newReadException(stream003->theStringReader());
              }
            }
          }
        }
        else if (tok_stellalogicalstatename_ == KWD_READ_ERROR) {
          { OutputStringStream* stream004 = newOutputStringStream();

            *(stream004->nativeStream) << "Illegal read syntax: " << "`" << getTokenTextInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, false) << "'";
            throw *newReadException(stream004->theStringReader());
          }
        }
        else {
          { OutputStringStream* stream005 = newOutputStringStream();

            *(stream005->nativeStream) << "Illegal symbol syntax: " << "`" << getTokenTextInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, false) << "'" << " in state " << "`" << ((GeneralizedSymbol*)(tok_statenames_[tok_state_])) << "'";
            throw *newReadException(stream005->theStringReader());
          }
        }
        symboltype = tok_stellalogicalstatename_;
        {
          {
            tok_tokenstart_ = -1;
            for (;;) {
              if (tok_cursor_ == tok_end_) {
                if (tok_nextstate_ == -1) {
                  tok_endoftokensP_ = true;
                }
                else if (coerceWrappedBooleanToBoolean(((BooleanWrapper*)((tok_table_->legalEofStates->theArray)[tok_state_])))) {
                  tok_nextstate_ = -1;
                  if (tok_tokenstart_ == -1) {
                    tok_endoftokensP_ = true;
                  }
                }
                else {
                  tok_state_ = 0;
                  tok_nextstate_ = -1;
                }
                break;
              }
              tok_nextstate_ = (int)(unsigned char) (tok_buffer_[tok_cursor_]);
              tok_nextstate_ = (int)(unsigned char) (tok_transitions_[((((tok_state_ << 8)) | tok_nextstate_))]);
              if ((tok_nextstate_ & 128) == 0) {
                tok_state_ = tok_nextstate_;
                tok_cursor_ = tok_cursor_ + 1;
              }
              else if (tok_tokenstart_ == -1) {
                if ((tok_nextstate_ & 64) == 0) {
                  tok_tokenstart_ = tok_cursor_;
                }
                tok_state_ = (tok_nextstate_ & 63);
                tok_cursor_ = tok_cursor_ + 1;
              }
              else {
                break;
              }
            }
          }
          tok_stellalogicalstatename_ = ((Keyword*)(tok_stellalogicalstatenames_[tok_state_]));
        }
        if (tok_endoftokensP_ ||
            (((GeneralizedSymbol*)(tok_statenames_[tok_state_])) == KWD_READ_CLOSE_FULLY_ESCAPED_NAME)) {
          _Return1 = modulename;
          _Return2 = symboltype;
          return (symbolname);
        }
        else {
          { OutputStringStream* stream006 = newOutputStringStream();

            *(stream006->nativeStream) << "Garbage found after " << "`" << name << "'";
            throw *newReadException(stream006->theStringReader());
          }
        }
      }
    }
  }
}

boolean qualifiedStellaNameP(const char* name) {
  // Return TRUE if `name' is a symbol or surrogate qualified with a module
  // pathname or a module pathname ending with a `/'.  Assumes that `name'
  // is the printed representation of a STELLA symbol (potentially containing
  // escape characters).
  { TokenizerTable* tok_table_ = oSTELLA_TOKENIZER_TABLEo;
    const char* tok_transitions_ = tok_table_->transitions;
    Object** tok_statenames_ = tok_table_->stateNames->theArray;
    int tok_tokenstart_ = -1;
    boolean tok_endoftokensP_ = false;
    TokenizerStreamState* tok_streamstate_ = NULL;
    char* tok_buffer_ = mutableStringCopy(name);
    int tok_state_ = 1;
    int tok_nextstate_ = tok_state_;
    int tok_cursor_ = 0;
    int tok_size_ = strlen(name);
    int tok_end_ = tok_size_;

    {
      tok_statenames_ = tok_statenames_;
      tok_endoftokensP_ = tok_endoftokensP_;
    }
    tok_streamstate_ = tok_streamstate_;
    { Object** tok_stellalogicalstatenames_ = oSTELLA_LOGICAL_STATE_NAMESo->theArray;
      Keyword* tok_stellalogicalstatename_ = NULL;

      {
        {
          tok_tokenstart_ = -1;
          for (;;) {
            if (tok_cursor_ == tok_end_) {
              if (tok_nextstate_ == -1) {
                tok_endoftokensP_ = true;
              }
              else if (coerceWrappedBooleanToBoolean(((BooleanWrapper*)((tok_table_->legalEofStates->theArray)[tok_state_])))) {
                tok_nextstate_ = -1;
                if (tok_tokenstart_ == -1) {
                  tok_endoftokensP_ = true;
                }
              }
              else {
                tok_state_ = 0;
                tok_nextstate_ = -1;
              }
              break;
            }
            tok_nextstate_ = (int)(unsigned char) (tok_buffer_[tok_cursor_]);
            tok_nextstate_ = (int)(unsigned char) (tok_transitions_[((((tok_state_ << 8)) | tok_nextstate_))]);
            if ((tok_nextstate_ & 128) == 0) {
              tok_state_ = tok_nextstate_;
              tok_cursor_ = tok_cursor_ + 1;
            }
            else if (tok_tokenstart_ == -1) {
              if ((tok_nextstate_ & 64) == 0) {
                tok_tokenstart_ = tok_cursor_;
              }
              tok_state_ = (tok_nextstate_ & 63);
              tok_cursor_ = tok_cursor_ + 1;
            }
            else {
              break;
            }
          }
        }
        tok_stellalogicalstatename_ = ((Keyword*)(tok_stellalogicalstatenames_[tok_state_]));
      }
      if (tok_endoftokensP_) {
        return (false);
      }
      { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tok_statenames_[tok_state_]));

        if ((testValue000 == KWD_READ_QUALIFIED_SYMBOL) ||
            ((testValue000 == KWD_READ_QUALIFIED_FULLY_ESCAPED_SYMBOL) ||
             ((testValue000 == KWD_READ_QUALIFIED_ESCAPED_SYMBOL) ||
              ((testValue000 == KWD_READ_QUALIFIED_SURROGATE) ||
               ((testValue000 == KWD_READ_QUALIFIED_FULLY_ESCAPED_SURROGATE) ||
                (testValue000 == KWD_READ_QUALIFIED_ESCAPED_SURROGATE)))))) {
          return (true);
        }
        else if (testValue000 == KWD_READ_QUALIFIED_NAME) {
          return (!stringEqlP(name, "/"));
        }
        else {
          return (false);
        }
      }
    }
  }
}

int parseInteger(const char* value) {
  // Convert an integer `value' string into an integer.  Leading and trailing
  // whitespace is allowed.  Raise an error if we have illegal number syntax which makes it
  // preferable over the naive C++ stringToInteger conversion function which just returns 0.
  { TokenizerTable* tok_table_ = oSTELLA_TOKENIZER_TABLEo;
    const char* tok_transitions_ = tok_table_->transitions;
    Object** tok_statenames_ = tok_table_->stateNames->theArray;
    int tok_tokenstart_ = -1;
    boolean tok_endoftokensP_ = false;
    TokenizerStreamState* tok_streamstate_ = NULL;
    char* tok_buffer_ = mutableStringCopy(value);
    int tok_state_ = 1;
    int tok_nextstate_ = tok_state_;
    int tok_cursor_ = 0;
    int tok_size_ = strlen(value);
    int tok_end_ = tok_size_;

    {
      tok_statenames_ = tok_statenames_;
      tok_endoftokensP_ = tok_endoftokensP_;
    }
    tok_streamstate_ = tok_streamstate_;
    { Object** tok_stellalogicalstatenames_ = oSTELLA_LOGICAL_STATE_NAMESo->theArray;
      Keyword* tok_stellalogicalstatename_ = NULL;

      {
        {
          tok_tokenstart_ = -1;
          for (;;) {
            if (tok_cursor_ == tok_end_) {
              if (tok_nextstate_ == -1) {
                tok_endoftokensP_ = true;
              }
              else if (coerceWrappedBooleanToBoolean(((BooleanWrapper*)((tok_table_->legalEofStates->theArray)[tok_state_])))) {
                tok_nextstate_ = -1;
                if (tok_tokenstart_ == -1) {
                  tok_endoftokensP_ = true;
                }
              }
              else {
                tok_state_ = 0;
                tok_nextstate_ = -1;
              }
              break;
            }
            tok_nextstate_ = (int)(unsigned char) (tok_buffer_[tok_cursor_]);
            tok_nextstate_ = (int)(unsigned char) (tok_transitions_[((((tok_state_ << 8)) | tok_nextstate_))]);
            if ((tok_nextstate_ & 128) == 0) {
              tok_state_ = tok_nextstate_;
              tok_cursor_ = tok_cursor_ + 1;
            }
            else if (tok_tokenstart_ == -1) {
              if ((tok_nextstate_ & 64) == 0) {
                tok_tokenstart_ = tok_cursor_;
              }
              tok_state_ = (tok_nextstate_ & 63);
              tok_cursor_ = tok_cursor_ + 1;
            }
            else {
              break;
            }
          }
        }
        tok_stellalogicalstatename_ = ((Keyword*)(tok_stellalogicalstatenames_[tok_state_]));
      }
      if (tok_endoftokensP_) {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "There is no integer in this string: " << "`" << value << "'";
          throw *newReadException(stream000->theStringReader());
        }
      }
      if (tok_stellalogicalstatename_ == KWD_READ_INTEGER) {
        return (getTokenIntegerInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_));
      }
      else {
        { OutputStringStream* stream001 = newOutputStringStream();

          *(stream001->nativeStream) << "Illegal integer syntax: " << "`" << value << "'";
          throw *newReadException(stream001->theStringReader());
        }
      }
    }
  }
}

long long int parseLongInteger(const char* value) {
  // Convert a long integer `value' string into a long integer.  Leading and
  // trailing whitespace is allowed.  Raise an error if we have illegal number syntax which makes it
  // preferable over the naive C++ stringToInteger conversion function which just returns 0.
  { TokenizerTable* tok_table_ = oSTELLA_TOKENIZER_TABLEo;
    const char* tok_transitions_ = tok_table_->transitions;
    Object** tok_statenames_ = tok_table_->stateNames->theArray;
    int tok_tokenstart_ = -1;
    boolean tok_endoftokensP_ = false;
    TokenizerStreamState* tok_streamstate_ = NULL;
    char* tok_buffer_ = mutableStringCopy(value);
    int tok_state_ = 1;
    int tok_nextstate_ = tok_state_;
    int tok_cursor_ = 0;
    int tok_size_ = strlen(value);
    int tok_end_ = tok_size_;

    {
      tok_statenames_ = tok_statenames_;
      tok_endoftokensP_ = tok_endoftokensP_;
    }
    tok_streamstate_ = tok_streamstate_;
    { Object** tok_stellalogicalstatenames_ = oSTELLA_LOGICAL_STATE_NAMESo->theArray;
      Keyword* tok_stellalogicalstatename_ = NULL;

      {
        {
          tok_tokenstart_ = -1;
          for (;;) {
            if (tok_cursor_ == tok_end_) {
              if (tok_nextstate_ == -1) {
                tok_endoftokensP_ = true;
              }
              else if (coerceWrappedBooleanToBoolean(((BooleanWrapper*)((tok_table_->legalEofStates->theArray)[tok_state_])))) {
                tok_nextstate_ = -1;
                if (tok_tokenstart_ == -1) {
                  tok_endoftokensP_ = true;
                }
              }
              else {
                tok_state_ = 0;
                tok_nextstate_ = -1;
              }
              break;
            }
            tok_nextstate_ = (int)(unsigned char) (tok_buffer_[tok_cursor_]);
            tok_nextstate_ = (int)(unsigned char) (tok_transitions_[((((tok_state_ << 8)) | tok_nextstate_))]);
            if ((tok_nextstate_ & 128) == 0) {
              tok_state_ = tok_nextstate_;
              tok_cursor_ = tok_cursor_ + 1;
            }
            else if (tok_tokenstart_ == -1) {
              if ((tok_nextstate_ & 64) == 0) {
                tok_tokenstart_ = tok_cursor_;
              }
              tok_state_ = (tok_nextstate_ & 63);
              tok_cursor_ = tok_cursor_ + 1;
            }
            else {
              break;
            }
          }
        }
        tok_stellalogicalstatename_ = ((Keyword*)(tok_stellalogicalstatenames_[tok_state_]));
      }
      if (tok_endoftokensP_) {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "There is no integer in this string: " << "`" << value << "'";
          throw *newReadException(stream000->theStringReader());
        }
      }
      if (tok_stellalogicalstatename_ == KWD_READ_INTEGER) {
        return (getTokenLongIntegerInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_));
      }
      else {
        { OutputStringStream* stream001 = newOutputStringStream();

          *(stream001->nativeStream) << "Illegal integer syntax: " << "`" << value << "'";
          throw *newReadException(stream001->theStringReader());
        }
      }
    }
  }
}

double parseFloat(const char* value) {
  // Convert a float `value' string into a float.  Leading and trailing
  // whitespace is allowed.  Raise an error if we have illegal number syntax which makes it
  // preferable over the naive C++ stringToFloat conversion function which just returns 0.
  { TokenizerTable* tok_table_ = oSTELLA_TOKENIZER_TABLEo;
    const char* tok_transitions_ = tok_table_->transitions;
    Object** tok_statenames_ = tok_table_->stateNames->theArray;
    int tok_tokenstart_ = -1;
    boolean tok_endoftokensP_ = false;
    TokenizerStreamState* tok_streamstate_ = NULL;
    char* tok_buffer_ = mutableStringCopy(value);
    int tok_state_ = 1;
    int tok_nextstate_ = tok_state_;
    int tok_cursor_ = 0;
    int tok_size_ = strlen(value);
    int tok_end_ = tok_size_;

    {
      tok_statenames_ = tok_statenames_;
      tok_endoftokensP_ = tok_endoftokensP_;
    }
    tok_streamstate_ = tok_streamstate_;
    { Object** tok_stellalogicalstatenames_ = oSTELLA_LOGICAL_STATE_NAMESo->theArray;
      Keyword* tok_stellalogicalstatename_ = NULL;

      {
        {
          tok_tokenstart_ = -1;
          for (;;) {
            if (tok_cursor_ == tok_end_) {
              if (tok_nextstate_ == -1) {
                tok_endoftokensP_ = true;
              }
              else if (coerceWrappedBooleanToBoolean(((BooleanWrapper*)((tok_table_->legalEofStates->theArray)[tok_state_])))) {
                tok_nextstate_ = -1;
                if (tok_tokenstart_ == -1) {
                  tok_endoftokensP_ = true;
                }
              }
              else {
                tok_state_ = 0;
                tok_nextstate_ = -1;
              }
              break;
            }
            tok_nextstate_ = (int)(unsigned char) (tok_buffer_[tok_cursor_]);
            tok_nextstate_ = (int)(unsigned char) (tok_transitions_[((((tok_state_ << 8)) | tok_nextstate_))]);
            if ((tok_nextstate_ & 128) == 0) {
              tok_state_ = tok_nextstate_;
              tok_cursor_ = tok_cursor_ + 1;
            }
            else if (tok_tokenstart_ == -1) {
              if ((tok_nextstate_ & 64) == 0) {
                tok_tokenstart_ = tok_cursor_;
              }
              tok_state_ = (tok_nextstate_ & 63);
              tok_cursor_ = tok_cursor_ + 1;
            }
            else {
              break;
            }
          }
        }
        tok_stellalogicalstatename_ = ((Keyword*)(tok_stellalogicalstatenames_[tok_state_]));
      }
      if (tok_endoftokensP_) {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "There is no float in this string: " << "`" << value << "'";
          throw *newReadException(stream000->theStringReader());
        }
      }
      if ((tok_stellalogicalstatename_ == KWD_READ_INTEGER) ||
          (tok_stellalogicalstatename_ == KWD_READ_FLOAT)) {
        return (getTokenFloatInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_));
      }
      else {
        { OutputStringStream* stream001 = newOutputStringStream();

          *(stream001->nativeStream) << "Illegal float syntax: " << "`" << value << "'";
          throw *newReadException(stream001->theStringReader());
        }
      }
    }
  }
}

Object* stellaTokenListToSExpression(StellaToken* tokenlist) {
  { Cons* parsedtree = NULL;
    Cons* parsedtreestack = NIL;
    Object* parsedtoken = NULL;
    Cons* conscell = NULL;
    Keyword* tokentype = NULL;

    for (;;) {
      tokentype = tokenlist->logicalTokenType;
      if (tokentype == KWD_READ_OPEN_PAREN) {
        if (((boolean)(parsedtree))) {
          parsedtreestack = cons(parsedtree, parsedtreestack);
        }
        parsedtree = NIL;
        tokenlist = ((StellaToken*)(tokenlist->next));
        continue;
      }
      else if (tokentype == KWD_READ_CLOSE_PAREN) {
        if (parsedtreestack == NIL) {
          parsedtree = parsedtree->reverse();
          break;
        }
        else {
          { Cons* parenttree = parsedtreestack;

            parsedtreestack = parsedtreestack->rest;
            parenttree->rest = ((Cons*)(parenttree->value));
            parenttree->firstSetter(parsedtree->reverse());
            parsedtree = parenttree;
            tokenlist = ((StellaToken*)(tokenlist->next));
            continue;
          }
        }
      }
      else if ((tokentype == KWD_READ_SYMBOL) ||
          (tokentype == KWD_READ_SURROGATE)) {
        { const char* modulename = tokenlist->module;
          const char* name = tokenlist->content;
          Module* module = ((modulename != NULL) ? getStellaModule(modulename, false) : oMODULEo);

          if (!((boolean)(module))) {
            { OutputStringStream* stream000 = newOutputStringStream();

              *(stream000->nativeStream) << "Module " << "`" << modulename << "'" << " does not exist;" << " current token=" << "`" << name << "'";
              throw *newReadException(stream000->theStringReader());
            }
          }
          else if (tokentype == KWD_READ_SURROGATE) {
            parsedtoken = internSurrogateInModule(name, module, false);
          }
          else {
            parsedtoken = ((oTRANSIENTOBJECTSpo &&
                (modulename == NULL)) ? internTransientSymbol(name) : internSymbolInModule(name, module, false));
          }
        }
      }
      else if (tokentype == KWD_READ_KEYWORD) {
        parsedtoken = internRigidSymbolWrtModule(tokenlist->content, NULL, KEYWORD_SYM);
      }
      else if (tokentype == KWD_READ_STRING) {
        parsedtoken = new StringWrapper();
        ((StringWrapper*)(parsedtoken))->wrapperValue = tokenlist->content;
      }
      else if (tokentype == KWD_READ_INTEGER) {
        parsedtoken = wrapIntegerValue(stringToInteger(tokenlist->content));
      }
      else if (tokentype == KWD_READ_FLOAT) {
        parsedtoken = new (PointerFreeGC)FloatWrapper;
        ((FloatWrapper*)(parsedtoken))->wrapperValue = stringToFloat(tokenlist->content);
      }
      else if (tokentype == KWD_READ_CHARACTER) {
        parsedtoken = new (PointerFreeGC)CharacterWrapper;
        ((CharacterWrapper*)(parsedtoken))->wrapperValue = stringToCharacter(tokenlist->content);
      }
      else if (tokentype == KWD_READ_COMMA) {
        parsedtoken = SYM_READ_STELLA_a;
      }
      else if (tokentype == KWD_READ_COMMA_SPLICE) {
        parsedtoken = SYM_READ_STELLA_aa;
      }
      else if ((tokentype == KWD_READ_SINGLE_QUOTE) ||
          (tokentype == KWD_READ_BACK_QUOTE)) {
        expandQuoteMacroToken(tokenlist);
        continue;
      }
      else {
        { OutputStringStream* stream001 = newOutputStringStream();

          *(stream001->nativeStream) << "Illegal read syntax: " << "`" << tokenlist->content << "'" << " of type " << "`" << tokentype << "'";
          throw *newReadException(stream001->theStringReader());
        }
      }
      if (((boolean)(parsedtree))) {
        conscell = new Cons();
        conscell->value = parsedtoken;
        conscell->rest = parsedtree;
        parsedtree = conscell;
        tokenlist = ((StellaToken*)(tokenlist->next));
      }
      else {
        break;
      }
    }
    if (!((boolean)(parsedtree))) {
      return (parsedtoken);
    }
    else {
      return (parsedtree);
    }
  }
}

void expandQuoteMacroToken(StellaToken* quotedlist) {
  { const char* quotestring = quotedlist->content;

    { StellaToken* self000 = newStellaToken();

      self000->type = KWD_READ_SYMBOL;
      self000->logicalTokenType = KWD_READ_SYMBOL;
      self000->content = (stringEqlP(quotestring, "'") ? "QUOTE" : "BQUOTE");
      self000->module = "/STELLA";
      self000->next = ((StellaToken*)(quotedlist->next));
      { StellaToken* token = self000;
        Keyword* tokentype = NULL;
        int balance = 0;

        quotedlist->type = KWD_READ_OPEN_PAREN;
        quotedlist->logicalTokenType = KWD_READ_OPEN_PAREN;
        quotedlist->content = "(";
        quotedlist->next = token;
        quotedlist = ((StellaToken*)(token->next));
        for (;;) {
          tokentype = quotedlist->logicalTokenType;
          if (!((boolean)(tokentype))) {
            break;
          }
          if (tokentype == KWD_READ_OPEN_PAREN) {
            balance = balance + 1;
          }
          else if (tokentype == KWD_READ_CLOSE_PAREN) {
            balance = balance - 1;
            if (balance == 0) {
              break;
            }
            else if (balance < 0) {
              { OutputStringStream* stream000 = newOutputStringStream();

                *(stream000->nativeStream) << "Illegal " << "`" << quotestring << "'" << " syntax";
                throw *newReadException(stream000->theStringReader());
              }
            }
          }
          else {
            if (balance == 0) {
              break;
            }
          }
          quotedlist = ((StellaToken*)(quotedlist->next));
        }
        if (!((boolean)(tokentype))) {
          { OutputStringStream* stream001 = newOutputStringStream();

            *(stream001->nativeStream) << "EOF encountered while parsing " << "`" << quotestring << "'" << " syntax";
            throw *newReadException(stream001->theStringReader());
          }
        }
        { StellaToken* self005 = newStellaToken();

          self005->type = KWD_READ_CLOSE_PAREN;
          self005->logicalTokenType = KWD_READ_CLOSE_PAREN;
          self005->content = ")";
          self005->next = ((StellaToken*)(quotedlist->next));
          token = self005;
        }
        quotedlist->next = token;
      }
    }
  }
}

char stringToCharacter(const char* name) {
  { char chaR = name[0];

    if (strlen(name) > 1) {
      if (stringEqlP(name, "SPACE")) {
        chaR = ' ';
      }
      else if (stringEqlP(name, "LINEFEED")) {
        chaR = '\n';
      }
      else if (stringEqlP(name, "NEWLINE")) {
        chaR = '\n';
      }
      else if (stringEqlP(name, "BACKSPACE")) {
        chaR = '\b';
      }
      else if (stringEqlP(name, "TAB")) {
        chaR = '\t';
      }
      else if (stringEqlP(name, "RETURN")) {
        chaR = '\r';
      }
      else if (stringEqlP(name, "PAGE")) {
        chaR = '\f';
      }
      else if (stringEqlP(name, "NULL")) {
        chaR = '\0';
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "Illegal character constant: " << "`" << stringConcatenate("#\\", name, 0) << "'";
          throw *newReadException(stream000->theStringReader());
        }
      }
    }
    return (chaR);
  }
}

Vector* createTokenizeStringTable(const char* punctuationchars, const char* quotechars, const char* escapechars) {
  { Vector* chartypetable = stella::newVector(256);

    { int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = chartypetable->length() - 1;

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        i = iter000;
        if (oCHARACTER_TYPE_TABLEo[(int)(unsigned char) ((char) i)] == KWD_READ_WHITE_SPACE) {
          (chartypetable->theArray)[i] = KWD_READ_WHITE_SPACE;
        }
        else {
          (chartypetable->theArray)[i] = KWD_READ_TEXT;
        }
      }
    }
    { char ch = NULL_CHARACTER;
      const char* vector000 = punctuationchars;
      int index000 = 0;
      int length000 = strlen(vector000);

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        ch = vector000[index000];
        (chartypetable->theArray)[((int)(unsigned char) ch)] = KWD_READ_PUNCTUATION;
      }
    }
    { char ch = NULL_CHARACTER;
      const char* vector001 = quotechars;
      int index001 = 0;
      int length001 = strlen(vector001);

      for  (; index001 < length001; 
            index001 = index001 + 1) {
        ch = vector001[index001];
        (chartypetable->theArray)[((int)(unsigned char) ch)] = KWD_READ_QUOTE;
      }
    }
    { char ch = NULL_CHARACTER;
      const char* vector002 = escapechars;
      int index002 = 0;
      int length002 = strlen(vector002);

      for  (; index002 < length002; 
            index002 = index002 + 1) {
        ch = vector002[index002];
        (chartypetable->theArray)[((int)(unsigned char) ch)] = KWD_READ_ESCAPE;
      }
    }
    return (chartypetable);
  }
}

Cons* tokenizeString(const char* string, const char* punctuationchars, const char* quotechars, const char* escapechars) {
  // Simple tokenizer that is somewhere between Java's StringTokenizer
  // and StreamTokenizer in functionality.  It doens't specially support number
  // tokens nor comment strings/sequences even though this could be added at
  // the expense of some extra complexity.
  // Returns a list of (<token-string> <token-type>) pairs, where the token
  // type is one of :TEXT, :PUNCTUATION or :QUOTE, i.e., all white space
  // is ignored and escape characters are handled and removed.  For example:
  // 	 
  //   (tokenize-string "for(i='fo^'o'; i>0; i++)" "()=<>+-;" "'" "^")
  //   =>
  //   (("for" :TEXT) ("(" :PUNCTUATION) ("i" :TEXT)
  //    ("=" :PUNCTUATION) ("'" :QUOTE) ("fo'o" :TEXT)
  //    ("'" :QUOTE) (";" :PUNCTUATION) ("i" :TEXT)
  //    (">" :PUNCTUATION) ("0" :TEXT) (";" :PUNCTUATION)
  //    ("i" :TEXT) ("++)" :PUNCTUATION))
  // 	
  // NOTE: this aggregates multiple punctuation characters that immediately
  // follow each other into a single token which is (generally) useful to pickup
  // multi-character operators such as ++, >=, etc.  It's still easy to pick them
  // apart in a post-processing step if necessary (e.g., for the `++)' case above),
  // so we leave this for now as a feature.
  { MemoizationTable* memoTable000 = NULL;
    Cons* memoizedEntry000 = NULL;
    Object* memoizedValue000 = NULL;

    if (oMEMOIZATION_ENABLEDpo) {
      memoTable000 = ((MemoizationTable*)(SGT_READ_STELLA_F_TOKENIZE_STRING_MEMO_TABLE_000->surrogateValue));
      if (!((boolean)(memoTable000))) {
        initializeMemoizationTable(SGT_READ_STELLA_F_TOKENIZE_STRING_MEMO_TABLE_000, "(:MAX-VALUES 10)");
        memoTable000 = ((MemoizationTable*)(SGT_READ_STELLA_F_TOKENIZE_STRING_MEMO_TABLE_000->surrogateValue));
      }
      memoizedEntry000 = lookupMruMemoizedValue(((MruMemoizationTable*)(memoTable000)), wrapString(punctuationchars), wrapString(quotechars), wrapString(escapechars), MEMOIZED_NULL_VALUE, 0);
      memoizedValue000 = memoizedEntry000->value;
    }
    if (((boolean)(memoizedValue000))) {
      if (memoizedValue000 == MEMOIZED_NULL_VALUE) {
        memoizedValue000 = NULL;
      }
    }
    else {
      memoizedValue000 = createTokenizeStringTable(punctuationchars, quotechars, escapechars);
      if (oMEMOIZATION_ENABLEDpo) {
        memoizedEntry000->value = ((!((boolean)(memoizedValue000))) ? MEMOIZED_NULL_VALUE : memoizedValue000);
      }
    }
    { Vector* chartypetable = ((Vector*)(memoizedValue000));
      int i = 0;
      char ch = NULL_CHARACTER;
      int start = 0;
      int end = strlen(string);
      Keyword* state = KWD_READ_TEXT;
      Keyword* newstate = KWD_READ_TEXT;
      boolean quotedtokenP = false;
      char quotechar = NULL_CHARACTER;
      boolean endoftokenP = false;
      Cons* escapepositions = NIL;
      const char* token = NULL;
      Cons* result = NIL;

      for (;;) {
        endoftokenP = false;
        if (i < end) {
          ch = string[i];
          newstate = ((Keyword*)((chartypetable->theArray)[((int)(unsigned char) ch)]));
          if (newstate == KWD_READ_TEXT) {
            if ((state == KWD_READ_PUNCTUATION) ||
                ((state == KWD_READ_WHITE_SPACE) ||
                 (state == KWD_READ_QUOTE))) {
              endoftokenP = true;
            }
            else {
            }
          }
          else if (newstate == KWD_READ_ESCAPE) {
            if ((state == KWD_READ_PUNCTUATION) ||
                ((state == KWD_READ_WHITE_SPACE) ||
                 (state == KWD_READ_QUOTE))) {
              endoftokenP = true;
            }
            else {
            }
            escapepositions = cons(wrapInteger(i), escapepositions);
            i = i + 2;
            continue;
          }
          else if (newstate == KWD_READ_QUOTE) {
            if (quotedtokenP &&
                (ch == quotechar)) {
              endoftokenP = true;
              quotedtokenP = false;
            }
            else if (quotedtokenP) {
              newstate = KWD_READ_TEXT;
            }
            else {
              endoftokenP = true;
              quotedtokenP = true;
              quotechar = ch;
            }
          }
          else if (newstate == KWD_READ_PUNCTUATION) {
            if (state == KWD_READ_TEXT) {
              if (quotedtokenP) {
                newstate = KWD_READ_TEXT;
              }
              else {
                endoftokenP = true;
              }
            }
            else if ((state == KWD_READ_WHITE_SPACE) ||
                (state == KWD_READ_QUOTE)) {
              endoftokenP = true;
            }
            else {
            }
          }
          else if (newstate == KWD_READ_WHITE_SPACE) {
            if (state == KWD_READ_TEXT) {
              if (quotedtokenP) {
                newstate = KWD_READ_TEXT;
              }
              else {
                endoftokenP = true;
              }
            }
            else if ((state == KWD_READ_PUNCTUATION) ||
                (state == KWD_READ_QUOTE)) {
              endoftokenP = true;
            }
            else {
            }
          }
          else {
            { OutputStringStream* stream000 = newOutputStringStream();

              *(stream000->nativeStream) << "`" << newstate << "'" << " is not a valid case option";
              throw *newStellaException(stream000->theStringReader());
            }
          }
        }
        if ((endoftokenP &&
            (i > 0)) ||
            (i >= end)) {
          if (!(state == KWD_READ_WHITE_SPACE)) {
            if (!(escapepositions == NIL)) {
              { Cons* parts = NIL;
                int s = start;

                { IntegerWrapper* e = NULL;
                  Cons* iter000 = escapepositions->reverse();

                  for (; !(iter000 == NIL); iter000 = iter000->rest) {
                    e = ((IntegerWrapper*)(iter000->value));
                    parts = cons(wrapString(stringSubsequence(string, s, e->wrapperValue)), parts);
                    s = e->wrapperValue + 1;
                  }
                }
                parts = cons(wrapString(stringSubsequence(string, stella::integerMin(s, end), stella::integerMin(i, end))), parts);
                parts = parts->reverse();
                token = stringConcatenate(((StringWrapper*)(parts->value))->wrapperValue, ((StringWrapper*)(parts->rest->value))->wrapperValue);
                { StringWrapper* part = NULL;
                  Cons* iter001 = parts->rest->rest;

                  for (; !(iter001 == NIL); iter001 = iter001->rest) {
                    part = ((StringWrapper*)(iter001->value));
                    token = stringConcatenate(token, part->wrapperValue);
                  }
                }
              }
              escapepositions = NIL;
            }
            else {
              token = stringSubsequence(string, start, i);
            }
            result = cons(cons(wrapString(token), cons(state, NIL)), result);
          }
          if (i >= end) {
            break;
          }
          start = i;
        }
        state = newstate;
        i = i + 1;
      }
      return (result->reverse());
    }
  }
}

Object* readSExpression(InputStream* stream, boolean& _Return1) {
  // Read one STELLA s-expression from `stream' and return
  // the result.  Return `true' as the second value on EOF.
  { TokenizerStreamState* tokenizerstate = stream->tokenizerState;
    StellaToken* tokenlist = (((boolean)(tokenizerstate)) ? ((StellaToken*)(tokenizerstate->tokenList)) : NULL);

    if (((boolean)(tokenlist))) {
      tokenlist = tokenizeSExpression(stream, tokenlist);
    }
    else {
      tokenlist = tokenizeSExpression(stream, NULL);
      stream->tokenizerState->tokenList = tokenlist;
    }
    if (!((boolean)(tokenlist))) {
      _Return1 = true;
      return (NULL);
    }
    if ((stream == STANDARD_INPUT) ||
        ((boolean)(stream->echoStream))) {
      eatNextCharacterIfWhitespace(stream);
    }
    { Object* _Return0 = stellaTokenListToSExpression(tokenlist);

      _Return1 = false;
      return (_Return0);
    }
  }
}

int oSTELLA_TOKENIZER_WHITE_SPACE_STATEo = NULL_INTEGER;

boolean eatNextCharacterIfWhitespace(InputStream* stream) {
  { char chaR = NULL_CHARACTER;
    boolean eofP = false;

    chaR = readCharacter(stream, eofP);
    if (eofP) {
      return (true);
    }
    if (oCHARACTER_TYPE_TABLEo[(int)(unsigned char) chaR] == KWD_READ_WHITE_SPACE) {
      { TokenizerStreamState* state = stream->tokenizerState;

        if (((boolean)(state))) {
          state->state = oSTELLA_TOKENIZER_WHITE_SPACE_STATEo;
        }
      }
    }
    else {
      unreadCharacter(chaR, stream);
    }
    return (false);
  }
}

boolean consumeWhitespace(InputStream* stream) {
  for (;;) {
    { char chaR = NULL_CHARACTER;
      boolean eofP = false;

      chaR = readCharacter(stream, eofP);
      if (eofP) {
        return (true);
      }
      if (!(oCHARACTER_TYPE_TABLEo[(int)(unsigned char) chaR] == KWD_READ_WHITE_SPACE)) {
        unreadCharacter(chaR, stream);
        break;
      }
    }
  }
  return (false);
}

Object* readSExpressionFromString(const char* string) {
  // Read one STELLA s-expression from `string' and
  // return the result.
  { boolean dummy1;

    return (readSExpression(makeTokenizerStringStream(string), dummy1));
  }
}

InputStringStream* makeTokenizerStringStream(const char* string) {
  { InputStringStream* stream = newInputStringStream(string);
    TokenizerStreamState* state = new TokenizerStreamState();
    int length = strlen(string) + 1;

    state->buffer = new (PointerFreeGC) char[length];
    state->bufferSize = length;
    state->cursor = length;
    state->end = length;
    state->state = 1;
    state->table = NULL;
    state->stateDictionary = NULL;
    state->tokenList = newStellaToken();
    stream->tokenizerState = state;
    return (stream);
  }
}

const char* nativeReadLine(InputStream* inputstream) {
  // Read one line from `inputStream' using the native language
  // readline algorithm and return the result.  On EOF return `null'
  if (((boolean)(inputstream->tokenizerState))) {
    return (readLineFromTokenizerBuffer(inputstream));
  }
  { std::istream* stream = inputstream->nativeStream;
    OutputStream* echostream = inputstream->echoStream;
    const char* input = NULL;

    input = native_read_line(stream);
    if (((boolean)(echostream)) &&
        (input != NULL)) {
      *(echostream->nativeStream) << input << std::endl;
    }
    return (input);
  }
}

Cons* oREAD_LINE_TOKENIZER_TABLE_DEFINITIONo = NULL;

Cons* oREAD_LINE2_TOKENIZER_TABLE_DEFINITIONo = NULL;

TokenizerTable* oREAD_LINE_TOKENIZER_TABLEo = NULL;

TokenizerTable* oREAD_LINE2_TOKENIZER_TABLEo = NULL;

const char* readLine(InputStream* stream) {
  // Read one line from `stream' and return the result.
  // This differs from `native-read-line' in that it is not platform-dependent.
  // It recognizes any of the three common line ending formats: CR, LF, CR-LF
  // in any combination.  It is not as fast as `native-read-line', however.
  if (stream == STANDARD_INPUT) {
    return (nativeReadLine(stream));
  }
  { TokenizerTable* tok_table_ = oREAD_LINE_TOKENIZER_TABLEo;
    const char* tok_transitions_ = tok_table_->transitions;
    Object** tok_statenames_ = tok_table_->stateNames->theArray;
    int tok_tokenstart_ = -1;
    boolean tok_endoftokensP_ = false;
    InputStream* tok_inputstream_ = stream;
    OutputStream* tok_echostream_ = tok_inputstream_->echoStream;
    TokenizerStreamState* tok_streamstate_ = ((!((boolean)(tok_inputstream_->tokenizerState))) ? (tok_inputstream_->tokenizerState = newTokenizerStreamState()) : tok_inputstream_->tokenizerState);
    char* tok_buffer_ = tok_streamstate_->buffer;
    int tok_size_ = tok_streamstate_->bufferSize;
    int tok_state_ = tok_streamstate_->getSavedState(tok_table_);
    int tok_nextstate_ = tok_state_;
    int tok_cursor_ = tok_streamstate_->cursor;
    int tok_end_ = tok_streamstate_->end;
    int tok_checkpoint_ = ((tok_cursor_ <= tok_end_) ? tok_end_ : tok_size_);

    {
      tok_statenames_ = tok_statenames_;
      tok_endoftokensP_ = tok_endoftokensP_;
    }
    for (;;) {
      {
        tok_tokenstart_ = -1;
        for (;;) {
          if (tok_cursor_ == tok_checkpoint_) {
            if (tok_cursor_ == tok_end_) {
              tok_streamstate_->cursor = tok_cursor_;
              tok_endoftokensP_ = readIntoTokenizerBuffer(tok_inputstream_, tok_streamstate_, tok_tokenstart_);
              tok_buffer_ = tok_streamstate_->buffer;
              tok_size_ = tok_streamstate_->bufferSize;
              tok_cursor_ = integerMod(tok_streamstate_->cursor, tok_size_);
              tok_end_ = tok_streamstate_->end;
              if (tok_endoftokensP_) {
                tok_checkpoint_ = tok_cursor_;
                if (tok_nextstate_ == -1) {
                }
                else if (coerceWrappedBooleanToBoolean(((BooleanWrapper*)((tok_table_->legalEofStates->theArray)[tok_state_])))) {
                  tok_nextstate_ = -1;
                  if (!(tok_tokenstart_ == -1)) {
                    tok_endoftokensP_ = false;
                  }
                }
                else {
                  tok_endoftokensP_ = false;
                  tok_state_ = 0;
                  tok_nextstate_ = -1;
                }
                break;
              }
              if (tok_cursor_ >= tok_end_) {
                tok_checkpoint_ = tok_size_;
              }
              else {
                tok_checkpoint_ = tok_end_;
              }
            }
            else {
              tok_checkpoint_ = tok_end_;
              tok_cursor_ = 0;
            }
          }
          tok_nextstate_ = (int)(unsigned char) (tok_buffer_[tok_cursor_]);
          tok_nextstate_ = (int)(unsigned char) (tok_transitions_[((((tok_state_ << 8)) | tok_nextstate_))]);
          if ((tok_nextstate_ & 128) == 0) {
            tok_state_ = tok_nextstate_;
            tok_cursor_ = tok_cursor_ + 1;
          }
          else if (tok_tokenstart_ == -1) {
            if ((tok_nextstate_ & 64) == 0) {
              tok_tokenstart_ = tok_cursor_;
            }
            tok_state_ = (tok_nextstate_ & 63);
            tok_cursor_ = tok_cursor_ + 1;
          }
          else {
            break;
          }
          if (((boolean)(tok_echostream_))) {
            *(tok_echostream_->nativeStream) << tok_buffer_[(tok_cursor_ - 1)];
          }
        }
      }
      if (tok_endoftokensP_) {
        if (((boolean)(tok_streamstate_))) {
          tok_streamstate_->cursor = tok_cursor_;
          tok_streamstate_->table = tok_table_;
          tok_streamstate_->state = tok_state_;
        }
        return (NULL);
      }
      { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tok_statenames_[tok_state_]));

        if (testValue000 == KWD_READ_LINE) {
          if (((boolean)(tok_streamstate_))) {
            tok_streamstate_->cursor = tok_cursor_;
            tok_streamstate_->table = tok_table_;
            tok_streamstate_->state = tok_state_;
          }
          return (getTokenTextInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, false));
        }
        else if ((testValue000 == KWD_READ_RETURN) ||
            (testValue000 == KWD_READ_LINEFEED)) {
        }
        else if ((testValue000 == KWD_READ_INITIAL_LINEFEED) ||
            (testValue000 == KWD_READ_INITIAL_RETURN)) {
          if (((boolean)(tok_streamstate_))) {
            tok_streamstate_->cursor = tok_cursor_;
            tok_streamstate_->table = tok_table_;
            tok_streamstate_->state = tok_state_;
          }
          return ("");
        }
        else if (testValue000 == KWD_READ_ERROR) {
          if (((boolean)(tok_streamstate_))) {
            tok_streamstate_->cursor = tok_cursor_;
            tok_streamstate_->table = tok_table_;
            tok_streamstate_->state = tok_state_;
          }
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "Illegal read syntax: " << "`" << getTokenTextInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, false) << "'";
            throw *newReadException(stream000->theStringReader());
          }
        }
        else {
          { OutputStringStream* stream001 = newOutputStringStream();

            *(stream001->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
            throw *newStellaException(stream001->theStringReader());
          }
        }
      }
    }
  }
}

const char* readLine2(InputStream* stream, Keyword*& _Return1) {
  // Read one line from `stream' and return the result and
  // a keyword that indicates the terminator for that line ending:
  // `:CR' `:LF' `:CRLF' or `:EOF'.   This is not platform-dependent
  // and differs from `read-line' by returning a second value.  It
  // may hang when used on interactive streams such as terminal or
  // network streams with only CR line endings.  It should only be
  // used on file or string input streams.
  { const char* line = "";

    { TokenizerTable* tok_table_ = oREAD_LINE_TOKENIZER_TABLEo;
      const char* tok_transitions_ = tok_table_->transitions;
      Object** tok_statenames_ = tok_table_->stateNames->theArray;
      int tok_tokenstart_ = -1;
      boolean tok_endoftokensP_ = false;
      InputStream* tok_inputstream_ = stream;
      OutputStream* tok_echostream_ = tok_inputstream_->echoStream;
      TokenizerStreamState* tok_streamstate_ = ((!((boolean)(tok_inputstream_->tokenizerState))) ? (tok_inputstream_->tokenizerState = newTokenizerStreamState()) : tok_inputstream_->tokenizerState);
      char* tok_buffer_ = tok_streamstate_->buffer;
      int tok_size_ = tok_streamstate_->bufferSize;
      int tok_state_ = tok_streamstate_->getSavedState(tok_table_);
      int tok_nextstate_ = tok_state_;
      int tok_cursor_ = tok_streamstate_->cursor;
      int tok_end_ = tok_streamstate_->end;
      int tok_checkpoint_ = ((tok_cursor_ <= tok_end_) ? tok_end_ : tok_size_);

      {
        tok_statenames_ = tok_statenames_;
        tok_endoftokensP_ = tok_endoftokensP_;
      }
      for (;;) {
        {
          tok_tokenstart_ = -1;
          for (;;) {
            if (tok_cursor_ == tok_checkpoint_) {
              if (tok_cursor_ == tok_end_) {
                tok_streamstate_->cursor = tok_cursor_;
                tok_endoftokensP_ = readIntoTokenizerBuffer(tok_inputstream_, tok_streamstate_, tok_tokenstart_);
                tok_buffer_ = tok_streamstate_->buffer;
                tok_size_ = tok_streamstate_->bufferSize;
                tok_cursor_ = integerMod(tok_streamstate_->cursor, tok_size_);
                tok_end_ = tok_streamstate_->end;
                if (tok_endoftokensP_) {
                  tok_checkpoint_ = tok_cursor_;
                  if (tok_nextstate_ == -1) {
                  }
                  else if (coerceWrappedBooleanToBoolean(((BooleanWrapper*)((tok_table_->legalEofStates->theArray)[tok_state_])))) {
                    tok_nextstate_ = -1;
                    if (!(tok_tokenstart_ == -1)) {
                      tok_endoftokensP_ = false;
                    }
                  }
                  else {
                    tok_endoftokensP_ = false;
                    tok_state_ = 0;
                    tok_nextstate_ = -1;
                  }
                  break;
                }
                if (tok_cursor_ >= tok_end_) {
                  tok_checkpoint_ = tok_size_;
                }
                else {
                  tok_checkpoint_ = tok_end_;
                }
              }
              else {
                tok_checkpoint_ = tok_end_;
                tok_cursor_ = 0;
              }
            }
            tok_nextstate_ = (int)(unsigned char) (tok_buffer_[tok_cursor_]);
            tok_nextstate_ = (int)(unsigned char) (tok_transitions_[((((tok_state_ << 8)) | tok_nextstate_))]);
            if ((tok_nextstate_ & 128) == 0) {
              tok_state_ = tok_nextstate_;
              tok_cursor_ = tok_cursor_ + 1;
            }
            else if (tok_tokenstart_ == -1) {
              if ((tok_nextstate_ & 64) == 0) {
                tok_tokenstart_ = tok_cursor_;
              }
              tok_state_ = (tok_nextstate_ & 63);
              tok_cursor_ = tok_cursor_ + 1;
            }
            else {
              break;
            }
            if (((boolean)(tok_echostream_))) {
              *(tok_echostream_->nativeStream) << tok_buffer_[(tok_cursor_ - 1)];
            }
          }
        }
        if (tok_endoftokensP_) {
          if (((boolean)(tok_streamstate_))) {
            tok_streamstate_->cursor = tok_cursor_;
            tok_streamstate_->table = tok_table_;
            tok_streamstate_->state = tok_state_;
          }
          if (stringEqlP(line, "")) {
            { const char* _Return0 = NULL;

              _Return1 = KWD_READ_EOF;
              return (_Return0);
            }
          }
          else {
            _Return1 = KWD_READ_EOF;
            return (line);
          }
        }
        { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tok_statenames_[tok_state_]));

          if (testValue000 == KWD_READ_LINE) {
            line = getTokenTextInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, false);
          }
          else if (testValue000 == KWD_READ_LINEFEED) {
            if (((boolean)(tok_streamstate_))) {
              tok_streamstate_->cursor = tok_cursor_;
              tok_streamstate_->table = tok_table_;
              tok_streamstate_->state = tok_state_;
            }
            _Return1 = KWD_READ_LF;
            return (line);
          }
          else if (testValue000 == KWD_READ_RETURN_LINEFEED) {
            if (((boolean)(tok_streamstate_))) {
              tok_streamstate_->cursor = tok_cursor_;
              tok_streamstate_->table = tok_table_;
              tok_streamstate_->state = tok_state_;
            }
            _Return1 = KWD_READ_CRLF;
            return (line);
          }
          else if (testValue000 == KWD_READ_RETURN) {
            if (((boolean)(tok_streamstate_))) {
              tok_streamstate_->cursor = tok_cursor_;
              tok_streamstate_->table = tok_table_;
              tok_streamstate_->state = tok_state_;
            }
            _Return1 = KWD_READ_CR;
            return (line);
          }
          else if (testValue000 == KWD_READ_ERROR) {
            if (((boolean)(tok_streamstate_))) {
              tok_streamstate_->cursor = tok_cursor_;
              tok_streamstate_->table = tok_table_;
              tok_streamstate_->state = tok_state_;
            }
            { OutputStringStream* stream000 = newOutputStringStream();

              *(stream000->nativeStream) << "Illegal read syntax: " << "`" << getTokenTextInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, false) << "'";
              throw *newReadException(stream000->theStringReader());
            }
          }
          else {
            { OutputStringStream* stream001 = newOutputStringStream();

              *(stream001->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
              throw *newStellaException(stream001->theStringReader());
            }
          }
        }
      }
    }
  }
}

char readCharacter(InputStream* inputstream, boolean& _Return1) {
  // Read one character from `inputStream' and return the result.
  // Return `true' as the second value on EOF.
  if (((boolean)(inputstream->tokenizerState))) {
    return (readCharacterFromTokenizerBuffer(inputstream, _Return1));
  }
  { std::istream* stream = inputstream->nativeStream;
    OutputStream* echostream = inputstream->echoStream;
    char input = NULL_CHARACTER;
    boolean eof = false;

    input = native_read_character(stream, eof);
    if (((boolean)(echostream)) &&
        (!eof)) {
      *(echostream->nativeStream) << input;
    }
    _Return1 = eof;
    return (input);
  }
}

void unreadCharacter(char ch, InputStream* inputstream) {
  // Unread `ch' from `inputStream'.  Signal an error if `ch'
  // was not the last character read.
  if (((boolean)(inputstream->tokenizerState))) {
    unreadCharacterFromTokenizerBuffer(ch, inputstream);
  }
  else {
    { std::istream* stream = inputstream->nativeStream;

      stream->putback(ch);
    }
  }
}

// Controls the behavior of interactive queries.  The default is :ASK
// which asks the user.  Other options are :YES, :NO, :YES-VERBOSE, :NO-VERBOSE.  These
// return the answer indicated, with the verbose versions printing the message and answer.
DEFINE_STELLA_SPECIAL(oUSER_QUERY_ACTIONo, Keyword* , NULL);

boolean yesOrNoP(const char* message) {
  // Read a line of input from STANDARD-INPUT and return `true'
  // if the input was `yes' or `false' if the input was `no'.  Loop until either
  // `yes' or `no' was entered.  If 'message' is non-`null' prompt with it before
  // the input is read.  See also special variable `*USER-QUERY-ACTION*'.
  if (oUSER_QUERY_ACTIONo == KWD_READ_YES) {
    return (true);
  }
  else if (oUSER_QUERY_ACTIONo == KWD_READ_NO) {
    return (false);
  }
  else if (oUSER_QUERY_ACTIONo == KWD_READ_YES_VERBOSE) {
    std::cout << message << " [Auto => YES]" << std::endl;
    return (true);
  }
  else if (oUSER_QUERY_ACTIONo == KWD_READ_NO_VERBOSE) {
    std::cout << message << " [Auto => NO]" << std::endl;
    return (false);
  }
  else if (oUSER_QUERY_ACTIONo == KWD_READ_ASK) {
    { const char* input = NULL;
      int start = 0;

      for (;;) {
        if (message != NULL) {
          std::cout << message;
        }
        input = readLine(STANDARD_INPUT);
        start = 0;
        { char ch = NULL_CHARACTER;
          const char* vector000 = input;
          int index000 = 0;
          int length000 = strlen(vector000);

          for  (; index000 < length000; 
                index000 = index000 + 1) {
            ch = vector000[index000];
            if (oCHARACTER_TYPE_TABLEo[(int)(unsigned char) ch] == KWD_READ_WHITE_SPACE) {
              start = start + 1;
            }
            else {
              break;
            }
          }
        }
        if (strlen(input) > start) {
          input = stringSubsequence(input, start, NULL_INTEGER);
          if (stringEqualP(input, "yes")) {
            return (true);
          }
          if (stringEqualP(input, "no")) {
            return (false);
          }
          std::cout << "Type `yes' for yes or `no' for no." << std::endl;
        }
      }
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << oUSER_QUERY_ACTIONo << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

boolean yOrNP(const char* message) {
  // Read a line of input from STANDARD-INPUT and return `true'
  // if the input was `y' or `false' if the input was `n'.  Loop until either
  // `y' or `n' was entered.  If 'message' is non-`null' prompt with it before
  // the input is read.  See also special variable `*USER-QUERY-ACTION*'.
  if (oUSER_QUERY_ACTIONo == KWD_READ_YES) {
    return (true);
  }
  else if (oUSER_QUERY_ACTIONo == KWD_READ_NO) {
    return (false);
  }
  else if (oUSER_QUERY_ACTIONo == KWD_READ_YES_VERBOSE) {
    std::cout << message << " [Auto => Y]" << std::endl;
    return (true);
  }
  else if (oUSER_QUERY_ACTIONo == KWD_READ_NO_VERBOSE) {
    std::cout << message << " [Auto => N]" << std::endl;
    return (false);
  }
  else if (oUSER_QUERY_ACTIONo == KWD_READ_ASK) {
    { const char* input = NULL;
      int start = 0;

      for (;;) {
        if (message != NULL) {
          std::cout << message;
        }
        input = readLine(STANDARD_INPUT);
        start = 0;
        { char ch = NULL_CHARACTER;
          const char* vector000 = input;
          int index000 = 0;
          int length000 = strlen(vector000);

          for  (; index000 < length000; 
                index000 = index000 + 1) {
            ch = vector000[index000];
            if (oCHARACTER_TYPE_TABLEo[(int)(unsigned char) ch] == KWD_READ_WHITE_SPACE) {
              start = start + 1;
            }
            else {
              break;
            }
          }
        }
        if (strlen(input) > start) {
          switch (input[start]) {
            case 'y': 
            case 'Y': 
              return (true);
            case 'n': 
            case 'N': 
              return (false);
            default:
              break;
          }
        }
        std::cout << "Type `y' for yes or `n' for no." << std::endl;
      }
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << oUSER_QUERY_ACTIONo << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

const char* InputStream::streamToString() {
  // Read all of the input from `stream' and return it as a string.
  { InputStream* from = this;

    { OutputStringStream* to = newOutputStringStream();

      copyStreamToStream(from, to);
      return (to->theStringReader());
    }
  }
}

const char* fileToString(const char* file) {
  // Read the content of `file' and return it as a string.
  { InputFileStream* in = NULL;

    try {
      in = openInputFile(file, 0);
      return (in->streamToString());
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
}

void helpStartupRead1() {
  {
    SGT_READ_STELLA_TOKENIZER_TABLE = ((Surrogate*)(internRigidSymbolWrtModule("TOKENIZER-TABLE", NULL, 1)));
    SYM_READ_STELLA_TRANSITIONS = ((Symbol*)(internRigidSymbolWrtModule("TRANSITIONS", NULL, 0)));
    SYM_READ_STELLA_UNIQUE_STATE_NAMES = ((Symbol*)(internRigidSymbolWrtModule("UNIQUE-STATE-NAMES", NULL, 0)));
    SYM_READ_STELLA_STATE_NAMES = ((Symbol*)(internRigidSymbolWrtModule("STATE-NAMES", NULL, 0)));
    SYM_READ_STELLA_LEGAL_EOF_STATES = ((Symbol*)(internRigidSymbolWrtModule("LEGAL-EOF-STATES", NULL, 0)));
    SYM_READ_STELLA_CHARACTER_SET = ((Symbol*)(internRigidSymbolWrtModule("CHARACTER-SET", NULL, 0)));
    KWD_READ_ERROR = ((Keyword*)(internRigidSymbolWrtModule("ERROR", NULL, 2)));
    KWD_READ_START = ((Keyword*)(internRigidSymbolWrtModule("START", NULL, 2)));
    KWD_READ_EOF = ((Keyword*)(internRigidSymbolWrtModule("EOF", NULL, 2)));
    SGT_READ_STELLA_GENERALIZED_SYMBOL = ((Surrogate*)(internRigidSymbolWrtModule("GENERALIZED-SYMBOL", NULL, 1)));
    SGT_READ_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", NULL, 1)));
    KWD_READ_BLOCK = ((Keyword*)(internRigidSymbolWrtModule("BLOCK", NULL, 2)));
    KWD_READ_LINE = ((Keyword*)(internRigidSymbolWrtModule("LINE", NULL, 2)));
    KWD_READ_CHARACTER = ((Keyword*)(internRigidSymbolWrtModule("CHARACTER", NULL, 2)));
    SGT_READ_STELLA_TOKENIZER_TOKEN = ((Surrogate*)(internRigidSymbolWrtModule("TOKENIZER-TOKEN", NULL, 1)));
    SYM_READ_STELLA_TYPE = ((Symbol*)(internRigidSymbolWrtModule("TYPE", NULL, 0)));
    SYM_READ_STELLA_CONTENT = ((Symbol*)(internRigidSymbolWrtModule("CONTENT", NULL, 0)));
    SYM_READ_STELLA_NEXT = ((Symbol*)(internRigidSymbolWrtModule("NEXT", NULL, 0)));
    SGT_READ_STELLA_TOKENIZER_STREAM_STATE = ((Surrogate*)(internRigidSymbolWrtModule("TOKENIZER-STREAM-STATE", NULL, 1)));
    SYM_READ_STELLA_BUFFER_SIZE = ((Symbol*)(internRigidSymbolWrtModule("BUFFER-SIZE", NULL, 0)));
    SYM_READ_STELLA_CURSOR = ((Symbol*)(internRigidSymbolWrtModule("CURSOR", NULL, 0)));
    SYM_READ_STELLA_END = ((Symbol*)(internRigidSymbolWrtModule("END", NULL, 0)));
    SYM_READ_STELLA_STATE = ((Symbol*)(internRigidSymbolWrtModule("STATE", NULL, 0)));
    SYM_READ_STELLA_TABLE = ((Symbol*)(internRigidSymbolWrtModule("TABLE", NULL, 0)));
    SYM_READ_STELLA_STATE_DICTIONARY = ((Symbol*)(internRigidSymbolWrtModule("STATE-DICTIONARY", NULL, 0)));
    SYM_READ_STELLA_TOKEN_LIST = ((Symbol*)(internRigidSymbolWrtModule("TOKEN-LIST", NULL, 0)));
    SGT_READ_STELLA_INPUT_STREAM = ((Surrogate*)(internRigidSymbolWrtModule("INPUT-STREAM", NULL, 1)));
    SGT_READ_STELLA_STRING = ((Surrogate*)(internRigidSymbolWrtModule("STRING", NULL, 1)));
    SGT_READ_STELLA_VOID = ((Surrogate*)(internRigidSymbolWrtModule("VOID", NULL, 1)));
    SGT_READ_STELLA_MUTABLE_STRING = ((Surrogate*)(internRigidSymbolWrtModule("MUTABLE-STRING", NULL, 1)));
    SYM_READ_STELLA_LET = ((Symbol*)(internRigidSymbolWrtModule("LET", NULL, 0)));
    SYM_READ_STELLA_TOK_TABLE_ = ((Symbol*)(internRigidSymbolWrtModule("TOK_TABLE_", NULL, 0)));
    SYM_READ_STELLA_TOK_TRANSITIONS_ = ((Symbol*)(internRigidSymbolWrtModule("TOK_TRANSITIONS_", NULL, 0)));
    SYM_READ_STELLA_TOK_STATENAMES_ = ((Symbol*)(internRigidSymbolWrtModule("TOK_STATENAMES_", NULL, 0)));
    SYM_READ_STELLA_THE_ARRAY = ((Symbol*)(internRigidSymbolWrtModule("THE-ARRAY", NULL, 0)));
    SYM_READ_STELLA_TOK_TOKENSTART_ = ((Symbol*)(internRigidSymbolWrtModule("TOK_TOKENSTART_", NULL, 0)));
    SYM_READ_STELLA_TOK_ENDOFTOKENSp_ = ((Symbol*)(internRigidSymbolWrtModule("TOK_ENDOFTOKENS?_", NULL, 0)));
    SYM_READ_STELLA_FALSE = ((Symbol*)(internRigidSymbolWrtModule("FALSE", NULL, 0)));
    SYM_READ_STELLA_IGNORE = ((Symbol*)(internRigidSymbolWrtModule("IGNORE", NULL, 0)));
    SYM_READ_STELLA_TOK_STREAMSTATE_ = ((Symbol*)(internRigidSymbolWrtModule("TOK_STREAMSTATE_", NULL, 0)));
    SYM_READ_STELLA_TOKENIZER_STREAM_STATE = ((Symbol*)(internRigidSymbolWrtModule("TOKENIZER-STREAM-STATE", NULL, 0)));
    SYM_READ_STELLA_NULL = ((Symbol*)(internRigidSymbolWrtModule("NULL", NULL, 0)));
    SYM_READ_STELLA_TOK_BUFFER_ = ((Symbol*)(internRigidSymbolWrtModule("TOK_BUFFER_", NULL, 0)));
    SYM_READ_STELLA_STRING_TO_TOKENIZER_BYTE_ARRAY = ((Symbol*)(internRigidSymbolWrtModule("STRING-TO-TOKENIZER-BYTE-ARRAY", NULL, 0)));
    SYM_READ_STELLA_TOK_STATE_ = ((Symbol*)(internRigidSymbolWrtModule("TOK_STATE_", NULL, 0)));
    SYM_READ_STELLA_TOK_NEXTSTATE_ = ((Symbol*)(internRigidSymbolWrtModule("TOK_NEXTSTATE_", NULL, 0)));
    SYM_READ_STELLA_TOK_CURSOR_ = ((Symbol*)(internRigidSymbolWrtModule("TOK_CURSOR_", NULL, 0)));
    SYM_READ_STELLA_TOK_SIZE_ = ((Symbol*)(internRigidSymbolWrtModule("TOK_SIZE_", NULL, 0)));
    SYM_READ_STELLA_LENGTH = ((Symbol*)(internRigidSymbolWrtModule("LENGTH", NULL, 0)));
    SYM_READ_STELLA_TOK_END_ = ((Symbol*)(internRigidSymbolWrtModule("TOK_END_", NULL, 0)));
    SYM_READ_STELLA_TOK_INPUTSTREAM_ = ((Symbol*)(internRigidSymbolWrtModule("TOK_INPUTSTREAM_", NULL, 0)));
    SYM_READ_STELLA_TOK_ECHOSTREAM_ = ((Symbol*)(internRigidSymbolWrtModule("TOK_ECHOSTREAM_", NULL, 0)));
    SYM_READ_STELLA_ECHO_STREAM = ((Symbol*)(internRigidSymbolWrtModule("ECHO-STREAM", NULL, 0)));
    SYM_READ_STELLA_CHOOSE = ((Symbol*)(internRigidSymbolWrtModule("CHOOSE", NULL, 0)));
    SYM_READ_STELLA_NULLp = ((Symbol*)(internRigidSymbolWrtModule("NULL?", NULL, 0)));
    SYM_READ_STELLA_TOKENIZER_STATE = ((Symbol*)(internRigidSymbolWrtModule("TOKENIZER-STATE", NULL, 0)));
    SYM_READ_STELLA_SETF = ((Symbol*)(internRigidSymbolWrtModule("SETF", NULL, 0)));
    SYM_READ_STELLA_NEW = ((Symbol*)(internRigidSymbolWrtModule("NEW", NULL, 0)));
    SYM_READ_STELLA_BUFFER = ((Symbol*)(internRigidSymbolWrtModule("BUFFER", NULL, 0)));
    SYM_READ_STELLA_GET_SAVED_STATE = ((Symbol*)(internRigidSymbolWrtModule("GET-SAVED-STATE", NULL, 0)));
  }
}

void helpStartupRead2() {
  {
    SYM_READ_STELLA_TOK_CHECKPOINT_ = ((Symbol*)(internRigidSymbolWrtModule("TOK_CHECKPOINT_", NULL, 0)));
    SYM_READ_STELLA_le = ((Symbol*)(internRigidSymbolWrtModule("<=", NULL, 0)));
    SYM_READ_STELLA_END_OF_TOKENSp = ((Symbol*)(internRigidSymbolWrtModule("END-OF-TOKENS?", NULL, 0)));
    SYM_READ_STELLA_GET_TOKEN_TEXT = ((Symbol*)(internRigidSymbolWrtModule("GET-TOKEN-TEXT", NULL, 0)));
    SYM_READ_STELLA_GET_TOKEN_TEXT_INTERNAL = ((Symbol*)(internRigidSymbolWrtModule("GET-TOKEN-TEXT-INTERNAL", NULL, 0)));
    SYM_READ_STELLA_i = ((Symbol*)(internRigidSymbolWrtModule("+", NULL, 0)));
    SYM_READ_STELLA_l = ((Symbol*)(internRigidSymbolWrtModule("<", NULL, 0)));
    SYM_READ_STELLA_COPY_TOKEN_TEXT_INTERNAL = ((Symbol*)(internRigidSymbolWrtModule("COPY-TOKEN-TEXT-INTERNAL", NULL, 0)));
    SYM_READ_STELLA_GET_TOKEN_TYPE = ((Symbol*)(internRigidSymbolWrtModule("GET-TOKEN-TYPE", NULL, 0)));
    SYM_READ_STELLA_NTH = ((Symbol*)(internRigidSymbolWrtModule("NTH", NULL, 0)));
    SYM_READ_STELLA_WHEN = ((Symbol*)(internRigidSymbolWrtModule("WHEN", NULL, 0)));
    SYM_READ_STELLA_DEFINEDp = ((Symbol*)(internRigidSymbolWrtModule("DEFINED?", NULL, 0)));
    SYM_READ_STELLA_SETQ = ((Symbol*)(internRigidSymbolWrtModule("SETQ", NULL, 0)));
    SYM_READ_STELLA_GET_NEXT_TOKEN = ((Symbol*)(internRigidSymbolWrtModule("GET-NEXT-TOKEN", NULL, 0)));
    SYM_READ_STELLA_SAVE_TOKENIZER_STREAM_STATE = ((Symbol*)(internRigidSymbolWrtModule("SAVE-TOKENIZER-STREAM-STATE", NULL, 0)));
    SYM_READ_STELLA_TRUE = ((Symbol*)(internRigidSymbolWrtModule("TRUE", NULL, 0)));
    SYM_READ_STELLA_PROGN = ((Symbol*)(internRigidSymbolWrtModule("PROGN", NULL, 0)));
    SYM_READ_STELLA_LOOP = ((Symbol*)(internRigidSymbolWrtModule("LOOP", NULL, 0)));
    SYM_READ_STELLA_CHARACTER_CODE = ((Symbol*)(internRigidSymbolWrtModule("CHARACTER-CODE", NULL, 0)));
    SYM_READ_STELLA_BYTE_ARRAY_NTH = ((Symbol*)(internRigidSymbolWrtModule("BYTE-ARRAY-NTH", NULL, 0)));
    SYM_READ_STELLA_IF_OUTPUT_LANGUAGE = ((Symbol*)(internRigidSymbolWrtModule("IF-OUTPUT-LANGUAGE", NULL, 0)));
    KWD_READ_COMMON_LISP = ((Keyword*)(internRigidSymbolWrtModule("COMMON-LISP", NULL, 2)));
    SYM_READ_STELLA_g = ((Symbol*)(internRigidSymbolWrtModule(">", NULL, 0)));
    SYM_READ_STELLA_LOGOR = ((Symbol*)(internRigidSymbolWrtModule("LOGOR", NULL, 0)));
    SYM_READ_STELLA_SHIFT_LEFT = ((Symbol*)(internRigidSymbolWrtModule("SHIFT-LEFT", NULL, 0)));
    SYM_READ_STELLA_COND = ((Symbol*)(internRigidSymbolWrtModule("COND", NULL, 0)));
    SYM_READ_STELLA_e = ((Symbol*)(internRigidSymbolWrtModule("=", NULL, 0)));
    SYM_READ_STELLA_LOGAND = ((Symbol*)(internRigidSymbolWrtModule("LOGAND", NULL, 0)));
    SYM_READ_STELLA_ii = ((Symbol*)(internRigidSymbolWrtModule("++", NULL, 0)));
    SYM_READ_STELLA_OTHERWISE = ((Symbol*)(internRigidSymbolWrtModule("OTHERWISE", NULL, 0)));
    SYM_READ_STELLA_BREAK = ((Symbol*)(internRigidSymbolWrtModule("BREAK", NULL, 0)));
    SYM_READ_STELLA_READ_INTO_TOKENIZER_BUFFER = ((Symbol*)(internRigidSymbolWrtModule("READ-INTO-TOKENIZER-BUFFER", NULL, 0)));
    SYM_READ_STELLA_MOD = ((Symbol*)(internRigidSymbolWrtModule("MOD", NULL, 0)));
    SYM_READ_STELLA_UNLESS = ((Symbol*)(internRigidSymbolWrtModule("UNLESS", NULL, 0)));
    SYM_READ_STELLA_IF = ((Symbol*)(internRigidSymbolWrtModule("IF", NULL, 0)));
    SYM_READ_STELLA_ge = ((Symbol*)(internRigidSymbolWrtModule(">=", NULL, 0)));
    SYM_READ_STELLA_PRINT_STREAM = ((Symbol*)(internRigidSymbolWrtModule("PRINT-STREAM", NULL, 0)));
    SYM_READ_STELLA_1_ = ((Symbol*)(internRigidSymbolWrtModule("1-", NULL, 0)));
    SGT_READ_STELLA_STREAM_TOKENIZER = ((Surrogate*)(internRigidSymbolWrtModule("STREAM-TOKENIZER", NULL, 1)));
    SYM_READ_STELLA_STREAM = ((Symbol*)(internRigidSymbolWrtModule("STREAM", NULL, 0)));
    KWD_READ_INCLUDE = ((Keyword*)(internRigidSymbolWrtModule("INCLUDE", NULL, 2)));
    KWD_READ_DELIMITER = ((Keyword*)(internRigidSymbolWrtModule("DELIMITER", NULL, 2)));
    KWD_READ_ATOM = ((Keyword*)(internRigidSymbolWrtModule("ATOM", NULL, 2)));
    SYM_READ_STELLA_o = ((Symbol*)(internRigidSymbolWrtModule("*", NULL, 0)));
    KWD_READ_OPEN_PAREN = ((Keyword*)(internRigidSymbolWrtModule("OPEN-PAREN", NULL, 2)));
    KWD_READ_CLOSE_PAREN = ((Keyword*)(internRigidSymbolWrtModule("CLOSE-PAREN", NULL, 2)));
    KWD_READ_OPEN_STRING = ((Keyword*)(internRigidSymbolWrtModule("OPEN-STRING", NULL, 2)));
    KWD_READ_STRING = ((Keyword*)(internRigidSymbolWrtModule("STRING", NULL, 2)));
    KWD_READ_SINGLE_QUOTE = ((Keyword*)(internRigidSymbolWrtModule("SINGLE-QUOTE", NULL, 2)));
    KWD_READ_BACK_QUOTE = ((Keyword*)(internRigidSymbolWrtModule("BACK-QUOTE", NULL, 2)));
    KWD_READ_COMMA = ((Keyword*)(internRigidSymbolWrtModule("COMMA", NULL, 2)));
    SYM_READ_STELLA_x = ((Symbol*)(internRigidSymbolWrtModule("!", NULL, 0)));
    KWD_READ_COMMENT = ((Keyword*)(internRigidSymbolWrtModule("COMMENT", NULL, 2)));
    KWD_READ_HASH = ((Keyword*)(internRigidSymbolWrtModule("HASH", NULL, 2)));
    KWD_READ_WHITE_SPACE = ((Keyword*)(internRigidSymbolWrtModule("WHITE-SPACE", NULL, 2)));
    KWD_READ_OTHERWISE = ((Keyword*)(internRigidSymbolWrtModule("OTHERWISE", NULL, 2)));
    KWD_READ_PAREN_COMMENT = ((Keyword*)(internRigidSymbolWrtModule("PAREN-COMMENT", NULL, 2)));
    KWD_READ_PAREN_COMMENT_ESCAPE = ((Keyword*)(internRigidSymbolWrtModule("PAREN-COMMENT-ESCAPE", NULL, 2)));
    KWD_READ_PAREN_COMMENT_BAR = ((Keyword*)(internRigidSymbolWrtModule("PAREN-COMMENT-BAR", NULL, 2)));
    KWD_READ_ANY = ((Keyword*)(internRigidSymbolWrtModule("ANY", NULL, 2)));
  }
}

void helpStartupRead3() {
  {
    KWD_READ_COMMA_SPLICE = ((Keyword*)(internRigidSymbolWrtModule("COMMA-SPLICE", NULL, 2)));
    KWD_READ_SYMBOL_OR_SIGNED_NUMBER = ((Keyword*)(internRigidSymbolWrtModule("SYMBOL-OR-SIGNED-NUMBER", NULL, 2)));
    KWD_READ_SYMBOL = ((Keyword*)(internRigidSymbolWrtModule("SYMBOL", NULL, 2)));
    KWD_READ_SYMBOL_OR_NUMBER = ((Keyword*)(internRigidSymbolWrtModule("SYMBOL-OR-NUMBER", NULL, 2)));
    KWD_READ_INTEGER = ((Keyword*)(internRigidSymbolWrtModule("INTEGER", NULL, 2)));
    KWD_READ_SYMBOL_OR_CL_SYMBOL = ((Keyword*)(internRigidSymbolWrtModule("SYMBOL-OR-CL-SYMBOL", NULL, 2)));
    KWD_READ_OPEN_FULLY_ESCAPED_SYMBOL = ((Keyword*)(internRigidSymbolWrtModule("OPEN-FULLY-ESCAPED-SYMBOL", NULL, 2)));
    KWD_READ_FULLY_ESCAPED_SYMBOL = ((Keyword*)(internRigidSymbolWrtModule("FULLY-ESCAPED-SYMBOL", NULL, 2)));
    KWD_READ_ESCAPED_SYMBOL_ESCAPE = ((Keyword*)(internRigidSymbolWrtModule("ESCAPED-SYMBOL-ESCAPE", NULL, 2)));
    KWD_READ_QUALIFIED_NAME = ((Keyword*)(internRigidSymbolWrtModule("QUALIFIED-NAME", NULL, 2)));
    KWD_READ_OPEN_KEYWORD = ((Keyword*)(internRigidSymbolWrtModule("OPEN-KEYWORD", NULL, 2)));
    KWD_READ_KEYWORD = ((Keyword*)(internRigidSymbolWrtModule("KEYWORD", NULL, 2)));
    KWD_READ_OPEN_SURROGATE = ((Keyword*)(internRigidSymbolWrtModule("OPEN-SURROGATE", NULL, 2)));
    KWD_READ_SURROGATE = ((Keyword*)(internRigidSymbolWrtModule("SURROGATE", NULL, 2)));
    KWD_READ_CLOSE_STRING = ((Keyword*)(internRigidSymbolWrtModule("CLOSE-STRING", NULL, 2)));
    KWD_READ_STRING_ESCAPE = ((Keyword*)(internRigidSymbolWrtModule("STRING-ESCAPE", NULL, 2)));
    KWD_READ_ESCAPED_STRING = ((Keyword*)(internRigidSymbolWrtModule("ESCAPED-STRING", NULL, 2)));
    KWD_READ_CHARACTER_CONSTANT = ((Keyword*)(internRigidSymbolWrtModule("CHARACTER-CONSTANT", NULL, 2)));
    KWD_READ_SYMBOL_OR_MANTISSA = ((Keyword*)(internRigidSymbolWrtModule("SYMBOL-OR-MANTISSA", NULL, 2)));
    KWD_READ_SYMBOL_OR_MANTISSA2 = ((Keyword*)(internRigidSymbolWrtModule("SYMBOL-OR-MANTISSA2", NULL, 2)));
    KWD_READ_FLOAT = ((Keyword*)(internRigidSymbolWrtModule("FLOAT", NULL, 2)));
    KWD_READ_SYMBOL_OR_EXPONENT_DELIMITER = ((Keyword*)(internRigidSymbolWrtModule("SYMBOL-OR-EXPONENT-DELIMITER", NULL, 2)));
    KWD_READ_SYMBOL_OR_EXPONENT = ((Keyword*)(internRigidSymbolWrtModule("SYMBOL-OR-EXPONENT", NULL, 2)));
    KWD_READ_SYMBOL_OR_EXPONENT2 = ((Keyword*)(internRigidSymbolWrtModule("SYMBOL-OR-EXPONENT2", NULL, 2)));
    KWD_READ_SYMBOL_OR_CL_SYMBOL2 = ((Keyword*)(internRigidSymbolWrtModule("SYMBOL-OR-CL-SYMBOL2", NULL, 2)));
    KWD_READ_SYMBOL_OR_CL_SYMBOL3 = ((Keyword*)(internRigidSymbolWrtModule("SYMBOL-OR-CL-SYMBOL3", NULL, 2)));
    KWD_READ_CL_SYMBOL = ((Keyword*)(internRigidSymbolWrtModule("CL-SYMBOL", NULL, 2)));
    KWD_READ_ESCAPED_SYMBOL = ((Keyword*)(internRigidSymbolWrtModule("ESCAPED-SYMBOL", NULL, 2)));
    KWD_READ_CLOSE_FULLY_ESCAPED_NAME = ((Keyword*)(internRigidSymbolWrtModule("CLOSE-FULLY-ESCAPED-NAME", NULL, 2)));
    KWD_READ_FULLY_ESCAPED_SYMBOL_ESCAPE = ((Keyword*)(internRigidSymbolWrtModule("FULLY-ESCAPED-SYMBOL-ESCAPE", NULL, 2)));
    KWD_READ_FULLY_ESCAPED_KEYWORD = ((Keyword*)(internRigidSymbolWrtModule("FULLY-ESCAPED-KEYWORD", NULL, 2)));
    KWD_READ_ESCAPED_KEYWORD_ESCAPE = ((Keyword*)(internRigidSymbolWrtModule("ESCAPED-KEYWORD-ESCAPE", NULL, 2)));
    KWD_READ_ESCAPED_KEYWORD = ((Keyword*)(internRigidSymbolWrtModule("ESCAPED-KEYWORD", NULL, 2)));
    KWD_READ_FULLY_ESCAPED_KEYWORD_ESCAPE = ((Keyword*)(internRigidSymbolWrtModule("FULLY-ESCAPED-KEYWORD-ESCAPE", NULL, 2)));
    KWD_READ_FULLY_ESCAPED_SURROGATE = ((Keyword*)(internRigidSymbolWrtModule("FULLY-ESCAPED-SURROGATE", NULL, 2)));
    KWD_READ_ESCAPED_SURROGATE_ESCAPE = ((Keyword*)(internRigidSymbolWrtModule("ESCAPED-SURROGATE-ESCAPE", NULL, 2)));
    KWD_READ_ESCAPED_SURROGATE = ((Keyword*)(internRigidSymbolWrtModule("ESCAPED-SURROGATE", NULL, 2)));
    KWD_READ_FULLY_ESCAPED_SURROGATE_ESCAPE = ((Keyword*)(internRigidSymbolWrtModule("FULLY-ESCAPED-SURROGATE-ESCAPE", NULL, 2)));
    KWD_READ_QUALIFIED_SURROGATE = ((Keyword*)(internRigidSymbolWrtModule("QUALIFIED-SURROGATE", NULL, 2)));
    KWD_READ_QUALIFIED_ESCAPED_SYMBOL_ESCAPE = ((Keyword*)(internRigidSymbolWrtModule("QUALIFIED-ESCAPED-SYMBOL-ESCAPE", NULL, 2)));
    KWD_READ_QUALIFIED_FULLY_ESCAPED_SYMBOL = ((Keyword*)(internRigidSymbolWrtModule("QUALIFIED-FULLY-ESCAPED-SYMBOL", NULL, 2)));
    KWD_READ_QUALIFIED_SYMBOL = ((Keyword*)(internRigidSymbolWrtModule("QUALIFIED-SYMBOL", NULL, 2)));
    KWD_READ_QUALIFIED_ESCAPED_SURROGATE_ESCAPE = ((Keyword*)(internRigidSymbolWrtModule("QUALIFIED-ESCAPED-SURROGATE-ESCAPE", NULL, 2)));
    KWD_READ_QUALIFIED_FULLY_ESCAPED_SURROGATE = ((Keyword*)(internRigidSymbolWrtModule("QUALIFIED-FULLY-ESCAPED-SURROGATE", NULL, 2)));
    KWD_READ_QUALIFIED_ESCAPED_SYMBOL = ((Keyword*)(internRigidSymbolWrtModule("QUALIFIED-ESCAPED-SYMBOL", NULL, 2)));
    KWD_READ_QUALIFIED_ESCAPED_SURROGATE = ((Keyword*)(internRigidSymbolWrtModule("QUALIFIED-ESCAPED-SURROGATE", NULL, 2)));
    KWD_READ_QUALIFIED_FULLY_ESCAPED_SYMBOL_ESCAPE = ((Keyword*)(internRigidSymbolWrtModule("QUALIFIED-FULLY-ESCAPED-SYMBOL-ESCAPE", NULL, 2)));
    KWD_READ_QUALIFIED_FULLY_ESCAPED_SURROGATE_ESCAPE = ((Keyword*)(internRigidSymbolWrtModule("QUALIFIED-FULLY-ESCAPED-SURROGATE-ESCAPE", NULL, 2)));
    KWD_READ_CLOSE_BALANCED_QUOTE = ((Keyword*)(internRigidSymbolWrtModule("CLOSE-BALANCED-QUOTE", NULL, 2)));
    SYM_READ_STELLA_WITH_TOKENIZER = ((Symbol*)(internRigidSymbolWrtModule("WITH-TOKENIZER", NULL, 0)));
    SYM_READ_STELLA_oSTELLA_TOKENIZER_TABLEo = ((Symbol*)(internRigidSymbolWrtModule("*STELLA-TOKENIZER-TABLE*", NULL, 0)));
    SYM_READ_STELLA_TOK_STELLALOGICALSTATENAMES_ = ((Symbol*)(internRigidSymbolWrtModule("TOK_STELLALOGICALSTATENAMES_", NULL, 0)));
    SYM_READ_STELLA_oSTELLA_LOGICAL_STATE_NAMESo = ((Symbol*)(internRigidSymbolWrtModule("*STELLA-LOGICAL-STATE-NAMES*", NULL, 0)));
    SYM_READ_STELLA_TOK_STELLALOGICALSTATENAME_ = ((Symbol*)(internRigidSymbolWrtModule("TOK_STELLALOGICALSTATENAME_", NULL, 0)));
    SYM_READ_STELLA_KEYWORD = ((Symbol*)(internRigidSymbolWrtModule("KEYWORD", NULL, 0)));
    KWD_READ_NONE = ((Keyword*)(internRigidSymbolWrtModule("NONE", NULL, 2)));
    SYM_READ_STELLA_GET_QUALIFIED_SYMBOL_SEPARATOR_POSITION_INTERNAL = ((Symbol*)(internRigidSymbolWrtModule("GET-QUALIFIED-SYMBOL-SEPARATOR-POSITION-INTERNAL", NULL, 0)));
    KWD_READ_FULLY_ESCAPED = ((Keyword*)(internRigidSymbolWrtModule("FULLY-ESCAPED", NULL, 2)));
    SYM_READ_STELLA_GET_TOKEN_INTEGER = ((Symbol*)(internRigidSymbolWrtModule("GET-TOKEN-INTEGER", NULL, 0)));
    SYM_READ_STELLA_GET_TOKEN_INTEGER_INTERNAL = ((Symbol*)(internRigidSymbolWrtModule("GET-TOKEN-INTEGER-INTERNAL", NULL, 0)));
  }
}

void helpStartupRead4() {
  {
    SYM_READ_STELLA_GET_TOKEN_LONG_INTEGER = ((Symbol*)(internRigidSymbolWrtModule("GET-TOKEN-LONG-INTEGER", NULL, 0)));
    SYM_READ_STELLA_GET_TOKEN_LONG_INTEGER_INTERNAL = ((Symbol*)(internRigidSymbolWrtModule("GET-TOKEN-LONG-INTEGER-INTERNAL", NULL, 0)));
    SYM_READ_STELLA_GET_TOKEN_FLOAT = ((Symbol*)(internRigidSymbolWrtModule("GET-TOKEN-FLOAT", NULL, 0)));
    SYM_READ_STELLA_GET_TOKEN_FLOAT_INTERNAL = ((Symbol*)(internRigidSymbolWrtModule("GET-TOKEN-FLOAT-INTERNAL", NULL, 0)));
    SGT_READ_STELLA_STELLA_TOKEN = ((Surrogate*)(internRigidSymbolWrtModule("STELLA-TOKEN", NULL, 1)));
    SYM_READ_STELLA_LOGICAL_TOKEN_TYPE = ((Symbol*)(internRigidSymbolWrtModule("LOGICAL-TOKEN-TYPE", NULL, 0)));
    SYM_READ_STELLA_MODULE = ((Symbol*)(internRigidSymbolWrtModule("MODULE", NULL, 0)));
    SYM_READ_STELLA_ESCAPE_MODE = ((Symbol*)(internRigidSymbolWrtModule("ESCAPE-MODE", NULL, 0)));
    KWD_READ_FULL = ((Keyword*)(internRigidSymbolWrtModule("FULL", NULL, 2)));
    KWD_READ_PARTIAL = ((Keyword*)(internRigidSymbolWrtModule("PARTIAL", NULL, 2)));
    KWD_READ_ESCAPED = ((Keyword*)(internRigidSymbolWrtModule("ESCAPED", NULL, 2)));
    SYM_READ_STELLA_a = ((Symbol*)(internRigidSymbolWrtModule("&", NULL, 0)));
    SYM_READ_STELLA_aa = ((Symbol*)(internRigidSymbolWrtModule("&&", NULL, 0)));
    KWD_READ_TEXT = ((Keyword*)(internRigidSymbolWrtModule("TEXT", NULL, 2)));
    KWD_READ_PUNCTUATION = ((Keyword*)(internRigidSymbolWrtModule("PUNCTUATION", NULL, 2)));
    KWD_READ_QUOTE = ((Keyword*)(internRigidSymbolWrtModule("QUOTE", NULL, 2)));
    KWD_READ_ESCAPE = ((Keyword*)(internRigidSymbolWrtModule("ESCAPE", NULL, 2)));
    SGT_READ_STELLA_F_TOKENIZE_STRING_MEMO_TABLE_000 = ((Surrogate*)(internRigidSymbolWrtModule("F-TOKENIZE-STRING-MEMO-TABLE-000", NULL, 1)));
    KWD_READ_INITIAL_LINEFEED = ((Keyword*)(internRigidSymbolWrtModule("INITIAL-LINEFEED", NULL, 2)));
    KWD_READ_INITIAL_RETURN = ((Keyword*)(internRigidSymbolWrtModule("INITIAL-RETURN", NULL, 2)));
    KWD_READ_LINEFEED = ((Keyword*)(internRigidSymbolWrtModule("LINEFEED", NULL, 2)));
    KWD_READ_RETURN = ((Keyword*)(internRigidSymbolWrtModule("RETURN", NULL, 2)));
    KWD_READ_RETURN_LINEFEED = ((Keyword*)(internRigidSymbolWrtModule("RETURN-LINEFEED", NULL, 2)));
    KWD_READ_LF = ((Keyword*)(internRigidSymbolWrtModule("LF", NULL, 2)));
    KWD_READ_CRLF = ((Keyword*)(internRigidSymbolWrtModule("CRLF", NULL, 2)));
    KWD_READ_CR = ((Keyword*)(internRigidSymbolWrtModule("CR", NULL, 2)));
    KWD_READ_ASK = ((Keyword*)(internRigidSymbolWrtModule("ASK", NULL, 2)));
    KWD_READ_YES = ((Keyword*)(internRigidSymbolWrtModule("YES", NULL, 2)));
    KWD_READ_NO = ((Keyword*)(internRigidSymbolWrtModule("NO", NULL, 2)));
    KWD_READ_YES_VERBOSE = ((Keyword*)(internRigidSymbolWrtModule("YES-VERBOSE", NULL, 2)));
    KWD_READ_NO_VERBOSE = ((Keyword*)(internRigidSymbolWrtModule("NO-VERBOSE", NULL, 2)));
    SYM_READ_STELLA_STARTUP_READ = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-READ", NULL, 0)));
    SYM_READ_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
  }
}

void helpStartupRead5() {
  {
    oSTELLA_TOKENIZER_TABLE_DEFINITIONo = listO(65, listO(6, KWD_READ_START, KWD_READ_INCLUDE, KWD_READ_DELIMITER, KWD_READ_INCLUDE, KWD_READ_ATOM, NIL), listO(31, KWD_READ_DELIMITER, SYM_READ_STELLA_o, wrapString("("), KWD_READ_OPEN_PAREN, SYM_READ_STELLA_o, wrapString(")"), KWD_READ_CLOSE_PAREN, SYM_READ_STELLA_o, wrapString("\""), listO(3, KWD_READ_OPEN_STRING, KWD_READ_STRING, NIL), SYM_READ_STELLA_o, wrapString("'"), KWD_READ_SINGLE_QUOTE, SYM_READ_STELLA_o, wrapString("`"), KWD_READ_BACK_QUOTE, SYM_READ_STELLA_o, wrapString(","), KWD_READ_COMMA, SYM_READ_STELLA_x, wrapString(";"), KWD_READ_COMMENT, SYM_READ_STELLA_x, wrapString("#"), KWD_READ_HASH, SYM_READ_STELLA_x, listO(5, wrapCharacter(' '), wrapCharacter('\t'), wrapCharacter('\n'), wrapCharacter('\r'), NIL), KWD_READ_WHITE_SPACE, KWD_READ_EOF, KWD_READ_EOF, NIL), listO(4, KWD_READ_WHITE_SPACE, KWD_READ_INCLUDE, KWD_READ_START, NIL), listO(8, KWD_READ_COMMENT, listO(3, wrapCharacter('\n'), wrapCharacter('\r'), NIL), KWD_READ_START, KWD_READ_EOF, KWD_READ_EOF, KWD_READ_OTHERWISE, KWD_READ_COMMENT, NIL), listO(8, KWD_READ_PAREN_COMMENT, wrapString("\\"), KWD_READ_PAREN_COMMENT_ESCAPE, wrapString("|"), KWD_READ_PAREN_COMMENT_BAR, KWD_READ_OTHERWISE, KWD_READ_PAREN_COMMENT, NIL), listO(4, KWD_READ_PAREN_COMMENT_ESCAPE, KWD_READ_ANY, KWD_READ_PAREN_COMMENT, NIL), listO(10, KWD_READ_PAREN_COMMENT_BAR, wrapString("#"), KWD_READ_START, wrapString("\\"), KWD_READ_PAREN_COMMENT_ESCAPE, wrapString("|"), KWD_READ_PAREN_COMMENT_BAR, KWD_READ_OTHERWISE, KWD_READ_PAREN_COMMENT, NIL), listO(4, KWD_READ_OPEN_PAREN, KWD_READ_INCLUDE, KWD_READ_START, NIL), listO(4, KWD_READ_CLOSE_PAREN, KWD_READ_INCLUDE, KWD_READ_START, NIL), listO(4, KWD_READ_SINGLE_QUOTE, KWD_READ_INCLUDE, KWD_READ_START, NIL), listO(4, KWD_READ_BACK_QUOTE, KWD_READ_INCLUDE, KWD_READ_START, NIL), listO(33, KWD_READ_COMMA, wrapString("."), KWD_READ_COMMA_SPLICE, KWD_READ_INCLUDE, KWD_READ_DELIMITER, SYM_READ_STELLA_o, wrapString("-+"), listO(3, KWD_READ_SYMBOL_OR_SIGNED_NUMBER, KWD_READ_SYMBOL, NIL), SYM_READ_STELLA_o, wrapString("0123456789"), listO(3, KWD_READ_SYMBOL_OR_NUMBER, KWD_READ_INTEGER, NIL), SYM_READ_STELLA_o, wrapString("cC"), listO(3, KWD_READ_SYMBOL_OR_CL_SYMBOL, KWD_READ_SYMBOL, NIL), SYM_READ_STELLA_o, wrapString("|"), listO(3, KWD_READ_OPEN_FULLY_ESCAPED_SYMBOL, KWD_READ_FULLY_ESCAPED_SYMBOL, NIL), SYM_READ_STELLA_o, wrapString("\\"), KWD_READ_ESCAPED_SYMBOL_ESCAPE, SYM_READ_STELLA_o, wrapString("/"), KWD_READ_QUALIFIED_NAME, SYM_READ_STELLA_o, wrapString(":"), listO(3, KWD_READ_OPEN_KEYWORD, KWD_READ_KEYWORD, NIL), SYM_READ_STELLA_o, wrapString("@"), listO(3, KWD_READ_OPEN_SURROGATE, KWD_READ_SURROGATE, NIL), SYM_READ_STELLA_o, KWD_READ_OTHERWISE, KWD_READ_SYMBOL, NIL), listO(4, KWD_READ_COMMA_SPLICE, KWD_READ_INCLUDE, KWD_READ_START, NIL), listO(9, KWD_READ_OPEN_STRING, SYM_READ_STELLA_o, wrapString("\""), KWD_READ_CLOSE_STRING, wrapString("\\"), KWD_READ_STRING_ESCAPE, KWD_READ_OTHERWISE, KWD_READ_STRING, NIL), listO(9, KWD_READ_STRING, SYM_READ_STELLA_o, wrapString("\""), KWD_READ_CLOSE_STRING, wrapString("\\"), KWD_READ_STRING_ESCAPE, KWD_READ_OTHERWISE, KWD_READ_STRING, NIL), listO(4, KWD_READ_CLOSE_STRING, KWD_READ_INCLUDE, KWD_READ_START, NIL), listO(4, KWD_READ_STRING_ESCAPE, KWD_READ_ANY, KWD_READ_ESCAPED_STRING, NIL), listO(9, KWD_READ_ESCAPED_STRING, SYM_READ_STELLA_o, wrapString("\""), KWD_READ_CLOSE_STRING, wrapString("\\"), KWD_READ_STRING_ESCAPE, KWD_READ_OTHERWISE, KWD_READ_ESCAPED_STRING, NIL), listO(6, KWD_READ_HASH, wrapString("\\"), KWD_READ_CHARACTER_CONSTANT, wrapString("|"), KWD_READ_PAREN_COMMENT, NIL), listO(5, KWD_READ_CHARACTER_CONSTANT, SYM_READ_STELLA_o, KWD_READ_ANY, KWD_READ_CHARACTER, NIL), listO(6, KWD_READ_CHARACTER, KWD_READ_INCLUDE, KWD_READ_DELIMITER, KWD_READ_OTHERWISE, KWD_READ_CHARACTER, NIL), listO(32, KWD_READ_ATOM, SYM_READ_STELLA_o, wrapString("-+"), listO(3, KWD_READ_SYMBOL_OR_SIGNED_NUMBER, KWD_READ_SYMBOL, NIL), SYM_READ_STELLA_o, wrapString("0123456789"), listO(3, KWD_READ_SYMBOL_OR_NUMBER, KWD_READ_INTEGER, NIL), SYM_READ_STELLA_o, wrapString("."), listO(3, KWD_READ_SYMBOL_OR_MANTISSA, KWD_READ_SYMBOL, NIL), SYM_READ_STELLA_o, wrapString("cC"), listO(3, KWD_READ_SYMBOL_OR_CL_SYMBOL, KWD_READ_SYMBOL, NIL), SYM_READ_STELLA_o, wrapString("|"), listO(3, KWD_READ_OPEN_FULLY_ESCAPED_SYMBOL, KWD_READ_FULLY_ESCAPED_SYMBOL, NIL), SYM_READ_STELLA_o, wrapString("\\"), KWD_READ_ESCAPED_SYMBOL_ESCAPE, SYM_READ_STELLA_o, wrapString("/"), KWD_READ_QUALIFIED_NAME, SYM_READ_STELLA_o, wrapString(":"), listO(3, KWD_READ_OPEN_KEYWORD, KWD_READ_KEYWORD, NIL), SYM_READ_STELLA_o, wrapString("@"), listO(3, KWD_READ_OPEN_SURROGATE, KWD_READ_SURROGATE, NIL), SYM_READ_STELLA_o, KWD_READ_OTHERWISE, KWD_READ_SYMBOL, NIL), listO(16, KWD_READ_SYMBOL_OR_SIGNED_NUMBER, KWD_READ_INCLUDE, KWD_READ_DELIMITER, wrapString("/"), KWD_READ_QUALIFIED_NAME, wrapString("\\"), KWD_READ_ESCAPED_SYMBOL_ESCAPE, wrapString("0123456789"), listO(3, KWD_READ_SYMBOL_OR_NUMBER, KWD_READ_INTEGER, NIL), wrapString("."), listO(3, KWD_READ_SYMBOL_OR_MANTISSA, KWD_READ_SYMBOL, NIL), wrapString("|"), KWD_READ_ERROR, KWD_READ_OTHERWISE, KWD_READ_SYMBOL, NIL), listO(18, KWD_READ_SYMBOL_OR_NUMBER, KWD_READ_INCLUDE, KWD_READ_DELIMITER, wrapString("/"), KWD_READ_QUALIFIED_NAME, wrapString("\\"), KWD_READ_ESCAPED_SYMBOL_ESCAPE, wrapString("0123456789"), listO(3, KWD_READ_SYMBOL_OR_NUMBER, KWD_READ_INTEGER, NIL), wrapString("."), listO(3, KWD_READ_SYMBOL_OR_MANTISSA2, KWD_READ_FLOAT, NIL), wrapString("eE"), listO(3, KWD_READ_SYMBOL_OR_EXPONENT_DELIMITER, KWD_READ_SYMBOL, NIL), wrapString("|"), KWD_READ_ERROR, KWD_READ_OTHERWISE, KWD_READ_SYMBOL, NIL), listO(16, KWD_READ_SYMBOL_OR_MANTISSA, KWD_READ_INCLUDE, KWD_READ_DELIMITER, wrapString("/"), KWD_READ_QUALIFIED_NAME, wrapString("\\"), KWD_READ_ESCAPED_SYMBOL_ESCAPE, wrapString("0123456789"), listO(3, KWD_READ_SYMBOL_OR_MANTISSA2, KWD_READ_FLOAT, NIL), wrapString("eE"), listO(3, KWD_READ_SYMBOL_OR_EXPONENT_DELIMITER, KWD_READ_SYMBOL, NIL), wrapString("|"), KWD_READ_ERROR, KWD_READ_OTHERWISE, KWD_READ_SYMBOL, NIL), listO(4, KWD_READ_SYMBOL_OR_MANTISSA2, KWD_READ_INCLUDE, KWD_READ_SYMBOL_OR_MANTISSA, NIL), listO(16, KWD_READ_SYMBOL_OR_EXPONENT_DELIMITER, KWD_READ_INCLUDE, KWD_READ_DELIMITER, wrapString("/"), KWD_READ_QUALIFIED_NAME, wrapString("\\"), KWD_READ_ESCAPED_SYMBOL_ESCAPE, wrapString("+-"), listO(3, KWD_READ_SYMBOL_OR_EXPONENT, KWD_READ_SYMBOL, NIL), wrapString("0123456789"), listO(3, KWD_READ_SYMBOL_OR_EXPONENT2, KWD_READ_FLOAT, NIL), wrapString("|"), KWD_READ_ERROR, KWD_READ_OTHERWISE, KWD_READ_SYMBOL, NIL), listO(14, KWD_READ_SYMBOL_OR_EXPONENT, KWD_READ_INCLUDE, KWD_READ_DELIMITER, wrapString("/"), KWD_READ_QUALIFIED_NAME, wrapString("\\"), KWD_READ_ESCAPED_SYMBOL_ESCAPE, wrapString("0123456789"), listO(3, KWD_READ_SYMBOL_OR_EXPONENT2, KWD_READ_FLOAT, NIL), wrapString("|"), KWD_READ_ERROR, KWD_READ_OTHERWISE, KWD_READ_SYMBOL, NIL), listO(4, KWD_READ_SYMBOL_OR_EXPONENT2, KWD_READ_INCLUDE, KWD_READ_SYMBOL_OR_EXPONENT, NIL), listO(14, KWD_READ_SYMBOL_OR_CL_SYMBOL, KWD_READ_INCLUDE, KWD_READ_DELIMITER, wrapString("/"), KWD_READ_QUALIFIED_NAME, wrapString("\\"), KWD_READ_ESCAPED_SYMBOL_ESCAPE, wrapString("lL"), listO(3, KWD_READ_SYMBOL_OR_CL_SYMBOL2, KWD_READ_SYMBOL, NIL), wrapString("|"), KWD_READ_ERROR, KWD_READ_OTHERWISE, KWD_READ_SYMBOL, NIL), listO(14, KWD_READ_SYMBOL_OR_CL_SYMBOL2, KWD_READ_INCLUDE, KWD_READ_DELIMITER, wrapString("/"), KWD_READ_QUALIFIED_NAME, wrapString("\\"), KWD_READ_ESCAPED_SYMBOL_ESCAPE, wrapString(":"), listO(3, KWD_READ_SYMBOL_OR_CL_SYMBOL3, KWD_READ_SYMBOL, NIL), wrapString("|"), KWD_READ_ERROR, KWD_READ_OTHERWISE, KWD_READ_SYMBOL, NIL), listO(8, KWD_READ_SYMBOL_OR_CL_SYMBOL3, KWD_READ_INCLUDE, KWD_READ_DELIMITER, wrapString("|"), KWD_READ_ERROR, KWD_READ_OTHERWISE, KWD_READ_CL_SYMBOL, NIL), listO(8, KWD_READ_CL_SYMBOL, KWD_READ_INCLUDE, KWD_READ_DELIMITER, wrapString("|"), KWD_READ_ERROR, KWD_READ_OTHERWISE, KWD_READ_CL_SYMBOL, NIL), listO(4, KWD_READ_ESCAPED_SYMBOL_ESCAPE, KWD_READ_ANY, KWD_READ_ESCAPED_SYMBOL, NIL), listO(10, KWD_READ_ESCAPED_SYMBOL, KWD_READ_INCLUDE, KWD_READ_DELIMITER, wrapString("/|"), KWD_READ_ERROR, wrapString("\\"), KWD_READ_ESCAPED_SYMBOL_ESCAPE, KWD_READ_OTHERWISE, KWD_READ_ESCAPED_SYMBOL, NIL), listO(9, KWD_READ_OPEN_FULLY_ESCAPED_SYMBOL, SYM_READ_STELLA_o, wrapString("|"), KWD_READ_CLOSE_FULLY_ESCAPED_NAME, wrapString("\\"), KWD_READ_FULLY_ESCAPED_SYMBOL_ESCAPE, KWD_READ_OTHERWISE, KWD_READ_FULLY_ESCAPED_SYMBOL, NIL), listO(4, KWD_READ_FULLY_ESCAPED_SYMBOL_ESCAPE, KWD_READ_ANY, KWD_READ_FULLY_ESCAPED_SYMBOL, NIL), listO(9, KWD_READ_FULLY_ESCAPED_SYMBOL, SYM_READ_STELLA_o, wrapString("|"), KWD_READ_CLOSE_FULLY_ESCAPED_NAME, wrapString("\\"), KWD_READ_FULLY_ESCAPED_SYMBOL_ESCAPE, KWD_READ_OTHERWISE, KWD_READ_FULLY_ESCAPED_SYMBOL, NIL), listO(4, KWD_READ_CLOSE_FULLY_ESCAPED_NAME, KWD_READ_INCLUDE, KWD_READ_START, NIL), listO(12, KWD_READ_SYMBOL, KWD_READ_INCLUDE, KWD_READ_DELIMITER, wrapString("/"), KWD_READ_QUALIFIED_NAME, wrapString("\\"), KWD_READ_ESCAPED_SYMBOL_ESCAPE, wrapString("|"), KWD_READ_ERROR, KWD_READ_OTHERWISE, KWD_READ_SYMBOL, NIL), listO(10, KWD_READ_OPEN_KEYWORD, KWD_READ_INCLUDE, KWD_READ_DELIMITER, wrapString("|"), KWD_READ_FULLY_ESCAPED_KEYWORD, wrapString("\\"), KWD_READ_ESCAPED_KEYWORD_ESCAPE, KWD_READ_OTHERWISE, KWD_READ_KEYWORD, NIL), listO(10, KWD_READ_KEYWORD, KWD_READ_INCLUDE, KWD_READ_DELIMITER, wrapString("\\"), KWD_READ_ESCAPED_KEYWORD_ESCAPE, wrapString("|"), KWD_READ_ERROR, KWD_READ_OTHERWISE, KWD_READ_KEYWORD, NIL), listO(4, KWD_READ_ESCAPED_KEYWORD_ESCAPE, KWD_READ_ANY, KWD_READ_ESCAPED_KEYWORD, NIL), listO(10, KWD_READ_ESCAPED_KEYWORD, KWD_READ_INCLUDE, KWD_READ_DELIMITER, wrapString("\\"), KWD_READ_ESCAPED_KEYWORD_ESCAPE, wrapString("|"), KWD_READ_ERROR, KWD_READ_OTHERWISE, KWD_READ_ESCAPED_KEYWORD, NIL), listO(9, KWD_READ_FULLY_ESCAPED_KEYWORD, SYM_READ_STELLA_o, wrapString("|"), KWD_READ_CLOSE_FULLY_ESCAPED_NAME, wrapString("\\"), KWD_READ_FULLY_ESCAPED_KEYWORD_ESCAPE, KWD_READ_OTHERWISE, KWD_READ_FULLY_ESCAPED_KEYWORD, NIL), listO(4, KWD_READ_FULLY_ESCAPED_KEYWORD_ESCAPE, KWD_READ_ANY, KWD_READ_FULLY_ESCAPED_KEYWORD, NIL), listO(10, KWD_READ_OPEN_SURROGATE, KWD_READ_INCLUDE, KWD_READ_DELIMITER, wrapString("|"), KWD_READ_FULLY_ESCAPED_SURROGATE, wrapString("\\"), KWD_READ_ESCAPED_SURROGATE_ESCAPE, KWD_READ_OTHERWISE, KWD_READ_SURROGATE, NIL), listO(10, KWD_READ_SURROGATE, KWD_READ_INCLUDE, KWD_READ_DELIMITER, wrapString("/|"), KWD_READ_ERROR, wrapString("\\"), KWD_READ_ESCAPED_SURROGATE_ESCAPE, KWD_READ_OTHERWISE, KWD_READ_SURROGATE, NIL), listO(10, KWD_READ_ESCAPED_SURROGATE, KWD_READ_INCLUDE, KWD_READ_DELIMITER, wrapString("/|"), KWD_READ_ERROR, wrapString("\\"), KWD_READ_ESCAPED_SURROGATE_ESCAPE, KWD_READ_OTHERWISE, KWD_READ_ESCAPED_SURROGATE, NIL), listO(4, KWD_READ_ESCAPED_SURROGATE_ESCAPE, KWD_READ_ANY, KWD_READ_ESCAPED_SURROGATE, NIL), listO(9, KWD_READ_FULLY_ESCAPED_SURROGATE, SYM_READ_STELLA_o, wrapString("|"), KWD_READ_CLOSE_FULLY_ESCAPED_NAME, wrapString("\\"), KWD_READ_FULLY_ESCAPED_SURROGATE_ESCAPE, KWD_READ_OTHERWISE, KWD_READ_FULLY_ESCAPED_SURROGATE, NIL), listO(4, KWD_READ_FULLY_ESCAPED_SURROGATE_ESCAPE, KWD_READ_ANY, KWD_READ_FULLY_ESCAPED_SURROGATE, NIL), listO(16, KWD_READ_QUALIFIED_NAME, KWD_READ_INCLUDE, KWD_READ_DELIMITER, wrapString("@"), KWD_READ_QUALIFIED_SURROGATE, wrapString(":"), KWD_READ_ERROR, wrapString("\\"), KWD_READ_QUALIFIED_ESCAPED_SYMBOL_ESCAPE, wrapString("|"), KWD_READ_QUALIFIED_FULLY_ESCAPED_SYMBOL, wrapString("/"), KWD_READ_QUALIFIED_NAME, KWD_READ_OTHERWISE, KWD_READ_QUALIFIED_SYMBOL, NIL), listO(12, KWD_READ_QUALIFIED_SYMBOL, KWD_READ_INCLUDE, KWD_READ_DELIMITER, wrapString("/"), KWD_READ_QUALIFIED_NAME, wrapString("\\"), KWD_READ_QUALIFIED_ESCAPED_SYMBOL_ESCAPE, wrapString("|"), KWD_READ_ERROR, KWD_READ_OTHERWISE, KWD_READ_QUALIFIED_SYMBOL, NIL), listO(12, KWD_READ_QUALIFIED_SURROGATE, KWD_READ_INCLUDE, KWD_READ_DELIMITER, wrapString("/"), KWD_READ_ERROR, wrapString("\\"), KWD_READ_QUALIFIED_ESCAPED_SURROGATE_ESCAPE, wrapString("|"), KWD_READ_QUALIFIED_FULLY_ESCAPED_SURROGATE, KWD_READ_OTHERWISE, KWD_READ_QUALIFIED_SURROGATE, NIL), listO(10, KWD_READ_QUALIFIED_ESCAPED_SYMBOL, KWD_READ_INCLUDE, KWD_READ_DELIMITER, wrapString("/|"), KWD_READ_ERROR, wrapString("\\"), KWD_READ_QUALIFIED_ESCAPED_SYMBOL_ESCAPE, KWD_READ_OTHERWISE, KWD_READ_QUALIFIED_ESCAPED_SYMBOL, NIL), listO(4, KWD_READ_QUALIFIED_ESCAPED_SYMBOL_ESCAPE, KWD_READ_ANY, KWD_READ_QUALIFIED_ESCAPED_SYMBOL, NIL), listO(10, KWD_READ_QUALIFIED_ESCAPED_SURROGATE, KWD_READ_INCLUDE, KWD_READ_DELIMITER, wrapString("/|"), KWD_READ_ERROR, wrapString("\\"), KWD_READ_QUALIFIED_ESCAPED_SURROGATE_ESCAPE, KWD_READ_OTHERWISE, KWD_READ_QUALIFIED_ESCAPED_SURROGATE, NIL), listO(4, KWD_READ_QUALIFIED_ESCAPED_SURROGATE_ESCAPE, KWD_READ_ANY, KWD_READ_QUALIFIED_ESCAPED_SURROGATE, NIL), listO(9, KWD_READ_QUALIFIED_FULLY_ESCAPED_SYMBOL, SYM_READ_STELLA_o, wrapString("|"), KWD_READ_CLOSE_FULLY_ESCAPED_NAME, wrapString("\\"), KWD_READ_QUALIFIED_FULLY_ESCAPED_SYMBOL_ESCAPE, KWD_READ_OTHERWISE, KWD_READ_QUALIFIED_FULLY_ESCAPED_SYMBOL, NIL), listO(4, KWD_READ_QUALIFIED_FULLY_ESCAPED_SYMBOL_ESCAPE, KWD_READ_ANY, KWD_READ_QUALIFIED_FULLY_ESCAPED_SYMBOL, NIL), listO(9, KWD_READ_QUALIFIED_FULLY_ESCAPED_SURROGATE, SYM_READ_STELLA_o, wrapString("|"), KWD_READ_CLOSE_FULLY_ESCAPED_NAME, wrapString("\\"), KWD_READ_QUALIFIED_FULLY_ESCAPED_SURROGATE_ESCAPE, KWD_READ_OTHERWISE, KWD_READ_QUALIFIED_FULLY_ESCAPED_SURROGATE, NIL), listO(4, KWD_READ_QUALIFIED_FULLY_ESCAPED_SURROGATE_ESCAPE, KWD_READ_ANY, KWD_READ_QUALIFIED_FULLY_ESCAPED_SURROGATE, NIL), listO(4, KWD_READ_ERROR, KWD_READ_INCLUDE, KWD_READ_START, NIL), NIL);
    oSTELLA_TOKENIZER_TABLEo = unstringifyTokenizerTable("32768|EJEJEJEJEJEJEJEJEJKMKMEJEJKMEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJKMEJEIJMEJEJEJFICIDIEJLIHILINIBJMIMIMIMIMIMIMIMIMIMICJIMEJEJEJEJDJEJEJOIEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJAJEJEJEJGIEJEJOIEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJPIEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJKMKMEJEJKMEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJKMEJEIJMEJEJEJFICIDIEJLIHILINIBJMIMIMIMIMIMIMIMIMIMICJIMEJEJEJEJDJEJEJOIEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJAJEJEJEJGIEJEJOIEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJPIEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJE" "JEJEJEJEJEJEJEJEJEJEJEJEJKMKMEJEJKMEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJKMEJEIJMEJEJEJFICIDIEJLIHILINIBJMIMIMIMIMIMIMIMIMIMICJIMEJEJEJEJDJEJEJOIEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJAJEJEJEJGIEJEJOIEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJPIEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJKMKMEJEJKMEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJKMEJEIJMEJEJEJFICIDIEJLIHILINIBJMIMIMIMIMIMIMIMIMIMICJIMEJEJEJEJDJEJEJOIEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJAJEJEJEJGIEJEJOIEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJPIEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJ" "EJEJEJEJMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBKJMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBLBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBEJEJEJEJEJEJEJEJEJKMKMEJEJKMEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJKMEJEIJMEJEJEJFICIDIEJLIHILINIBJMIMIMIMIMIMIMIMIMIMICJIMEJEJEJEJDJEJEJOIEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJAJEJEJEJGIEJEJOIEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJPIEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJE" "JEJEJEJEJEJEJEJEJEJEJEJEJEJKMKMEJEJKMEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJKMEJEIJMEJEJEJFICIDIEJLIHILINIBJMIMIMIMIMIMIMIMIMIMICJIMEJEJEJEJDJEJEJOIEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJAJEJEJEJGIEJEJOIEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJPIEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJKMKMEJEJKMEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJKMEJEIJMEJEJEJFICIDIEJLIHILIJBBJMIMIMIMIMIMIMIMIMIMICJIMEJEJEJEJDJEJEJOIEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJAJEJEJEJGIEJEJOIEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJPIEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJ" "EJEJEJEJEJIAIAIAIAIAIAIAIAIAIABAIAIABAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAOBAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAGBAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" "AAAAAAAAAAAEJEJEJEJEJEJEJEJEJKMKMEJEJKMEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJKMEJEIJMEJEJEJFICIDIEJLIHILINIBJMIMIMIMIMIMIMIMIMIMICJIMEJEJEJEJDJEJEJOIEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJAJEJEJEJGIEJEJOIEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJPIEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEBEBEBEBEBEBEBEBEBKMKMEBEBKMEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBKMEBEIJMEBEBEBFICIDIEBEBHIEBNABBMAMAMAMAMAMAMAMAMAMAEBIMEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBABEBEBEBGIEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBAAEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEB" "EBEBEBEBEBEBEBEBEBEBEBEBEBEBEBKMKMEBEBKMEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBKMEBEIJMEBEBEBFICIDIEBEBHIEBBCBBMAMAMAMAMAMAMAMAMAMAEBIMEBEBEBEBEBEBEBEBEBCCEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBABEBEBEBGIEBEBEBEBCCEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBAAEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBKMKMEBEBKMEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBKMEBEIJMEBEBEBFICIDIEBEBHIEBEBBBBCBCBCBCBCBCBCBCBCBCEBIMEBEBEBEBEBEBEBEBEBCCEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBABEBEBEBGIEBEBEBEBCCEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBAAEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBE" "BEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBKMKMEBEBKMEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBKMEBEIJMEBEBEBFICIDIEBEBHIEBEBBBEBEBEBEBEBEBEBEBEBEBEBIMEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBFCEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBABEBEBEBGIEBEBEBEBEBEBEBEBEBEBEBFCEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBAAEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCKCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCJKLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLC" "LCLCLCLCLCLCLCICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICJDJDJDJDJDJDJDJDJDKMKMJDJDKMJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDKMJDEIJMJDJDJDFICIDIJDJDHIJDJDBBJDJDJDJDJDJDJDJDJDJDAAIMJDJDJDJDGDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDHDJDJDJDGIJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDIDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJ" "DJDJDJDJDJDJDJDOCOCOCOCOCOCOCOCOCKMKMOCOCKMOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCKMOCEIJMOCOCOCFICIDIOCOCHIOCOCOCOCOCOCOCOCOCOCOCOCOCOCIMOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCNCOCOCOCGIOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCMCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCDDDDDDDDDDDDDDDDDDKMKMDDDDKMDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDKMDDEIJMDDDDDDFICIDIDDDDHIDDDDDDDDDDDDDDDDDDDDDDDDDDDDIMDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDCDDDDDDDGIDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDBDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD" "DDDDDDDDDDDDDDDDEBEBEBEBEBEBEBEBEBKMKMEBEBKMEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBKMEBEIJMEBEBEBFICIDIEBEBHIEBEBBBEBEBEBEBEBEBEBEBEBEBEBIMEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBABEBEBEBGIEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBAAEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBAAAAAAAAAAAAAAAAAAKMKMAAAAKMAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAKMAAEIJMAAAAAAFICIDIAAAAHIAAAAAAAAAAAAAAAAAAAAAAAAAAAAIMAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAGIAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" "AAAAAAAAAAAAAAAAAGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBHBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBIBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGB" "GBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBBAGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBHBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBIBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBGBEJEJEJEJEJEJEJEJEJKMKMEJEJKMEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJKMEJEIJMEJEJEJFICIDIEJLIHILINIBJMIMIMIMIMIMIMIMIMIMICJIMEJEJEJEJDJEJEJOIEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJAJEJEJEJGIEJEJOIEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJPIEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJE" "JEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJKMKMEJEJKMEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJKMEJEIJMEJEJEJFICIDIEJLIHILINIBJMIMIMIMIMIMIMIMIMIMICJIMEJEJEJEJDJEJEJOIEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJAJEJEJEJGIEJEJOIEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJPIEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNB" "NBNBNBNBNBNBNBNBNBNBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBKJMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBLBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBMBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBKJNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBLBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBNBN" "BNBNBNBNBNBNBNBNBNBNBPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPJPBPBPBPBPBPBPBPBPBKMKMPBPBKMPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBKMPBEIJMPBPBPBFICIDIPBPBHIPBPBPBPBPBPBPBPBPBPBPBPBPBPBIMPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBGIPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPBPB" "PBPBPBPBPBPBPBPBPBPBPBEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJLIEJLINIBJMIMIMIMIMIMIMIMIMIMICJEJEJEJEJEJDJEJEJOIEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJAJEJEJEJEJEJEJOIEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJPIEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEBEBEBEBEBEBEBEBEBKMKMEBEBKMEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBKMEBEIJMEBEBEBFICIDIEBEBHIEBEBBBBCBCBCBCBCBCBCBCBCBCEBIMEBEBEBEBEBEBEBEBEBCCEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBABEBEBEBGIEBEBEBEBCCEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBAAEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBE" "BEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBKMKMEBEBKMEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBKMEBEIJMEBEBEBFICIDIEBDCHIDCEBBBECECECECECECECECECECEBIMEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBABEBEBEBGIEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBAAEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBKMKMEBEBKMEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBKMEBEIJMEBEBEBFICIDIEBEBHIEBEBBBECECECECECECECECECECEBIMEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBABEBEBEBGIEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBAAEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEB" "EBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBKMKMEBEBKMEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBKMEBEIJMEBEBEBFICIDIEBEBHIEBEBBBECECECECECECECECECECEBIMEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBABEBEBEBGIEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBAAEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBKMKMEBEBKMEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBKMEBEIJMEBEBEBFICIDIEBEBHIEBEBBBEBEBEBEBEBEBEBEBEBEBGCIMEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBABEBEBEBGIEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBAAEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBEBE" "BEBEBEBEBEBEBEBEBEBEBEBEBHCHCHCHCHCHCHCHCHCKMKMHCHCKMHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCKMHCEIJMHCHCHCFICIDIHCHCHIHCHCHCHCHCHCHCHCHCHCHCHCHCHCIMHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCGIHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCAAHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCKMKMHCHCKMHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCKMHCEIJMHCHCHCFICIDIHCHCHIHCHCHCHCHCHCHCHCHCHCHCHCHCHCIMHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCGIHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCAAHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHCHC" "HCHCHCHCHCHCHCHCHCHCHCHCHCICICICICICICICICICKMKMICICKMICICICICICICICICICICICICICICICICICICKMICEIJMICICICFICIDIICICHIICICAAICICICICICICICICICICICIMICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICABICICICGIICICICICICICICICICICICICICICICICICICICICICICICICICICICAAICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICICEJEJEJEJEJEJEJEJEJKMKMEJEJKMEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJKMEJEIJMEJEJEJFICIDIEJLIHILINIBJMIMIMIMIMIMIMIMIMIMICJIMEJEJEJEJDJEJEJOIEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJAJEJEJEJGIEJEJOIEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJPIEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJEJE" "JEJEJEJEJEJEJEJEJEJEJEJEJEJLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCKCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCJKLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLCLC" "LCLCLCLCLCLCLCLCLCLCLCLCLCLCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCADMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCJKMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCP" "CPCPCPCPCPCPCPCPCPCPCPCPCPCPCOCOCOCOCOCOCOCOCOCKMKMOCOCKMOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCKMOCEIJMOCOCOCFICIDIOCOCHIOCOCOCOCOCOCOCOCOCOCOCOCOCOCIMOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCNCOCOCOCGIOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCAAOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCOCPCPCPCPCPCPCPCPCPCKMKMPCPCKMPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCKMPCEIJMPCPCPCFICIDIPCPCHIPCPCPCPCPCPCPCPCPCPCPCPCPCPCIMPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCNCPCPCPCGIPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCAAPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPCPC" "PCPCPCPCPCPCPCPCPCPCPCPCPCPCPCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCMCBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDFDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDJKBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDB" "DBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDDDDDDDDDDDDDDDDDDDKMKMDDDDKMDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDKMDDEIJMDDDDDDFICIDIDDDDHIDDDDAADDDDDDDDDDDDDDDDDDDDDDIMDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDCDDDDDDDGIDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDAADDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD" "DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDEDEDEDEDEDEDEDEDEDKMKMEDEDKMEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDKMEDEIJMEDEDEDFICIDIEDEDHIEDEDAAEDEDEDEDEDEDEDEDEDEDEDIMEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDCDEDEDEDGIEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDAAEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDB" "DBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDBDGDGDGDGDGDGDGDGDGDKMKMGDGDKMGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDKMGDEIJMGDGDGDFICIDIGDGDHIGDGDAAGDGDGDGDGDGDGDGDGDGDGDIMGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDKDGDGDGDGIGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDLDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDGDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMD" "MDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDODIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDJKIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDJDJDJDJDJDJDJDJDJDKMKMJDJDKMJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDKMJDEIJMJDJDJDFICIDIJDJDHIJDJDBBJDJDJDJDJDJDJDJDJDJDJDIMJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDHDJDJDJDGIJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDAAJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJ" "DJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDJDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDPDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDJKLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLD" "LDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDMDMDMDMDMDMDMDMDMDKMKMMDMDKMMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDKMMDEIJMMDMDMDFICIDIMDMDHIMDMDAAMDMDMDMDMDMDMDMDMDMDMDIMMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDHDMDMDMDGIMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDAAMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDMDNDNDNDNDNDNDNDNDNDKMKMNDNDKMNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDKMNDEIJMNDNDNDFICIDINDNDHINDNDAANDNDNDNDNDNDNDNDNDNDNDIMNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDKDNDNDNDGINDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDAANDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDN" "DNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDNDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDIDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLD" "LDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLDLD|64|ERROR|START|OPEN-PAREN|CLOSE-PAREN|OPEN-STRING|SINGLE-QUOTE|BACK-QUOTE|COMMA|COMMENT|HASH|WHITE-SPACE|SYMBOL-OR-SIGNED-NUMBER|SYMBOL-OR-NUMBER|SYMBOL-OR-MANTISSA|SYMBOL-OR-CL-SYMBOL|OPEN-FULLY-ESCAPED-SYMBOL|ESCAPED-SYMBOL-ESCAPE|QUALIFIED-NAME|OPEN-KEYWORD|OPEN-SURROGATE|SYMBOL|DELIMITER|PAREN-COMMENT|PAREN-COMMENT-ESCAPE|PAREN-COMMENT-BAR|COMMA-SPLICE|CLOSE-STRING|STRING-ESCAPE|STRING|ESCAPED-STRING|CHARACTER-CONSTANT|CHARACTER|ATOM|SYMBOL-OR-MANTISSA2|SYMBOL-OR-EXPONENT-DELIMITER|SYMBOL-OR-EXPONENT|SYMBOL-OR-EXPONENT2|SYMBOL-OR-CL-SYMBOL2|SYMBOL-OR-CL-SYMBOL3|CL-SYMBOL|ESCAPED-SYMBOL|CLOSE-FULLY-ESCAPED-NAME|FULLY-ESCAPED-SYMBOL-ESCAPE|FULLY-ESCAPED-SYMBOL|FULLY-ESCAPED-KEYWORD|ESCAPED-KEYWORD-ESCAPE|KEYWORD|ESCAPED-KEYWORD|FULLY-ESCAPED-KEYWORD-ESCAPE|FULLY-ESCAPED-SURROGATE|ESCAPED-SURROGATE-ESCAPE|SURROGATE|ESCAPED-SURROGATE|FULLY-ESCAPED-SURROGATE-ESCAPE|QUALIFIED-SURROGATE|QUALIFIED-ESCAPED-SYMBOL-ESCAPE|QUALIFIED-FULLY-ESCAPED-SYMBOL|QUALIFIED-SYMBOL|QUALIFI" "ED-ESCAPED-SURROGATE-ESCAPE|QUALIFIED-FULLY-ESCAPED-SURROGATE|QUALIFIED-ESCAPED-SYMBOL|QUALIFIED-ESCAPED-SURROGATE|QUALIFIED-FULLY-ESCAPED-SYMBOL-ESCAPE|QUALIFIED-FULLY-ESCAPED-SURROGATE-ESCAPE|64|ERROR|START|OPEN-PAREN|CLOSE-PAREN|STRING|SINGLE-QUOTE|BACK-QUOTE|COMMA|COMMENT|HASH|WHITE-SPACE|SYMBOL|INTEGER|SYMBOL|SYMBOL|FULLY-ESCAPED-SYMBOL|ESCAPED-SYMBOL-ESCAPE|QUALIFIED-NAME|KEYWORD|SURROGATE|SYMBOL|DELIMITER|PAREN-COMMENT|PAREN-COMMENT-ESCAPE|PAREN-COMMENT-BAR|COMMA-SPLICE|CLOSE-STRING|STRING-ESCAPE|STRING|ESCAPED-STRING|CHARACTER-CONSTANT|CHARACTER|ATOM|FLOAT|SYMBOL|SYMBOL|FLOAT|SYMBOL|SYMBOL|CL-SYMBOL|ESCAPED-SYMBOL|CLOSE-FULLY-ESCAPED-NAME|FULLY-ESCAPED-SYMBOL-ESCAPE|FULLY-ESCAPED-SYMBOL|FULLY-ESCAPED-KEYWORD|ESCAPED-KEYWORD-ESCAPE|KEYWORD|ESCAPED-KEYWORD|FULLY-ESCAPED-KEYWORD-ESCAPE|FULLY-ESCAPED-SURROGATE|ESCAPED-SURROGATE-ESCAPE|SURROGATE|ESCAPED-SURROGATE|FULLY-ESCAPED-SURROGATE-ESCAPE|QUALIFIED-SURROGATE|QUALIFIED-ESCAPED-SYMBOL-ESCAPE|QUALIFIED-FULLY-ESCAPED-SYMBOL|QUALIFIED-SYMBOL|QUALIFIED-ESC" "APED-SURROGATE-ESCAPE|QUALIFIED-FULLY-ESCAPED-SURROGATE|QUALIFIED-ESCAPED-SYMBOL|QUALIFIED-ESCAPED-SURROGATE|QUALIFIED-FULLY-ESCAPED-SYMBOL-ESCAPE|QUALIFIED-FULLY-ESCAPED-SURROGATE-ESCAPE|64|TTTTFTTTTFTTTTTFFTTTTTFFFTTFFFFTFTTTTTTTTTFFFFTTFFFTTFTFFTFFTTFF|");
    { PropertyList* self065 = newPropertyList();

      self065->thePlist = listO(63, KWD_READ_SYMBOL, KWD_READ_SYMBOL, KWD_READ_ESCAPED_SYMBOL, KWD_READ_SYMBOL, KWD_READ_FULLY_ESCAPED_SYMBOL, KWD_READ_SYMBOL, KWD_READ_QUALIFIED_SYMBOL, KWD_READ_SYMBOL, KWD_READ_QUALIFIED_ESCAPED_SYMBOL, KWD_READ_SYMBOL, KWD_READ_QUALIFIED_FULLY_ESCAPED_SYMBOL, KWD_READ_SYMBOL, KWD_READ_CL_SYMBOL, KWD_READ_SYMBOL, KWD_READ_SURROGATE, KWD_READ_SURROGATE, KWD_READ_ESCAPED_SURROGATE, KWD_READ_SURROGATE, KWD_READ_QUALIFIED_SURROGATE, KWD_READ_SURROGATE, KWD_READ_QUALIFIED_ESCAPED_SURROGATE, KWD_READ_SURROGATE, KWD_READ_FULLY_ESCAPED_SURROGATE, KWD_READ_SURROGATE, KWD_READ_QUALIFIED_FULLY_ESCAPED_SURROGATE, KWD_READ_SURROGATE, KWD_READ_KEYWORD, KWD_READ_KEYWORD, KWD_READ_ESCAPED_KEYWORD, KWD_READ_KEYWORD, KWD_READ_FULLY_ESCAPED_KEYWORD, KWD_READ_KEYWORD, KWD_READ_QUALIFIED_NAME, KWD_READ_QUALIFIED_NAME, KWD_READ_STRING, KWD_READ_STRING, KWD_READ_ESCAPED_STRING, KWD_READ_STRING, KWD_READ_INTEGER, KWD_READ_INTEGER, KWD_READ_FLOAT, KWD_READ_FLOAT, KWD_READ_CHARACTER, KWD_READ_CHARACTER, KWD_READ_OPEN_PAREN, KWD_READ_OPEN_PAREN, KWD_READ_CLOSE_PAREN, KWD_READ_CLOSE_PAREN, KWD_READ_SINGLE_QUOTE, KWD_READ_SINGLE_QUOTE, KWD_READ_BACK_QUOTE, KWD_READ_BACK_QUOTE, KWD_READ_COMMA, KWD_READ_COMMA, KWD_READ_COMMA_SPLICE, KWD_READ_COMMA_SPLICE, KWD_READ_CLOSE_STRING, KWD_READ_CLOSE_BALANCED_QUOTE, KWD_READ_CLOSE_FULLY_ESCAPED_NAME, KWD_READ_CLOSE_BALANCED_QUOTE, KWD_READ_ERROR, KWD_READ_ERROR, NIL);
      oSTELLA_LOGICAL_STATE_NAMES_TABLEo = self065;
    }
    oSTELLA_LOGICAL_STATE_NAMESo = stella::newVector(oSTELLA_TOKENIZER_TABLEo->stateNames->length());
    { int i = NULL_INTEGER;
      int iter067 = 0;
      int upperBound068 = oSTELLA_LOGICAL_STATE_NAMESo->length() - 1;

      for  (; iter067 <= upperBound068; 
            iter067 = iter067 + 1) {
        i = iter067;
        (oSTELLA_LOGICAL_STATE_NAMESo->theArray)[i] = (((Keyword*)(oSTELLA_LOGICAL_STATE_NAMES_TABLEo->lookup(((Keyword*)(((GeneralizedSymbol*)((oSTELLA_TOKENIZER_TABLEo->stateNames->theArray)[i]))))))));
        if (!((boolean)(((Keyword*)((oSTELLA_LOGICAL_STATE_NAMESo->theArray)[i]))))) {
          (oSTELLA_LOGICAL_STATE_NAMESo->theArray)[i] = KWD_READ_ERROR;
        }
      }
    }
    oGET_TOKEN_INTEGER_CHECKPOINTo = ((MOST_POSITIVE_INTEGER - 9) / 10);
    oGET_TOKEN_LONG_INTEGER_CHECKPOINTo = ((MOST_POSITIVE_LONG_INTEGER - 9) / (10l));
    oSTELLA_TOKENIZER_WHITE_SPACE_STATEo = oSTELLA_TOKENIZER_TABLEo->stateNames->position(KWD_READ_WHITE_SPACE, 0);
    oREAD_LINE_TOKENIZER_TABLE_DEFINITIONo = listO(8, listO(13, KWD_READ_START, SYM_READ_STELLA_o, cons(wrapCharacter('\n'), NIL), KWD_READ_INITIAL_LINEFEED, SYM_READ_STELLA_o, cons(wrapCharacter('\r'), NIL), KWD_READ_INITIAL_RETURN, KWD_READ_EOF, KWD_READ_EOF, SYM_READ_STELLA_o, KWD_READ_OTHERWISE, KWD_READ_LINE, NIL), listO(4, KWD_READ_INITIAL_LINEFEED, KWD_READ_INCLUDE, KWD_READ_LINEFEED, NIL), listO(4, KWD_READ_INITIAL_RETURN, KWD_READ_INCLUDE, KWD_READ_RETURN, NIL), listO(13, KWD_READ_RETURN, SYM_READ_STELLA_o, cons(wrapCharacter('\n'), NIL), KWD_READ_LINEFEED, SYM_READ_STELLA_o, cons(wrapCharacter('\r'), NIL), KWD_READ_INITIAL_RETURN, KWD_READ_EOF, KWD_READ_EOF, SYM_READ_STELLA_o, KWD_READ_OTHERWISE, KWD_READ_LINE, NIL), listO(13, KWD_READ_LINEFEED, KWD_READ_EOF, KWD_READ_EOF, SYM_READ_STELLA_o, cons(wrapCharacter('\n'), NIL), KWD_READ_INITIAL_LINEFEED, SYM_READ_STELLA_o, cons(wrapCharacter('\r'), NIL), KWD_READ_INITIAL_RETURN, SYM_READ_STELLA_o, KWD_READ_OTHERWISE, KWD_READ_LINE, NIL), listO(13, KWD_READ_LINE, SYM_READ_STELLA_o, cons(wrapCharacter('\n'), NIL), KWD_READ_LINEFEED, SYM_READ_STELLA_o, cons(wrapCharacter('\r'), NIL), KWD_READ_RETURN, SYM_READ_STELLA_o, KWD_READ_EOF, KWD_READ_EOF, KWD_READ_OTHERWISE, KWD_READ_LINE, NIL), listO(4, KWD_READ_ERROR, KWD_READ_INCLUDE, KWD_READ_START, NIL), NIL);
    oREAD_LINE2_TOKENIZER_TABLE_DEFINITIONo = listO(7, listO(13, KWD_READ_START, SYM_READ_STELLA_o, cons(wrapCharacter('\n'), NIL), KWD_READ_LINEFEED, SYM_READ_STELLA_o, cons(wrapCharacter('\r'), NIL), KWD_READ_RETURN, KWD_READ_EOF, KWD_READ_EOF, SYM_READ_STELLA_o, KWD_READ_OTHERWISE, KWD_READ_LINE, NIL), listO(13, KWD_READ_LINE, SYM_READ_STELLA_o, cons(wrapCharacter('\n'), NIL), KWD_READ_LINEFEED, SYM_READ_STELLA_o, cons(wrapCharacter('\r'), NIL), KWD_READ_RETURN, SYM_READ_STELLA_o, KWD_READ_EOF, KWD_READ_EOF, KWD_READ_OTHERWISE, KWD_READ_LINE, NIL), listO(13, KWD_READ_RETURN, SYM_READ_STELLA_o, KWD_READ_EOF, KWD_READ_EOF, cons(wrapCharacter('\n'), NIL), KWD_READ_RETURN_LINEFEED, SYM_READ_STELLA_o, cons(wrapCharacter('\r'), NIL), KWD_READ_RETURN, SYM_READ_STELLA_o, KWD_READ_OTHERWISE, KWD_READ_LINE, NIL), listO(13, KWD_READ_LINEFEED, KWD_READ_EOF, KWD_READ_EOF, SYM_READ_STELLA_o, cons(wrapCharacter('\n'), NIL), KWD_READ_LINEFEED, SYM_READ_STELLA_o, cons(wrapCharacter('\r'), NIL), KWD_READ_RETURN, SYM_READ_STELLA_o, KWD_READ_OTHERWISE, KWD_READ_LINE, NIL), listO(14, KWD_READ_RETURN_LINEFEED, SYM_READ_STELLA_o, KWD_READ_EOF, KWD_READ_EOF, SYM_READ_STELLA_o, cons(wrapCharacter('\n'), NIL), KWD_READ_LINEFEED, SYM_READ_STELLA_o, cons(wrapCharacter('\r'), NIL), KWD_READ_RETURN, SYM_READ_STELLA_o, KWD_READ_OTHERWISE, KWD_READ_LINE, NIL), listO(4, KWD_READ_ERROR, KWD_READ_INCLUDE, KWD_READ_START, NIL), NIL);
    oUSER_QUERY_ACTIONo = KWD_READ_ASK;
  }
}

void helpStartupRead6() {
  {
    { Class* clasS = defineClassFromStringifiedSource("TOKENIZER-TABLE", "(DEFCLASS TOKENIZER-TABLE (STANDARD-OBJECT) :SLOTS ((TRANSITIONS :TYPE STRING) (UNIQUE-STATE-NAMES :TYPE (VECTOR OF GENERALIZED-SYMBOL)) (STATE-NAMES :TYPE (VECTOR OF GENERALIZED-SYMBOL)) (LEGAL-EOF-STATES :TYPE (VECTOR OF BOOLEAN-WRAPPER))))");

      clasS->classConstructorCode = ((cpp_function_code)(&newTokenizerTable));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessTokenizerTableSlotValue));
    }
    defineStellaTypeFromStringifiedSource("(DEFTYPE CHARACTER-SET (CONS OF CHARACTER-WRAPPER))");
    defineClassFromStringifiedSource("TOKENIZER-BYTE", "(DEFCLASS TOKENIZER-BYTE () :CL-NATIVE-TYPE \"CHARACTER\" :CPP-NATIVE-TYPE \"char\" :JAVA-NATIVE-TYPE \"char\")");
    defineClassFromStringifiedSource("TOKENIZER-BYTE-ARRAY", "(DEFCLASS TOKENIZER-BYTE-ARRAY () :CL-NATIVE-TYPE \"STRING\" :CPP-NATIVE-TYPE \"char*\" :JAVA-NATIVE-TYPE \"char[]\")");
    { Class* clasS = defineClassFromStringifiedSource("TOKENIZER-TOKEN", "(DEFCLASS TOKENIZER-TOKEN (STANDARD-OBJECT) :SLOTS ((TYPE :TYPE KEYWORD) (CONTENT :TYPE STRING) (NEXT :TYPE TOKENIZER-TOKEN)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newTokenizerToken));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessTokenizerTokenSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("TOKENIZER-STREAM-STATE", "(DEFCLASS TOKENIZER-STREAM-STATE (STANDARD-OBJECT) :SLOTS ((BUFFER :TYPE TOKENIZER-BYTE-ARRAY :INITIALLY (MAKE-TOKENIZER-BYTE-ARRAY *TOKENIZER-INITIAL-BUFFER-SIZE*)) (BUFFER-SIZE :TYPE INTEGER :INITIALLY *TOKENIZER-INITIAL-BUFFER-SIZE*) (CURSOR :TYPE INTEGER :INITIALLY *TOKENIZER-INITIAL-BUFFER-SIZE*) (END :TYPE INTEGER :INITIALLY *TOKENIZER-INITIAL-BUFFER-SIZE*) (STATE :TYPE INTEGER :INITIALLY 1) (TABLE :TYPE TOKENIZER-TABLE) (STATE-DICTIONARY :TYPE (DICTIONARY OF TOKENIZER-TABLE INTEGER-WRAPPER)) (TOKEN-LIST :TYPE TOKENIZER-TOKEN)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newTokenizerStreamState));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessTokenizerStreamStateSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("STREAM-TOKENIZER", "(DEFCLASS STREAM-TOKENIZER (ITERATOR) :DOCUMENTATION \"Iterator that generates tokens by tokenizing a `stream'\naccording to a particular tokenization `table'.\" :PUBLIC? TRUE :PARAMETERS ((ANY-VALUE :TYPE TOKENIZER-TOKEN)) :SLOTS ((STREAM :TYPE INPUT-STREAM :REQUIRED? TRUE) (TABLE :TYPE TOKENIZER-TABLE :REQUIRED? TRUE) (TOKEN :RENAMES VALUE)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newStreamTokenizer));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessStreamTokenizerSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("STELLA-TOKEN", "(DEFCLASS STELLA-TOKEN (TOKENIZER-TOKEN) :SLOTS ((LOGICAL-TOKEN-TYPE :TYPE KEYWORD) (MODULE :TYPE STRING) (ESCAPE-MODE :TYPE KEYWORD) (NEXT :TYPE STELLA-TOKEN)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newStellaToken));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessStellaTokenSlotValue));
    }
  }
}

void helpStartupRead7() {
  {
    defineFunctionObject("PARSE-TOKENIZER-DEFINITION", "(DEFUN (PARSE-TOKENIZER-DEFINITION TOKENIZER-TABLE) ((DEFINITION (CONS OF CONS))))", ((cpp_function_code)(&parseTokenizerDefinition)), NULL);
    defineFunctionObject("LEGAL-TOKENIZER-STATE?", "(DEFUN (LEGAL-TOKENIZER-STATE? BOOLEAN) ((X OBJECT)))", ((cpp_function_code)(&legalTokenizerStateP)), NULL);
    defineFunctionObject("LEGAL-TOKENIZER-FROM-STATE?", "(DEFUN (LEGAL-TOKENIZER-FROM-STATE? BOOLEAN) ((X OBJECT)))", ((cpp_function_code)(&legalTokenizerFromStateP)), NULL);
    defineFunctionObject("LEGAL-TOKENIZER-TO-STATE?", "(DEFUN (LEGAL-TOKENIZER-TO-STATE? BOOLEAN) ((X OBJECT)))", ((cpp_function_code)(&legalTokenizerToStateP)), NULL);
    defineFunctionObject("TOKENIZER-TO-STATE-NAME", "(DEFUN (TOKENIZER-TO-STATE-NAME GENERALIZED-SYMBOL) ((STATE OBJECT)))", ((cpp_function_code)(&tokenizerToStateName)), NULL);
    defineFunctionObject("TOKENIZER-TO-STATE-ALIAS", "(DEFUN (TOKENIZER-TO-STATE-ALIAS GENERALIZED-SYMBOL) ((STATE OBJECT)))", ((cpp_function_code)(&tokenizerToStateAlias)), NULL);
    defineFunctionObject("PARSE-TOKENIZER-STATE-MODIFIERS", "(DEFUN (PARSE-TOKENIZER-STATE-MODIFIERS INTEGER) ((MODIFIER OBJECT)))", ((cpp_function_code)(&parseTokenizerStateModifiers)), NULL);
    defineFunctionObject("TOKENIZER-INCLUDE-SPEC?", "(DEFUN (TOKENIZER-INCLUDE-SPEC? BOOLEAN) ((X OBJECT)))", ((cpp_function_code)(&tokenizerIncludeSpecP)), NULL);
    defineFunctionObject("PARSE-TOKENIZER-CHARACTER-SPEC", "(DEFUN (PARSE-TOKENIZER-CHARACTER-SPEC CHARACTER-SET) ((CHARACTERSPEC OBJECT) (ALLCHARACTERSETS (LIST OF CHARACTER-SET))))", ((cpp_function_code)(&parseTokenizerCharacterSpec)), NULL);
    defineFunctionObject("STRINGIFY-TOKENIZER-TABLE", "(DEFUN (STRINGIFY-TOKENIZER-TABLE STRING) ((TABLE TOKENIZER-TABLE)))", ((cpp_function_code)(&stringifyTokenizerTable)), NULL);
    defineFunctionObject("UNSTRINGIFY-TOKENIZER-TABLE", "(DEFUN (UNSTRINGIFY-TOKENIZER-TABLE TOKENIZER-TABLE) ((TABLE STRING)))", ((cpp_function_code)(&unstringifyTokenizerTable)), NULL);
    defineFunctionObject("MAKE-TOKENIZER-BYTE-ARRAY", "(DEFUN (MAKE-TOKENIZER-BYTE-ARRAY TOKENIZER-BYTE-ARRAY) ((SIZE INTEGER)) :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:MAKE-STRING SIZE) :CPP \"new (PointerFreeGC) char[size]\" :JAVA \"new char[size]\")))", ((cpp_function_code)(&makeTokenizerByteArray)), NULL);
    defineFunctionObject("STRING-TO-TOKENIZER-BYTE-ARRAY", "(DEFUN (STRING-TO-TOKENIZER-BYTE-ARRAY TOKENIZER-BYTE-ARRAY) ((STRING STRING)) :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (VERBATIM :COMMON-LISP STRING :CPP \"mutableStringCopy(string)\" :JAVA \"string.toCharArray()\")))", ((cpp_function_code)(((char*  (*) (const char*))(&stringToTokenizerByteArray)))), NULL);
    defineFunctionObject("TOKENIZER-BYTE-ARRAY-TO-STRING", "(DEFUN (TOKENIZER-BYTE-ARRAY-TO-STRING STRING) ((BYTES TOKENIZER-BYTE-ARRAY)) :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (VERBATIM :COMMON-LISP BYTES :CPP \"((const char*)bytes)\" :JAVA \"new String(bytes)\")))", ((cpp_function_code)(((const char*  (*) (char*))(&tokenizerByteArrayToString)))), NULL);
    defineMethodObject("(DEFMETHOD (BYTE-ARRAY-NTH CHARACTER) ((BUFFER TOKENIZER-BYTE-ARRAY) (POSITION INTEGER)) :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:SCHAR (CL:THE CL:SIMPLE-STRING BUFFER) (CL:THE CL:FIXNUM POSITION)) :CPP \"buffer[position]\" :JAVA \"buffer[position]\")))", wrapFunctionCode(((cpp_function_code)(((char  (*) (char*, int))(&tokenizerByteArrayByteArrayNth))))), NULL);
    defineMethodObject("(DEFMETHOD (BYTE-ARRAY-NTH-SETTER TOKENIZER-BYTE) ((BUFFER TOKENIZER-BYTE-ARRAY) (CH CHARACTER) (POSITION INTEGER)) :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:SETF (CL:SCHAR (CL:THE CL:SIMPLE-STRING BUFFER) (CL:THE CL:FIXNUM POSITION)) (CL:THE CL:CHARACTER CH)) :CPP \"buffer[position] = ch\" :JAVA \"buffer[position] = ch\")))", wrapFunctionCode(((cpp_function_code)(((char  (*) (char*, char, int))(&tokenizerByteArrayByteArrayNthSetter))))), NULL);
    defineFunctionObject("NATIVE-BYTE-ARRAY-READ-SEQUENCE", "(DEFUN (NATIVE-BYTE-ARRAY-READ-SEQUENCE INTEGER) ((BUFFER TOKENIZER-BYTE-ARRAY) (STREAM NATIVE-INPUT-STREAM) (START INTEGER) (END INTEGER)))", ((cpp_function_code)(&nativeByteArrayReadSequence)), NULL);
    defineFunctionObject("TOKENIZER-BYTE-ARRAY-READ-SEQUENCE", "(DEFUN (TOKENIZER-BYTE-ARRAY-READ-SEQUENCE INTEGER) ((BUFFER TOKENIZER-BYTE-ARRAY) (STREAM INPUT-STREAM) (START INTEGER) (END INTEGER)))", ((cpp_function_code)(((int  (*) (char*, InputStream*, int, int))(&tokenizerByteArrayReadSequence)))), NULL);
    defineFunctionObject("BYTE-ARRAY-READ-SEQUENCE", "(DEFUN (BYTE-ARRAY-READ-SEQUENCE INTEGER) ((BUFFER TOKENIZER-BYTE-ARRAY) (STREAM INPUT-STREAM) (START INTEGER) (END INTEGER)) :PUBLIC? TRUE :DOCUMENTATION \"Read from `stream' filling `buffer' between `start' and `end' (depending\non how many characters are available).\nReturn the actual end pointer to the input read into `buffer'.  EOF is\nindicated by the return value being equal to start.\")", ((cpp_function_code)(((int  (*) (char*, InputStream*, int, int))(&byteArrayReadSequence)))), NULL);
    defineFunctionObject("NATIVE-BYTE-ARRAY-WRITE-SEQUENCE", "(DEFUN NATIVE-BYTE-ARRAY-WRITE-SEQUENCE ((BUFFER TOKENIZER-BYTE-ARRAY) (STREAM NATIVE-OUTPUT-STREAM) (START INTEGER) (END INTEGER)))", ((cpp_function_code)(&nativeByteArrayWriteSequence)), NULL);
    defineFunctionObject("BYTE-ARRAY-WRITE-SEQUENCE", "(DEFUN BYTE-ARRAY-WRITE-SEQUENCE ((BUFFER TOKENIZER-BYTE-ARRAY) (STREAM NATIVE-OUTPUT-STREAM) (START INTEGER) (END INTEGER)) :PUBLIC? TRUE :DOCUMENTATION \"Write from `buffer' to `stream', using data in the buffer starting at position\n`start' stopping just before `end'.\")", ((cpp_function_code)(((void  (*) (char*, std::ostream*, int, int))(&byteArrayWriteSequence)))), NULL);
    defineFunctionObject("ENSURE-TOKENIZER-BUFFER-SIZE", "(DEFUN ENSURE-TOKENIZER-BUFFER-SIZE ((STATE TOKENIZER-STREAM-STATE) (CURRENTTOKENSTART INTEGER) (REQUIREDSPACE INTEGER)))", ((cpp_function_code)(&ensureTokenizerBufferSize)), NULL);
    defineFunctionObject("READ-INTO-TOKENIZER-BUFFER", "(DEFUN (READ-INTO-TOKENIZER-BUFFER BOOLEAN) ((STREAM INPUT-STREAM) (STATE TOKENIZER-STREAM-STATE) (CURRENTTOKENSTART INTEGER)))", ((cpp_function_code)(&readIntoTokenizerBuffer)), NULL);
    defineFunctionObject("READ-CHARACTER-FROM-TOKENIZER-BUFFER", "(DEFUN (READ-CHARACTER-FROM-TOKENIZER-BUFFER CHARACTER BOOLEAN) ((STREAM INPUT-STREAM)))", ((cpp_function_code)(&readCharacterFromTokenizerBuffer)), NULL);
    defineFunctionObject("UNREAD-CHARACTER-FROM-TOKENIZER-BUFFER", "(DEFUN UNREAD-CHARACTER-FROM-TOKENIZER-BUFFER ((CHAR CHARACTER) (STREAM INPUT-STREAM)))", ((cpp_function_code)(&unreadCharacterFromTokenizerBuffer)), NULL);
    defineFunctionObject("READ-LINE-FROM-TOKENIZER-BUFFER", "(DEFUN (READ-LINE-FROM-TOKENIZER-BUFFER STRING) ((STREAM INPUT-STREAM)))", ((cpp_function_code)(&readLineFromTokenizerBuffer)), NULL);
    defineMethodObject("(DEFMETHOD (BUFFERED-INPUT-LENGTH INTEGER) ((STATE TOKENIZER-STREAM-STATE)))", wrapMethodCode(((cpp_method_code)(&TokenizerStreamState::bufferedInputLength))), NULL);
    defineMethodObject("(DEFMETHOD CLEAR ((STATE TOKENIZER-STREAM-STATE)))", wrapMethodCode(((cpp_method_code)(&TokenizerStreamState::clear))), NULL);
    defineMethodObject("(DEFMETHOD RESET ((STATE TOKENIZER-STREAM-STATE)))", wrapMethodCode(((cpp_method_code)(&TokenizerStreamState::reset))), NULL);
    defineMethodObject("(DEFMETHOD (GET-SAVED-STATE INTEGER) ((STATE-OBJECT TOKENIZER-STREAM-STATE) (TABLE TOKENIZER-TABLE)))", wrapMethodCode(((cpp_method_code)(&TokenizerStreamState::getSavedState))), NULL);
    defineFunctionObject("WITH-TOKENIZER", "(DEFUN WITH-TOKENIZER ((TABLE OBJECT) (INPUT OBJECT) |&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&withTokenizer)), NULL);
    defineFunctionObject("WITH-TOKENIZER-STRING-INPUT?", "(DEFUN (WITH-TOKENIZER-STRING-INPUT? BOOLEAN) ())", ((cpp_function_code)(&withTokenizerStringInputP)), NULL);
    defineFunctionObject("INSIDE-WITH-TOKENIZER?", "(DEFUN (INSIDE-WITH-TOKENIZER? BOOLEAN) ())", ((cpp_function_code)(&insideWithTokenizerP)), NULL);
    defineFunctionObject("END-OF-TOKENS?", "(DEFUN END-OF-TOKENS? () :TYPE OBJECT :MACRO? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&endOfTokensP)), NULL);
    defineFunctionObject("GET-TOKEN-TEXT", "(DEFUN GET-TOKEN-TEXT (|&BODY| (OPTIONS CONS)) :TYPE OBJECT :MACRO? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&getTokenText)), NULL);
    defineFunctionObject("GET-TOKEN-TEXT-INTERNAL", "(DEFUN (GET-TOKEN-TEXT-INTERNAL STRING) ((BUFFER TOKENIZER-BYTE-ARRAY) (START INTEGER) (END INTEGER) (SIZE INTEGER) (UPCASE? BOOLEAN)))", ((cpp_function_code)(&getTokenTextInternal)), NULL);
    defineFunctionObject("COPY-TOKEN-TEXT", "(DEFUN COPY-TOKEN-TEXT ((BUFFER OBJECT) |&BODY| (OPTIONS CONS)) :TYPE OBJECT :MACRO? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&copyTokenText)), NULL);
    defineFunctionObject("COPY-TOKEN-TEXT-INTERNAL", "(DEFUN (COPY-TOKEN-TEXT-INTERNAL INTEGER) ((BUFFER TOKENIZER-BYTE-ARRAY) (START INTEGER) (END INTEGER) (SIZE INTEGER) (UPCASE? BOOLEAN) (RESULTBUFFER STRING-BUFFER)))", ((cpp_function_code)(&copyTokenTextInternal)), NULL);
    defineFunctionObject("GET-TOKEN-TYPE", "(DEFUN GET-TOKEN-TYPE () :TYPE OBJECT :MACRO? TRUE)", ((cpp_function_code)(&getTokenType)), NULL);
    defineFunctionObject("SAVE-TOKENIZER-STREAM-STATE", "(DEFUN SAVE-TOKENIZER-STREAM-STATE () :TYPE OBJECT :MACRO? TRUE)", ((cpp_function_code)(&saveTokenizerStreamState)), NULL);
    defineFunctionObject("RESTORE-TOKENIZER-STREAM-STATE", "(DEFUN RESTORE-TOKENIZER-STREAM-STATE () :TYPE OBJECT :MACRO? TRUE)", ((cpp_function_code)(&restoreTokenizerStreamState)), NULL);
    defineFunctionObject("GET-NEXT-TOKEN", "(DEFUN GET-NEXT-TOKEN (|&BODY| (OPTIONS CONS)) :TYPE OBJECT :MACRO? TRUE)", ((cpp_function_code)(&getNextToken)), NULL);
    defineFunctionObject("UNESCAPE-TOKEN-STRING", "(DEFUN (UNESCAPE-TOKEN-STRING STRING) ((TOKEN STRING) (ESCAPECHAR CHARACTER) (UPCASE? BOOLEAN)))", ((cpp_function_code)(&unescapeTokenString)), NULL);
    defineMethodObject("(DEFMETHOD (NEXT? BOOLEAN) ((SELF STREAM-TOKENIZER)))", wrapMethodCode(((cpp_method_code)(&StreamTokenizer::nextP))), NULL);
    defineFunctionObject("WITH-STELLA-TOKENIZER", "(DEFUN WITH-STELLA-TOKENIZER ((INPUT OBJECT) |&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE)", ((cpp_function_code)(&withStellaTokenizer)), NULL);
    defineFunctionObject("GET-NEXT-STELLA-TOKEN", "(DEFUN GET-NEXT-STELLA-TOKEN (|&BODY| (OPTIONS CONS)) :TYPE OBJECT :MACRO? TRUE)", ((cpp_function_code)(&getNextStellaToken)), NULL);
    defineFunctionObject("GET-STELLA-TOKEN-TYPE", "(DEFUN GET-STELLA-TOKEN-TYPE () :TYPE OBJECT :MACRO? TRUE)", ((cpp_function_code)(&getStellaTokenType)), NULL);
    defineFunctionObject("GET-QUALIFIED-SYMBOL-SEPARATOR-POSITION", "(DEFUN GET-QUALIFIED-SYMBOL-SEPARATOR-POSITION (|&BODY| (ESCAPEMODE CONS)) :TYPE OBJECT :MACRO? TRUE)", ((cpp_function_code)(&getQualifiedSymbolSeparatorPosition)), NULL);
    defineFunctionObject("GET-QUALIFIED-SYMBOL-SEPARATOR-POSITION-INTERNAL", "(DEFUN (GET-QUALIFIED-SYMBOL-SEPARATOR-POSITION-INTERNAL INTEGER) ((BUFFER TOKENIZER-BYTE-ARRAY) (TOKENSTART INTEGER) (TOKENEND INTEGER) (SIZE INTEGER) (ESCAPEMODE KEYWORD)))", ((cpp_function_code)(&getQualifiedSymbolSeparatorPositionInternal)), NULL);
    defineFunctionObject("GET-TOKEN-INTEGER", "(DEFUN GET-TOKEN-INTEGER () :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"User-level macro to access the most recently parsed token as an integer.\nThis assumes correct signed integer syntax and only checks for overflows.\" :PUBLIC? TRUE)", ((cpp_function_code)(&getTokenInteger)), NULL);
    defineFunctionObject("GET-TOKEN-INTEGER-INTERNAL", "(DEFUN (GET-TOKEN-INTEGER-INTERNAL INTEGER) ((BUFFER TOKENIZER-BYTE-ARRAY) (START INTEGER) (END INTEGER) (SIZE INTEGER)))", ((cpp_function_code)(&getTokenIntegerInternal)), NULL);
    defineFunctionObject("GET-TOKEN-LONG-INTEGER", "(DEFUN GET-TOKEN-LONG-INTEGER () :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"User-level macro to access the most recently parsed token as a long integer.\nThis assumes correct signed long-integer syntax and only checks for overflows.\" :PUBLIC? TRUE)", ((cpp_function_code)(&getTokenLongInteger)), NULL);
    defineFunctionObject("GET-TOKEN-LONG-INTEGER-INTERNAL", "(DEFUN (GET-TOKEN-LONG-INTEGER-INTERNAL LONG-INTEGER) ((BUFFER TOKENIZER-BYTE-ARRAY) (START INTEGER) (END INTEGER) (SIZE INTEGER)))", ((cpp_function_code)(&getTokenLongIntegerInternal)), NULL);
    defineFunctionObject("GET-TOKEN-FLOAT", "(DEFUN GET-TOKEN-FLOAT () :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"User-level macro to access the most recently parsed token as a float.\nThis assumes correct signed float syntax and only checks for overflows.\nThe main benefit for this is that it doesn't generate strings and wrappers.\nFloat parsing and conversion is generally hairy and we are probably not\ncovering all special cases here; but we are fast :-)\" :PUBLIC? TRUE)", ((cpp_function_code)(&getTokenFloat)), NULL);
    defineFunctionObject("GET-TOKEN-FLOAT-INTERNAL", "(DEFUN (GET-TOKEN-FLOAT-INTERNAL FLOAT) ((BUFFER TOKENIZER-BYTE-ARRAY) (START INTEGER) (END INTEGER) (SIZE INTEGER)))", ((cpp_function_code)(&getTokenFloatInternal)), NULL);
    defineFunctionObject("TOKENIZE-S-EXPRESSION", "(DEFUN (TOKENIZE-S-EXPRESSION STELLA-TOKEN) ((STREAM INPUT-STREAM) (TOKENLIST STELLA-TOKEN)))", ((cpp_function_code)(&tokenizeSExpression)), NULL);
    defineFunctionObject("PARSE-STELLA-NAME", "(DEFUN (PARSE-STELLA-NAME STRING STRING KEYWORD) ((NAME STRING) (ENABLECASECONVERSION? BOOLEAN)) :DOCUMENTATION \"Parse the printed representation `name' of a STELLA symbol, surrogate or\nkeyword and return its symbol name, module name and type (which is either\n:SYMBOL, :SURROGATE or :KEYWORD).  `name' can be qualified and must use the\nexact same syntax and escape characters that would be used if it were to be\nread by `read-s-expression-from-string' (or `unstringify').  If\n`enableCaseConversion?' is TRUE, the returned symbol name will be upcased if\nthe current module is case-insensitive; otherwise, it will be returned as is.\nRaises a read exception if `name' does not represent a symbol.\nThis function is available primarily for efficiency, since it is about\n10-15 times faster than `unstringify'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&parseStellaName)), NULL);
    defineFunctionObject("QUALIFIED-STELLA-NAME?", "(DEFUN (QUALIFIED-STELLA-NAME? BOOLEAN) ((NAME STRING)) :DOCUMENTATION \"Return TRUE if `name' is a symbol or surrogate qualified with a module\npathname or a module pathname ending with a `/'.  Assumes that `name'\nis the printed representation of a STELLA symbol (potentially containing\nescape characters).\" :PUBLIC? TRUE)", ((cpp_function_code)(&qualifiedStellaNameP)), NULL);
    defineFunctionObject("PARSE-INTEGER", "(DEFUN (PARSE-INTEGER INTEGER) ((VALUE STRING)) :DOCUMENTATION \"Convert an integer `value' string into an integer.  Leading and trailing\nwhitespace is allowed.  Raise an error if we have illegal number syntax which makes it\npreferable over the naive C++ stringToInteger conversion function which just returns 0.\" :PUBLIC? TRUE)", ((cpp_function_code)(&parseInteger)), NULL);
    defineFunctionObject("PARSE-LONG-INTEGER", "(DEFUN (PARSE-LONG-INTEGER LONG-INTEGER) ((VALUE STRING)) :DOCUMENTATION \"Convert a long integer `value' string into a long integer.  Leading and\ntrailing whitespace is allowed.  Raise an error if we have illegal number syntax which makes it\npreferable over the naive C++ stringToInteger conversion function which just returns 0.\" :PUBLIC? TRUE)", ((cpp_function_code)(&parseLongInteger)), NULL);
  }
}

void startupRead() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupRead1();
      helpStartupRead2();
      helpStartupRead3();
      helpStartupRead4();
    }
    if (currentStartupTimePhaseP(4)) {
      helpStartupRead5();
    }
    if (currentStartupTimePhaseP(5)) {
      helpStartupRead6();
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupRead7();
      defineFunctionObject("PARSE-FLOAT", "(DEFUN (PARSE-FLOAT FLOAT) ((VALUE STRING)) :DOCUMENTATION \"Convert a float `value' string into a float.  Leading and trailing\nwhitespace is allowed.  Raise an error if we have illegal number syntax which makes it\npreferable over the naive C++ stringToFloat conversion function which just returns 0.\" :PUBLIC? TRUE)", ((cpp_function_code)(&parseFloat)), NULL);
      defineFunctionObject("STELLA-TOKEN-LIST-TO-S-EXPRESSION", "(DEFUN (STELLA-TOKEN-LIST-TO-S-EXPRESSION OBJECT) ((TOKENLIST STELLA-TOKEN)))", ((cpp_function_code)(&stellaTokenListToSExpression)), NULL);
      defineFunctionObject("EXPAND-QUOTE-MACRO-TOKEN", "(DEFUN EXPAND-QUOTE-MACRO-TOKEN ((QUOTEDLIST STELLA-TOKEN)))", ((cpp_function_code)(&expandQuoteMacroToken)), NULL);
      defineFunctionObject("STRING-TO-CHARACTER", "(DEFUN (STRING-TO-CHARACTER CHARACTER) ((NAME STRING)))", ((cpp_function_code)(((char  (*) (const char*))(&stringToCharacter)))), NULL);
      defineFunctionObject("CREATE-TOKENIZE-STRING-TABLE", "(DEFUN (CREATE-TOKENIZE-STRING-TABLE (VECTOR OF KEYWORD)) ((PUNCTUATIONCHARS STRING) (QUOTECHARS STRING) (ESCAPECHARS STRING)))", ((cpp_function_code)(&createTokenizeStringTable)), NULL);
      defineFunctionObject("TOKENIZE-STRING", "(DEFUN (TOKENIZE-STRING (CONS OF CONS)) ((STRING STRING) (PUNCTUATIONCHARS STRING) (QUOTECHARS STRING) (ESCAPECHARS STRING)) :DOCUMENTATION \"Simple tokenizer that is somewhere between Java's StringTokenizer\nand StreamTokenizer in functionality.  It doens't specially support number\ntokens nor comment strings/sequences even though this could be added at\nthe expense of some extra complexity.\nReturns a list of (<token-string> <token-type>) pairs, where the token\ntype is one of :TEXT, :PUNCTUATION or :QUOTE, i.e., all white space\nis ignored and escape characters are handled and removed.  For example:\n	 \n  (tokenize-string \\\"for(i='fo^'o'; i>0; i++)\\\" \\\"()=<>+-;\\\" \\\"'\\\" \\\"^\\\")\n  =>\n  ((\\\"for\\\" :TEXT) (\\\"(\\\" :PUNCTUATION) (\\\"i\\\" :TEXT)\n   (\\\"=\\\" :PUNCTUATION) (\\\"'\\\" :QUOTE) (\\\"fo'o\\\" :TEXT)\n   (\\\"'\\\" :QUOTE) (\\\";\\\" :PUNCTUATION) (\\\"i\\\" :TEXT)\n   (\\\">\\\" :PUNCTUATION) (\\\"0\\\" :TEXT) (\\\";\\\" :PUNCTUATION)\n   (\\\"i\\\" :TEXT) (\\\"++)\\\" :PU" "NCTUATION))\n	\nNOTE: this aggregates multiple punctuation characters that immediately\nfollow each other into a single token which is (generally) useful to pickup\nmulti-character operators such as ++, >=, etc.  It's still easy to pick them\napart in a post-processing step if necessary (e.g., for the `++)' case above),\nso we leave this for now as a feature.\" :PUBLIC? TRUE)", ((cpp_function_code)(&tokenizeString)), NULL);
      defineFunctionObject("READ-S-EXPRESSION", "(DEFUN (READ-S-EXPRESSION OBJECT BOOLEAN) ((STREAM INPUT-STREAM)) :DOCUMENTATION \"Read one STELLA s-expression from `stream' and return\nthe result.  Return `true' as the second value on EOF.\" :PUBLIC? TRUE)", ((cpp_function_code)(&readSExpression)), NULL);
      defineFunctionObject("EAT-NEXT-CHARACTER-IF-WHITESPACE", "(DEFUN (EAT-NEXT-CHARACTER-IF-WHITESPACE BOOLEAN) ((STREAM INPUT-STREAM)))", ((cpp_function_code)(&eatNextCharacterIfWhitespace)), NULL);
      defineFunctionObject("CONSUME-WHITESPACE", "(DEFUN (CONSUME-WHITESPACE BOOLEAN) ((STREAM INPUT-STREAM)))", ((cpp_function_code)(&consumeWhitespace)), NULL);
      defineFunctionObject("READ-S-EXPRESSION-FROM-STRING", "(DEFUN (READ-S-EXPRESSION-FROM-STRING OBJECT) ((STRING STRING)) :DOCUMENTATION \"Read one STELLA s-expression from `string' and\nreturn the result.\" :PUBLIC? TRUE)", ((cpp_function_code)(&readSExpressionFromString)), NULL);
      defineFunctionObject("MAKE-TOKENIZER-STRING-STREAM", "(DEFUN (MAKE-TOKENIZER-STRING-STREAM STRING-INPUT-STREAM) ((STRING STRING)))", ((cpp_function_code)(&makeTokenizerStringStream)), NULL);
      defineFunctionObject("NATIVE-READ-LINE", "(DEFUN (NATIVE-READ-LINE STRING) ((INPUTSTREAM INPUT-STREAM)) :DOCUMENTATION \"Read one line from `inputStream' using the native language\nreadline algorithm and return the result.  On EOF return `null'\" :PUBLIC? TRUE)", ((cpp_function_code)(&nativeReadLine)), NULL);
      defineFunctionObject("READ-LINE", "(DEFUN (READ-LINE STRING) ((STREAM INPUT-STREAM)) :PUBLIC? TRUE :DOCUMENTATION \"Read one line from `stream' and return the result.\nThis differs from `native-read-line' in that it is not platform-dependent.\nIt recognizes any of the three common line ending formats: CR, LF, CR-LF\nin any combination.  It is not as fast as `native-read-line', however.\")", ((cpp_function_code)(&readLine)), NULL);
      defineFunctionObject("READ-LINE2", "(DEFUN (READ-LINE2 STRING KEYWORD) ((STREAM INPUT-STREAM)) :PUBLIC? TRUE :DOCUMENTATION \"Read one line from `stream' and return the result and\na keyword that indicates the terminator for that line ending:\n`:CR' `:LF' `:CRLF' or `:EOF'.   This is not platform-dependent\nand differs from `read-line' by returning a second value.  It\nmay hang when used on interactive streams such as terminal or\nnetwork streams with only CR line endings.  It should only be\nused on file or string input streams.\")", ((cpp_function_code)(&readLine2)), NULL);
      defineFunctionObject("READ-CHARACTER", "(DEFUN (READ-CHARACTER CHARACTER BOOLEAN) ((INPUTSTREAM INPUT-STREAM)) :DOCUMENTATION \"Read one character from `inputStream' and return the result.\nReturn `true' as the second value on EOF.\" :PUBLIC? TRUE)", ((cpp_function_code)(&readCharacter)), NULL);
      defineFunctionObject("UNREAD-CHARACTER", "(DEFUN UNREAD-CHARACTER ((CH CHARACTER) (INPUTSTREAM INPUT-STREAM)) :DOCUMENTATION \"Unread `ch' from `inputStream'.  Signal an error if `ch'\nwas not the last character read.\" :PUBLIC? TRUE)", ((cpp_function_code)(&unreadCharacter)), NULL);
      defineFunctionObject("YES-OR-NO?", "(DEFUN (YES-OR-NO? BOOLEAN) ((MESSAGE STRING)) :DOCUMENTATION \"Read a line of input from STANDARD-INPUT and return `true'\nif the input was `yes' or `false' if the input was `no'.  Loop until either\n`yes' or `no' was entered.  If 'message' is non-`null' prompt with it before\nthe input is read.  See also special variable `*USER-QUERY-ACTION*'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&yesOrNoP)), NULL);
      defineFunctionObject("Y-OR-N?", "(DEFUN (Y-OR-N? BOOLEAN) ((MESSAGE STRING)) :DOCUMENTATION \"Read a line of input from STANDARD-INPUT and return `true'\nif the input was `y' or `false' if the input was `n'.  Loop until either\n`y' or `n' was entered.  If 'message' is non-`null' prompt with it before\nthe input is read.  See also special variable `*USER-QUERY-ACTION*'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&yOrNP)), NULL);
      defineMethodObject("(DEFMETHOD (STREAM-TO-STRING STRING) ((FROM INPUT-STREAM)) :DOCUMENTATION \"Read all of the input from `stream' and return it as a string.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&InputStream::streamToString))), NULL);
      defineFunctionObject("FILE-TO-STRING", "(DEFUN (FILE-TO-STRING STRING) ((FILE STRING)) :DOCUMENTATION \"Read the content of `file' and return it as a string.\" :PUBLIC? TRUE)", ((cpp_function_code)(&fileToString)), NULL);
      defineFunctionObject("STARTUP-READ", "(DEFUN STARTUP-READ () :PUBLIC? TRUE)", ((cpp_function_code)(&startupRead)), NULL);
      { MethodSlot* function = lookupFunction(SYM_READ_STELLA_STARTUP_READ);

        setDynamicSlotValue(function->dynamicSlots, SYM_READ_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupRead"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("/STELLA")))));
      defineGlobalVariableObject("(DEFGLOBAL *MAX-TOKENIZER-STATES* INTEGER 64)", &oMAX_TOKENIZER_STATESo);
      defineGlobalVariableObject("(DEFGLOBAL *MAX-TOKENIZER-CHARACTERS* INTEGER 256)", &oMAX_TOKENIZER_CHARACTERSo);
      defineGlobalVariableObject("(DEFGLOBAL *TOKENIZER-INITIAL-BUFFER-SIZE* INTEGER 2048)", &oTOKENIZER_INITIAL_BUFFER_SIZEo);
      defineGlobalVariableObject("(DEFSPECIAL *WITHTOKENIZERINPUTTYPE* TYPE NULL)", &oWITHTOKENIZERINPUTTYPEo);
      defineGlobalVariableObject("(DEFGLOBAL *TRACE-GET-NEXT-TOKEN?* BOOLEAN FALSE)", &oTRACE_GET_NEXT_TOKENpo);
      defineGlobalVariableObject("(DEFGLOBAL *STELLA-TOKENIZER-TABLE-DEFINITION* CONS (BQUOTE ((:START :INCLUDE :DELIMITER :INCLUDE :ATOM) (:DELIMITER * \"(\" :OPEN-PAREN * \")\" :CLOSE-PAREN * \"\\\"\" (:OPEN-STRING :STRING) * \"'\" :SINGLE-QUOTE * \"`\" :BACK-QUOTE * \",\" :COMMA ! \";\" :COMMENT ! \"#\" :HASH ! (#\\  #\\Tab #\\Linefeed #\\Return) :WHITE-SPACE :EOF :EOF) (:WHITE-SPACE :INCLUDE :START) (:COMMENT (#\\Linefeed #\\Return) :START :EOF :EOF :OTHERWISE :COMMENT) (:PAREN-COMMENT \"\\\\\" :PAREN-COMMENT-ESCAPE \"|\" :PAREN-COMMENT-BAR :OTHERWISE :PAREN-COMMENT) (:PAREN-COMMENT-ESCAPE :ANY :PAREN-COMMENT) (:PAREN-COMMENT-BAR \"#\" :START \"\\\\\" :PAREN-COMMENT-ESCAPE \"|\" :PAREN-COMMENT-BAR :OTHERWISE :PAREN-COMMENT) (:OPEN-PAREN :INCLUDE :START) (:CLOSE-PAREN :INCLUDE :START) (:SINGLE-QUOTE :INCLUDE :START) (:BACK-QUOTE :INCLUDE :START) (:COMMA \".\" :COMMA-SPLICE :INCLUDE :DELIMITER * \"-+\" (:SYMBOL-OR-SIGNED-NUMBER :SYMBOL) * \"0123456789\" (:SYMBOL-OR-NUMBER :INTEGER) * \"cC\" (:SYMBOL-OR-CL-SYMBOL :SYMBOL) * \"|\" (:OPEN-FUL" "LY-ESCAPED-SYMBOL :FULLY-ESCAPED-SYMBOL) * \"\\\\\" :ESCAPED-SYMBOL-ESCAPE * \"/\" :QUALIFIED-NAME * \":\" (:OPEN-KEYWORD :KEYWORD) * \"@\" (:OPEN-SURROGATE :SURROGATE) * :OTHERWISE :SYMBOL) (:COMMA-SPLICE :INCLUDE :START) (:OPEN-STRING * \"\\\"\" :CLOSE-STRING \"\\\\\" :STRING-ESCAPE :OTHERWISE :STRING) (:STRING * \"\\\"\" :CLOSE-STRING \"\\\\\" :STRING-ESCAPE :OTHERWISE :STRING) (:CLOSE-STRING :INCLUDE :START) (:STRING-ESCAPE :ANY :ESCAPED-STRING) (:ESCAPED-STRING * \"\\\"\" :CLOSE-STRING \"\\\\\" :STRING-ESCAPE :OTHERWISE :ESCAPED-STRING) (:HASH \"\\\\\" :CHARACTER-CONSTANT \"|\" :PAREN-COMMENT) (:CHARACTER-CONSTANT * :ANY :CHARACTER) (:CHARACTER :INCLUDE :DELIMITER :OTHERWISE :CHARACTER) (:ATOM * \"-+\" (:SYMBOL-OR-SIGNED-NUMBER :SYMBOL) * \"0123456789\" (:SYMBOL-OR-NUMBER :INTEGER) * \".\" (:SYMBOL-OR-MANTISSA :SYMBOL) * \"cC\" (:SYMBOL-OR-CL-SYMBOL :SYMBOL) * \"|\" (:OPEN-FULLY-ESCAPED-SYMBOL :FULLY-ESCAPED-SYMBOL) * \"\\\\\" :ESCAPED-SYMBOL-ESCAPE * \"/\" :QUALIFIED-NAME * \":\" (:OPEN-KEYWORD :KEYWOR" "D) * \"@\" (:OPEN-SURROGATE :SURROGATE) * :OTHERWISE :SYMBOL) (:SYMBOL-OR-SIGNED-NUMBER :INCLUDE :DELIMITER \"/\" :QUALIFIED-NAME \"\\\\\" :ESCAPED-SYMBOL-ESCAPE \"0123456789\" (:SYMBOL-OR-NUMBER :INTEGER) \".\" (:SYMBOL-OR-MANTISSA :SYMBOL) \"|\" :ERROR :OTHERWISE :SYMBOL) (:SYMBOL-OR-NUMBER :INCLUDE :DELIMITER \"/\" :QUALIFIED-NAME \"\\\\\" :ESCAPED-SYMBOL-ESCAPE \"0123456789\" (:SYMBOL-OR-NUMBER :INTEGER) \".\" (:SYMBOL-OR-MANTISSA2 :FLOAT) \"eE\" (:SYMBOL-OR-EXPONENT-DELIMITER :SYMBOL) \"|\" :ERROR :OTHERWISE :SYMBOL) (:SYMBOL-OR-MANTISSA :INCLUDE :DELIMITER \"/\" :QUALIFIED-NAME \"\\\\\" :ESCAPED-SYMBOL-ESCAPE \"0123456789\" (:SYMBOL-OR-MANTISSA2 :FLOAT) \"eE\" (:SYMBOL-OR-EXPONENT-DELIMITER :SYMBOL) \"|\" :ERROR :OTHERWISE :SYMBOL) (:SYMBOL-OR-MANTISSA2 :INCLUDE :SYMBOL-OR-MANTISSA) (:SYMBOL-OR-EXPONENT-DELIMITER :INCLUDE :DELIMITER \"/\" :QUALIFIED-NAME \"\\\\\" :ESCAPED-SYMBOL-ESCAPE \"+-\" (:SYMBOL-OR-EXPONENT :SYMBOL) \"0123456789\" (:SYMBOL-OR-EXPONENT2 :FLOAT) \"|\" :ERROR :OTHERWISE :SYMBOL) (:S" "YMBOL-OR-EXPONENT :INCLUDE :DELIMITER \"/\" :QUALIFIED-NAME \"\\\\\" :ESCAPED-SYMBOL-ESCAPE \"0123456789\" (:SYMBOL-OR-EXPONENT2 :FLOAT) \"|\" :ERROR :OTHERWISE :SYMBOL) (:SYMBOL-OR-EXPONENT2 :INCLUDE :SYMBOL-OR-EXPONENT) (:SYMBOL-OR-CL-SYMBOL :INCLUDE :DELIMITER \"/\" :QUALIFIED-NAME \"\\\\\" :ESCAPED-SYMBOL-ESCAPE \"lL\" (:SYMBOL-OR-CL-SYMBOL2 :SYMBOL) \"|\" :ERROR :OTHERWISE :SYMBOL) (:SYMBOL-OR-CL-SYMBOL2 :INCLUDE :DELIMITER \"/\" :QUALIFIED-NAME \"\\\\\" :ESCAPED-SYMBOL-ESCAPE \":\" (:SYMBOL-OR-CL-SYMBOL3 :SYMBOL) \"|\" :ERROR :OTHERWISE :SYMBOL) (:SYMBOL-OR-CL-SYMBOL3 :INCLUDE :DELIMITER \"|\" :ERROR :OTHERWISE :CL-SYMBOL) (:CL-SYMBOL :INCLUDE :DELIMITER \"|\" :ERROR :OTHERWISE :CL-SYMBOL) (:ESCAPED-SYMBOL-ESCAPE :ANY :ESCAPED-SYMBOL) (:ESCAPED-SYMBOL :INCLUDE :DELIMITER \"/|\" :ERROR \"\\\\\" :ESCAPED-SYMBOL-ESCAPE :OTHERWISE :ESCAPED-SYMBOL) (:OPEN-FULLY-ESCAPED-SYMBOL * \"|\" :CLOSE-FULLY-ESCAPED-NAME \"\\\\\" :FULLY-ESCAPED-SYMBOL-ESCAPE :OTHERWISE :FULLY-ESCAPED-SYMBOL) (:FULLY-ESCAPED-SYMBOL-ESCA" "PE :ANY :FULLY-ESCAPED-SYMBOL) (:FULLY-ESCAPED-SYMBOL * \"|\" :CLOSE-FULLY-ESCAPED-NAME \"\\\\\" :FULLY-ESCAPED-SYMBOL-ESCAPE :OTHERWISE :FULLY-ESCAPED-SYMBOL) (:CLOSE-FULLY-ESCAPED-NAME :INCLUDE :START) (:SYMBOL :INCLUDE :DELIMITER \"/\" :QUALIFIED-NAME \"\\\\\" :ESCAPED-SYMBOL-ESCAPE \"|\" :ERROR :OTHERWISE :SYMBOL) (:OPEN-KEYWORD :INCLUDE :DELIMITER \"|\" :FULLY-ESCAPED-KEYWORD \"\\\\\" :ESCAPED-KEYWORD-ESCAPE :OTHERWISE :KEYWORD) (:KEYWORD :INCLUDE :DELIMITER \"\\\\\" :ESCAPED-KEYWORD-ESCAPE \"|\" :ERROR :OTHERWISE :KEYWORD) (:ESCAPED-KEYWORD-ESCAPE :ANY :ESCAPED-KEYWORD) (:ESCAPED-KEYWORD :INCLUDE :DELIMITER \"\\\\\" :ESCAPED-KEYWORD-ESCAPE \"|\" :ERROR :OTHERWISE :ESCAPED-KEYWORD) (:FULLY-ESCAPED-KEYWORD * \"|\" :CLOSE-FULLY-ESCAPED-NAME \"\\\\\" :FULLY-ESCAPED-KEYWORD-ESCAPE :OTHERWISE :FULLY-ESCAPED-KEYWORD) (:FULLY-ESCAPED-KEYWORD-ESCAPE :ANY :FULLY-ESCAPED-KEYWORD) (:OPEN-SURROGATE :INCLUDE :DELIMITER \"|\" :FULLY-ESCAPED-SURROGATE \"\\\\\" :ESCAPED-SURROGATE-ESCAPE :OTHERWISE :SURROGATE) (:SURROGA" "TE :INCLUDE :DELIMITER \"/|\" :ERROR \"\\\\\" :ESCAPED-SURROGATE-ESCAPE :OTHERWISE :SURROGATE) (:ESCAPED-SURROGATE :INCLUDE :DELIMITER \"/|\" :ERROR \"\\\\\" :ESCAPED-SURROGATE-ESCAPE :OTHERWISE :ESCAPED-SURROGATE) (:ESCAPED-SURROGATE-ESCAPE :ANY :ESCAPED-SURROGATE) (:FULLY-ESCAPED-SURROGATE * \"|\" :CLOSE-FULLY-ESCAPED-NAME \"\\\\\" :FULLY-ESCAPED-SURROGATE-ESCAPE :OTHERWISE :FULLY-ESCAPED-SURROGATE) (:FULLY-ESCAPED-SURROGATE-ESCAPE :ANY :FULLY-ESCAPED-SURROGATE) (:QUALIFIED-NAME :INCLUDE :DELIMITER \"@\" :QUALIFIED-SURROGATE \":\" :ERROR \"\\\\\" :QUALIFIED-ESCAPED-SYMBOL-ESCAPE \"|\" :QUALIFIED-FULLY-ESCAPED-SYMBOL \"/\" :QUALIFIED-NAME :OTHERWISE :QUALIFIED-SYMBOL) (:QUALIFIED-SYMBOL :INCLUDE :DELIMITER \"/\" :QUALIFIED-NAME \"\\\\\" :QUALIFIED-ESCAPED-SYMBOL-ESCAPE \"|\" :ERROR :OTHERWISE :QUALIFIED-SYMBOL) (:QUALIFIED-SURROGATE :INCLUDE :DELIMITER \"/\" :ERROR \"\\\\\" :QUALIFIED-ESCAPED-SURROGATE-ESCAPE \"|\" :QUALIFIED-FULLY-ESCAPED-SURROGATE :OTHERWISE :QUALIFIED-SURROGATE) (:QUALIFIED-ESCAPED-SYMBO" "L :INCLUDE :DELIMITER \"/|\" :ERROR \"\\\\\" :QUALIFIED-ESCAPED-SYMBOL-ESCAPE :OTHERWISE :QUALIFIED-ESCAPED-SYMBOL) (:QUALIFIED-ESCAPED-SYMBOL-ESCAPE :ANY :QUALIFIED-ESCAPED-SYMBOL) (:QUALIFIED-ESCAPED-SURROGATE :INCLUDE :DELIMITER \"/|\" :ERROR \"\\\\\" :QUALIFIED-ESCAPED-SURROGATE-ESCAPE :OTHERWISE :QUALIFIED-ESCAPED-SURROGATE) (:QUALIFIED-ESCAPED-SURROGATE-ESCAPE :ANY :QUALIFIED-ESCAPED-SURROGATE) (:QUALIFIED-FULLY-ESCAPED-SYMBOL * \"|\" :CLOSE-FULLY-ESCAPED-NAME \"\\\\\" :QUALIFIED-FULLY-ESCAPED-SYMBOL-ESCAPE :OTHERWISE :QUALIFIED-FULLY-ESCAPED-SYMBOL) (:QUALIFIED-FULLY-ESCAPED-SYMBOL-ESCAPE :ANY :QUALIFIED-FULLY-ESCAPED-SYMBOL) (:QUALIFIED-FULLY-ESCAPED-SURROGATE * \"|\" :CLOSE-FULLY-ESCAPED-NAME \"\\\\\" :QUALIFIED-FULLY-ESCAPED-SURROGATE-ESCAPE :OTHERWISE :QUALIFIED-FULLY-ESCAPED-SURROGATE) (:QUALIFIED-FULLY-ESCAPED-SURROGATE-ESCAPE :ANY :QUALIFIED-FULLY-ESCAPED-SURROGATE) (:ERROR :INCLUDE :START))))", &oSTELLA_TOKENIZER_TABLE_DEFINITIONo);
      defineGlobalVariableObject("(DEFGLOBAL *STELLA-TOKENIZER-TABLE* TOKENIZER-TABLE NULL)", &oSTELLA_TOKENIZER_TABLEo);
      defineGlobalVariableObject("(DEFGLOBAL *STELLA-LOGICAL-STATE-NAMES* (VECTOR OF KEYWORD) NULL)", &oSTELLA_LOGICAL_STATE_NAMESo);
      defineGlobalVariableObject("(DEFGLOBAL *STELLA-LOGICAL-STATE-NAMES-TABLE* (PROPERTY-LIST OF KEYWORD KEYWORD) (NEW (PROPERTY-LIST OF KEYWORD KEYWORD) :THE-PLIST (BQUOTE (:SYMBOL :SYMBOL :ESCAPED-SYMBOL :SYMBOL :FULLY-ESCAPED-SYMBOL :SYMBOL :QUALIFIED-SYMBOL :SYMBOL :QUALIFIED-ESCAPED-SYMBOL :SYMBOL :QUALIFIED-FULLY-ESCAPED-SYMBOL :SYMBOL :CL-SYMBOL :SYMBOL :SURROGATE :SURROGATE :ESCAPED-SURROGATE :SURROGATE :QUALIFIED-SURROGATE :SURROGATE :QUALIFIED-ESCAPED-SURROGATE :SURROGATE :FULLY-ESCAPED-SURROGATE :SURROGATE :QUALIFIED-FULLY-ESCAPED-SURROGATE :SURROGATE :KEYWORD :KEYWORD :ESCAPED-KEYWORD :KEYWORD :FULLY-ESCAPED-KEYWORD :KEYWORD :QUALIFIED-NAME :QUALIFIED-NAME :STRING :STRING :ESCAPED-STRING :STRING :INTEGER :INTEGER :FLOAT :FLOAT :CHARACTER :CHARACTER :OPEN-PAREN :OPEN-PAREN :CLOSE-PAREN :CLOSE-PAREN :SINGLE-QUOTE :SINGLE-QUOTE :BACK-QUOTE :BACK-QUOTE :COMMA :COMMA :COMMA-SPLICE :COMMA-SPLICE :CLOSE-STRING :CLOSE-BALANCED-QUOTE :CLOSE-FULLY-ESCAPED-NAME :CLOSE-BALANCED-QUOTE :ERROR :ERROR))))", &oSTELLA_LOGICAL_STATE_NAMES_TABLEo);
      defineGlobalVariableObject("(DEFGLOBAL *GET-TOKEN-INTEGER-CHECKPOINT* INTEGER (DIV (- MOST-POSITIVE-INTEGER 9) 10))", &oGET_TOKEN_INTEGER_CHECKPOINTo);
      defineGlobalVariableObject("(DEFGLOBAL *GET-TOKEN-LONG-INTEGER-CHECKPOINT* LONG-INTEGER (DIV (- MOST-POSITIVE-LONG-INTEGER 9) 10))", &oGET_TOKEN_LONG_INTEGER_CHECKPOINTo);
      defineGlobalVariableObject("(DEFGLOBAL *STELLA-TOKENIZER-WHITE-SPACE-STATE* INTEGER (POSITION (STATE-NAMES *STELLA-TOKENIZER-TABLE*) :WHITE-SPACE 0))", &oSTELLA_TOKENIZER_WHITE_SPACE_STATEo);
      defineGlobalVariableObject("(DEFGLOBAL *READ-LINE-TOKENIZER-TABLE-DEFINITION* CONS (BQUOTE ((:START * (#\\Linefeed) :INITIAL-LINEFEED * (#\\Return) :INITIAL-RETURN :EOF :EOF * :OTHERWISE :LINE) (:INITIAL-LINEFEED :INCLUDE :LINEFEED) (:INITIAL-RETURN :INCLUDE :RETURN) (:RETURN * (#\\Linefeed) :LINEFEED * (#\\Return) :INITIAL-RETURN :EOF :EOF * :OTHERWISE :LINE) (:LINEFEED :EOF :EOF * (#\\Linefeed) :INITIAL-LINEFEED * (#\\Return) :INITIAL-RETURN * :OTHERWISE :LINE) (:LINE * (#\\Linefeed) :LINEFEED * (#\\Return) :RETURN * :EOF :EOF :OTHERWISE :LINE) (:ERROR :INCLUDE :START))) :PUBLIC? FALSE)", &oREAD_LINE_TOKENIZER_TABLE_DEFINITIONo);
      defineGlobalVariableObject("(DEFGLOBAL *READ-LINE2-TOKENIZER-TABLE-DEFINITION* CONS (BQUOTE ((:START * (#\\Linefeed) :LINEFEED * (#\\Return) :RETURN :EOF :EOF * :OTHERWISE :LINE) (:LINE * (#\\Linefeed) :LINEFEED * (#\\Return) :RETURN * :EOF :EOF :OTHERWISE :LINE) (:RETURN * :EOF :EOF (#\\Linefeed) :RETURN-LINEFEED * (#\\Return) :RETURN * :OTHERWISE :LINE) (:LINEFEED :EOF :EOF * (#\\Linefeed) :LINEFEED * (#\\Return) :RETURN * :OTHERWISE :LINE) (:RETURN-LINEFEED * :EOF :EOF * (#\\Linefeed) :LINEFEED * (#\\Return) :RETURN * :OTHERWISE :LINE) (:ERROR :INCLUDE :START))) :PUBLIC? FALSE)", &oREAD_LINE2_TOKENIZER_TABLE_DEFINITIONo);
      defineGlobalVariableObject("(DEFGLOBAL *READ-LINE-TOKENIZER-TABLE* TOKENIZER-TABLE NULL :PUBLIC? FALSE)", &oREAD_LINE_TOKENIZER_TABLEo);
      defineGlobalVariableObject("(DEFGLOBAL *READ-LINE2-TOKENIZER-TABLE* TOKENIZER-TABLE NULL :PUBLIC? FALSE)", &oREAD_LINE2_TOKENIZER_TABLEo);
      oREAD_LINE_TOKENIZER_TABLEo = parseTokenizerDefinition(oREAD_LINE_TOKENIZER_TABLE_DEFINITIONo);
      oREAD_LINE2_TOKENIZER_TABLEo = parseTokenizerDefinition(oREAD_LINE2_TOKENIZER_TABLE_DEFINITIONo);
      defineGlobalVariableObject("(DEFSPECIAL *USER-QUERY-ACTION* KEYWORD :ASK :PUBLIC? TRUE :DOCUMENTATION \"Controls the behavior of interactive queries.  The default is :ASK\nwhich asks the user.  Other options are :YES, :NO, :YES-VERBOSE, :NO-VERBOSE.  These\nreturn the answer indicated, with the verbose versions printing the message and answer.\")", &oUSER_QUERY_ACTIONo);
    }
  }
}

Surrogate* SGT_READ_STELLA_TOKENIZER_TABLE = NULL;

Symbol* SYM_READ_STELLA_TRANSITIONS = NULL;

Symbol* SYM_READ_STELLA_UNIQUE_STATE_NAMES = NULL;

Symbol* SYM_READ_STELLA_STATE_NAMES = NULL;

Symbol* SYM_READ_STELLA_LEGAL_EOF_STATES = NULL;

Symbol* SYM_READ_STELLA_CHARACTER_SET = NULL;

Keyword* KWD_READ_ERROR = NULL;

Keyword* KWD_READ_START = NULL;

Keyword* KWD_READ_EOF = NULL;

Surrogate* SGT_READ_STELLA_GENERALIZED_SYMBOL = NULL;

Surrogate* SGT_READ_STELLA_CONS = NULL;

Keyword* KWD_READ_BLOCK = NULL;

Keyword* KWD_READ_LINE = NULL;

Keyword* KWD_READ_CHARACTER = NULL;

Surrogate* SGT_READ_STELLA_TOKENIZER_TOKEN = NULL;

Symbol* SYM_READ_STELLA_TYPE = NULL;

Symbol* SYM_READ_STELLA_CONTENT = NULL;

Symbol* SYM_READ_STELLA_NEXT = NULL;

Surrogate* SGT_READ_STELLA_TOKENIZER_STREAM_STATE = NULL;

Symbol* SYM_READ_STELLA_BUFFER_SIZE = NULL;

Symbol* SYM_READ_STELLA_CURSOR = NULL;

Symbol* SYM_READ_STELLA_END = NULL;

Symbol* SYM_READ_STELLA_STATE = NULL;

Symbol* SYM_READ_STELLA_TABLE = NULL;

Symbol* SYM_READ_STELLA_STATE_DICTIONARY = NULL;

Symbol* SYM_READ_STELLA_TOKEN_LIST = NULL;

Surrogate* SGT_READ_STELLA_INPUT_STREAM = NULL;

Surrogate* SGT_READ_STELLA_STRING = NULL;

Surrogate* SGT_READ_STELLA_VOID = NULL;

Surrogate* SGT_READ_STELLA_MUTABLE_STRING = NULL;

Symbol* SYM_READ_STELLA_LET = NULL;

Symbol* SYM_READ_STELLA_TOK_TABLE_ = NULL;

Symbol* SYM_READ_STELLA_TOK_TRANSITIONS_ = NULL;

Symbol* SYM_READ_STELLA_TOK_STATENAMES_ = NULL;

Symbol* SYM_READ_STELLA_THE_ARRAY = NULL;

Symbol* SYM_READ_STELLA_TOK_TOKENSTART_ = NULL;

Symbol* SYM_READ_STELLA_TOK_ENDOFTOKENSp_ = NULL;

Symbol* SYM_READ_STELLA_FALSE = NULL;

Symbol* SYM_READ_STELLA_IGNORE = NULL;

Symbol* SYM_READ_STELLA_TOK_STREAMSTATE_ = NULL;

Symbol* SYM_READ_STELLA_TOKENIZER_STREAM_STATE = NULL;

Symbol* SYM_READ_STELLA_NULL = NULL;

Symbol* SYM_READ_STELLA_TOK_BUFFER_ = NULL;

Symbol* SYM_READ_STELLA_STRING_TO_TOKENIZER_BYTE_ARRAY = NULL;

Symbol* SYM_READ_STELLA_TOK_STATE_ = NULL;

Symbol* SYM_READ_STELLA_TOK_NEXTSTATE_ = NULL;

Symbol* SYM_READ_STELLA_TOK_CURSOR_ = NULL;

Symbol* SYM_READ_STELLA_TOK_SIZE_ = NULL;

Symbol* SYM_READ_STELLA_LENGTH = NULL;

Symbol* SYM_READ_STELLA_TOK_END_ = NULL;

Symbol* SYM_READ_STELLA_TOK_INPUTSTREAM_ = NULL;

Symbol* SYM_READ_STELLA_TOK_ECHOSTREAM_ = NULL;

Symbol* SYM_READ_STELLA_ECHO_STREAM = NULL;

Symbol* SYM_READ_STELLA_CHOOSE = NULL;

Symbol* SYM_READ_STELLA_NULLp = NULL;

Symbol* SYM_READ_STELLA_TOKENIZER_STATE = NULL;

Symbol* SYM_READ_STELLA_SETF = NULL;

Symbol* SYM_READ_STELLA_NEW = NULL;

Symbol* SYM_READ_STELLA_BUFFER = NULL;

Symbol* SYM_READ_STELLA_GET_SAVED_STATE = NULL;

Symbol* SYM_READ_STELLA_TOK_CHECKPOINT_ = NULL;

Symbol* SYM_READ_STELLA_le = NULL;

Symbol* SYM_READ_STELLA_END_OF_TOKENSp = NULL;

Symbol* SYM_READ_STELLA_GET_TOKEN_TEXT = NULL;

Symbol* SYM_READ_STELLA_GET_TOKEN_TEXT_INTERNAL = NULL;

Symbol* SYM_READ_STELLA_i = NULL;

Symbol* SYM_READ_STELLA_l = NULL;

Symbol* SYM_READ_STELLA_COPY_TOKEN_TEXT_INTERNAL = NULL;

Symbol* SYM_READ_STELLA_GET_TOKEN_TYPE = NULL;

Symbol* SYM_READ_STELLA_NTH = NULL;

Symbol* SYM_READ_STELLA_WHEN = NULL;

Symbol* SYM_READ_STELLA_DEFINEDp = NULL;

Symbol* SYM_READ_STELLA_SETQ = NULL;

Symbol* SYM_READ_STELLA_GET_NEXT_TOKEN = NULL;

Symbol* SYM_READ_STELLA_SAVE_TOKENIZER_STREAM_STATE = NULL;

Symbol* SYM_READ_STELLA_TRUE = NULL;

Symbol* SYM_READ_STELLA_PROGN = NULL;

Symbol* SYM_READ_STELLA_LOOP = NULL;

Symbol* SYM_READ_STELLA_CHARACTER_CODE = NULL;

Symbol* SYM_READ_STELLA_BYTE_ARRAY_NTH = NULL;

Symbol* SYM_READ_STELLA_IF_OUTPUT_LANGUAGE = NULL;

Keyword* KWD_READ_COMMON_LISP = NULL;

Symbol* SYM_READ_STELLA_g = NULL;

Symbol* SYM_READ_STELLA_LOGOR = NULL;

Symbol* SYM_READ_STELLA_SHIFT_LEFT = NULL;

Symbol* SYM_READ_STELLA_COND = NULL;

Symbol* SYM_READ_STELLA_e = NULL;

Symbol* SYM_READ_STELLA_LOGAND = NULL;

Symbol* SYM_READ_STELLA_ii = NULL;

Symbol* SYM_READ_STELLA_OTHERWISE = NULL;

Symbol* SYM_READ_STELLA_BREAK = NULL;

Symbol* SYM_READ_STELLA_READ_INTO_TOKENIZER_BUFFER = NULL;

Symbol* SYM_READ_STELLA_MOD = NULL;

Symbol* SYM_READ_STELLA_UNLESS = NULL;

Symbol* SYM_READ_STELLA_IF = NULL;

Symbol* SYM_READ_STELLA_ge = NULL;

Symbol* SYM_READ_STELLA_PRINT_STREAM = NULL;

Symbol* SYM_READ_STELLA_1_ = NULL;

Surrogate* SGT_READ_STELLA_STREAM_TOKENIZER = NULL;

Symbol* SYM_READ_STELLA_STREAM = NULL;

Keyword* KWD_READ_INCLUDE = NULL;

Keyword* KWD_READ_DELIMITER = NULL;

Keyword* KWD_READ_ATOM = NULL;

Symbol* SYM_READ_STELLA_o = NULL;

Keyword* KWD_READ_OPEN_PAREN = NULL;

Keyword* KWD_READ_CLOSE_PAREN = NULL;

Keyword* KWD_READ_OPEN_STRING = NULL;

Keyword* KWD_READ_STRING = NULL;

Keyword* KWD_READ_SINGLE_QUOTE = NULL;

Keyword* KWD_READ_BACK_QUOTE = NULL;

Keyword* KWD_READ_COMMA = NULL;

Symbol* SYM_READ_STELLA_x = NULL;

Keyword* KWD_READ_COMMENT = NULL;

Keyword* KWD_READ_HASH = NULL;

Keyword* KWD_READ_WHITE_SPACE = NULL;

Keyword* KWD_READ_OTHERWISE = NULL;

Keyword* KWD_READ_PAREN_COMMENT = NULL;

Keyword* KWD_READ_PAREN_COMMENT_ESCAPE = NULL;

Keyword* KWD_READ_PAREN_COMMENT_BAR = NULL;

Keyword* KWD_READ_ANY = NULL;

Keyword* KWD_READ_COMMA_SPLICE = NULL;

Keyword* KWD_READ_SYMBOL_OR_SIGNED_NUMBER = NULL;

Keyword* KWD_READ_SYMBOL = NULL;

Keyword* KWD_READ_SYMBOL_OR_NUMBER = NULL;

Keyword* KWD_READ_INTEGER = NULL;

Keyword* KWD_READ_SYMBOL_OR_CL_SYMBOL = NULL;

Keyword* KWD_READ_OPEN_FULLY_ESCAPED_SYMBOL = NULL;

Keyword* KWD_READ_FULLY_ESCAPED_SYMBOL = NULL;

Keyword* KWD_READ_ESCAPED_SYMBOL_ESCAPE = NULL;

Keyword* KWD_READ_QUALIFIED_NAME = NULL;

Keyword* KWD_READ_OPEN_KEYWORD = NULL;

Keyword* KWD_READ_KEYWORD = NULL;

Keyword* KWD_READ_OPEN_SURROGATE = NULL;

Keyword* KWD_READ_SURROGATE = NULL;

Keyword* KWD_READ_CLOSE_STRING = NULL;

Keyword* KWD_READ_STRING_ESCAPE = NULL;

Keyword* KWD_READ_ESCAPED_STRING = NULL;

Keyword* KWD_READ_CHARACTER_CONSTANT = NULL;

Keyword* KWD_READ_SYMBOL_OR_MANTISSA = NULL;

Keyword* KWD_READ_SYMBOL_OR_MANTISSA2 = NULL;

Keyword* KWD_READ_FLOAT = NULL;

Keyword* KWD_READ_SYMBOL_OR_EXPONENT_DELIMITER = NULL;

Keyword* KWD_READ_SYMBOL_OR_EXPONENT = NULL;

Keyword* KWD_READ_SYMBOL_OR_EXPONENT2 = NULL;

Keyword* KWD_READ_SYMBOL_OR_CL_SYMBOL2 = NULL;

Keyword* KWD_READ_SYMBOL_OR_CL_SYMBOL3 = NULL;

Keyword* KWD_READ_CL_SYMBOL = NULL;

Keyword* KWD_READ_ESCAPED_SYMBOL = NULL;

Keyword* KWD_READ_CLOSE_FULLY_ESCAPED_NAME = NULL;

Keyword* KWD_READ_FULLY_ESCAPED_SYMBOL_ESCAPE = NULL;

Keyword* KWD_READ_FULLY_ESCAPED_KEYWORD = NULL;

Keyword* KWD_READ_ESCAPED_KEYWORD_ESCAPE = NULL;

Keyword* KWD_READ_ESCAPED_KEYWORD = NULL;

Keyword* KWD_READ_FULLY_ESCAPED_KEYWORD_ESCAPE = NULL;

Keyword* KWD_READ_FULLY_ESCAPED_SURROGATE = NULL;

Keyword* KWD_READ_ESCAPED_SURROGATE_ESCAPE = NULL;

Keyword* KWD_READ_ESCAPED_SURROGATE = NULL;

Keyword* KWD_READ_FULLY_ESCAPED_SURROGATE_ESCAPE = NULL;

Keyword* KWD_READ_QUALIFIED_SURROGATE = NULL;

Keyword* KWD_READ_QUALIFIED_ESCAPED_SYMBOL_ESCAPE = NULL;

Keyword* KWD_READ_QUALIFIED_FULLY_ESCAPED_SYMBOL = NULL;

Keyword* KWD_READ_QUALIFIED_SYMBOL = NULL;

Keyword* KWD_READ_QUALIFIED_ESCAPED_SURROGATE_ESCAPE = NULL;

Keyword* KWD_READ_QUALIFIED_FULLY_ESCAPED_SURROGATE = NULL;

Keyword* KWD_READ_QUALIFIED_ESCAPED_SYMBOL = NULL;

Keyword* KWD_READ_QUALIFIED_ESCAPED_SURROGATE = NULL;

Keyword* KWD_READ_QUALIFIED_FULLY_ESCAPED_SYMBOL_ESCAPE = NULL;

Keyword* KWD_READ_QUALIFIED_FULLY_ESCAPED_SURROGATE_ESCAPE = NULL;

Keyword* KWD_READ_CLOSE_BALANCED_QUOTE = NULL;

Symbol* SYM_READ_STELLA_WITH_TOKENIZER = NULL;

Symbol* SYM_READ_STELLA_oSTELLA_TOKENIZER_TABLEo = NULL;

Symbol* SYM_READ_STELLA_TOK_STELLALOGICALSTATENAMES_ = NULL;

Symbol* SYM_READ_STELLA_oSTELLA_LOGICAL_STATE_NAMESo = NULL;

Symbol* SYM_READ_STELLA_TOK_STELLALOGICALSTATENAME_ = NULL;

Symbol* SYM_READ_STELLA_KEYWORD = NULL;

Keyword* KWD_READ_NONE = NULL;

Symbol* SYM_READ_STELLA_GET_QUALIFIED_SYMBOL_SEPARATOR_POSITION_INTERNAL = NULL;

Keyword* KWD_READ_FULLY_ESCAPED = NULL;

Symbol* SYM_READ_STELLA_GET_TOKEN_INTEGER = NULL;

Symbol* SYM_READ_STELLA_GET_TOKEN_INTEGER_INTERNAL = NULL;

Symbol* SYM_READ_STELLA_GET_TOKEN_LONG_INTEGER = NULL;

Symbol* SYM_READ_STELLA_GET_TOKEN_LONG_INTEGER_INTERNAL = NULL;

Symbol* SYM_READ_STELLA_GET_TOKEN_FLOAT = NULL;

Symbol* SYM_READ_STELLA_GET_TOKEN_FLOAT_INTERNAL = NULL;

Surrogate* SGT_READ_STELLA_STELLA_TOKEN = NULL;

Symbol* SYM_READ_STELLA_LOGICAL_TOKEN_TYPE = NULL;

Symbol* SYM_READ_STELLA_MODULE = NULL;

Symbol* SYM_READ_STELLA_ESCAPE_MODE = NULL;

Keyword* KWD_READ_FULL = NULL;

Keyword* KWD_READ_PARTIAL = NULL;

Keyword* KWD_READ_ESCAPED = NULL;

Symbol* SYM_READ_STELLA_a = NULL;

Symbol* SYM_READ_STELLA_aa = NULL;

Keyword* KWD_READ_TEXT = NULL;

Keyword* KWD_READ_PUNCTUATION = NULL;

Keyword* KWD_READ_QUOTE = NULL;

Keyword* KWD_READ_ESCAPE = NULL;

Surrogate* SGT_READ_STELLA_F_TOKENIZE_STRING_MEMO_TABLE_000 = NULL;

Keyword* KWD_READ_INITIAL_LINEFEED = NULL;

Keyword* KWD_READ_INITIAL_RETURN = NULL;

Keyword* KWD_READ_LINEFEED = NULL;

Keyword* KWD_READ_RETURN = NULL;

Keyword* KWD_READ_RETURN_LINEFEED = NULL;

Keyword* KWD_READ_LF = NULL;

Keyword* KWD_READ_CRLF = NULL;

Keyword* KWD_READ_CR = NULL;

Keyword* KWD_READ_ASK = NULL;

Keyword* KWD_READ_YES = NULL;

Keyword* KWD_READ_NO = NULL;

Keyword* KWD_READ_YES_VERBOSE = NULL;

Keyword* KWD_READ_NO_VERBOSE = NULL;

Symbol* SYM_READ_STELLA_STARTUP_READ = NULL;

Symbol* SYM_READ_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
