//  -*- Mode: C++ -*-

// name-utility.cc

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

const char* makeMatchingName(const char* original, int options, ...) {
  // Keyword options:
  //   :break-on-cap    one of  :YES :NO :CLEVER         default is :CLEVER
  //   :break-on-number one of  :YES :NO :CLEVER         default is :CLEVER
  //   :break-on-separators string                       default is "-_ "
  //   :remove-prefix   string
  //   :remove-suffix   string
  //   
  //   :case            one of  :UPCASE :TitleCase :titleCaseX :downcase :Capitalize :preserve
  //                                                      default is :TitleCase
  //   :separator       string                            default is ""
  //   :add-prefix      string
  //   :add-suffix      string
  // 
  //   MAKE-MATCHING-NAME returns a matching name (a string) for the input name (a string).
  // A matching name is constructed by breaking the input into 'words' and then applying
  // appropriate transforms.  The arguments are used as follows:
  //   `original'         is the input name.  It is a string.
  //   :break-on-cap    is a keyword controlling whether changes in capitalization is used
  //                    to indicate word boundaries.  If :YES, then all capitalization
  //                    changes delineate words.  If :CLEVER, then unbroken runs of
  //                    capitalized letters are treated as acronyms and remain grouped.
  //                    If :NO or NULL, there is no breaking of words based on capitalization.
  //   :break-on-number is a flag controlling whether encountering a number indicates
  //                    a word boundary.  If :YES, then each run of numbers is treated as
  // 		   a word separate from surrounding words.  If :CLEVER, then an 
  // 		   attempt is made to recognize ordinal numbers (ie, 101st) and
  // 		   treat them as separate words.  If :NO or NULL, there is no breaking
  //                    of words when numbers are encountered.
  //   :break-on-separators   A string of characters which constitute word delimiters in
  //                          the input word.  This is used to determine how to break
  //                    the name into individual words.  Defaults are space, '-' and '_'.
  //   :remove-prefix   Specifies a prefix or suffix that is stripped from the input
  //   :remove-suffix   name before any other processing.  This allows the removal of
  //                    any naming convention dictated prefixes or suffixes.
  //   :add-prefix      Specifies a prefix or suffix that is added to the output name
  //   :add-suffix      after all other processing.  This allows the addition of any
  //                    naming convention dictated prefixes or suffixes.
  //   :case            The case of the resulting name.  This is applied to the name 
  //                    before adding prefixes or suffixes.  The two title case options 
  //                    differ only in how the first word of the name is treated.
  //                    :TitleCase capitalizes the first letter of the first word and
  //                        also the first letter of all other words.
  //                    :TitleCaseX does not capitalizes the first letter of the first
  // 		       word but capitalizes the first letter of all subsequent words.
  // 		   :preserve results in no change in case.
  //   :separator       This is a string specifying the word separator to use in the
  //                    returned name.  An empty string (the default) means that the
  //                    resulting words are concatenated without any separation.  This
  //                    normally only makes sense when using one of the title case values
  //                    for the case keyword.
  { PropertyList* self000 = newPropertyList();

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
      self000->thePlist = arglist000;
    }
    { PropertyList* plist = self000;
      Keyword* breakoncap = KWD_NAME_UTILITY_CLEVER;
      Keyword* breakonnumber = KWD_NAME_UTILITY_CLEVER;
      const char* breakonseparators = "-_ ";
      const char* removeprefix = "";
      const char* removesuffix = "";
      const char* addprefix = "";
      const char* addsuffix = "";
      Keyword* outputcase = KWD_NAME_UTILITY_TITLECASE;
      const char* outputseparator = "";

      vetOptions(plist, getQuotedTree("((:BREAK-ON-CAP :BREAK-ON-NUMBER :BREAK-ON-SEPARATORS :REMOVE-PREFIX :REMOVE-SUFFIX :ADD-PREFIX :ADD-SUFFIX :CASE :SEPARATOR) \"/STELLA\")", "/STELLA"));
      { Object* key = NULL;
        Object* value = NULL;
        Cons* iter001 = plist->thePlist;

        for  (; !(iter001 == NIL); 
              iter001 = iter001->rest->rest) {
          key = iter001->value;
          value = iter001->rest->value;
          { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(key));

            if (testValue000 == KWD_NAME_UTILITY_BREAK_ON_CAP) {
              if (((boolean)(value))) {
                breakoncap = ((Keyword*)(value));
              }
              else {
                breakoncap = KWD_NAME_UTILITY_NO;
              }
            }
            else if (testValue000 == KWD_NAME_UTILITY_BREAK_ON_NUMBER) {
              if (((boolean)(value))) {
                breakonnumber = ((Keyword*)(value));
              }
              else {
                breakonnumber = KWD_NAME_UTILITY_NO;
              }
            }
            else if (testValue000 == KWD_NAME_UTILITY_BREAK_ON_SEPARATORS) {
              breakonseparators = ((StringWrapper*)(value))->wrapperValue;
            }
            else if (testValue000 == KWD_NAME_UTILITY_REMOVE_PREFIX) {
              removeprefix = ((StringWrapper*)(value))->wrapperValue;
            }
            else if (testValue000 == KWD_NAME_UTILITY_REMOVE_SUFFIX) {
              removesuffix = ((StringWrapper*)(value))->wrapperValue;
            }
            else if (testValue000 == KWD_NAME_UTILITY_ADD_PREFIX) {
              addprefix = ((StringWrapper*)(value))->wrapperValue;
            }
            else if (testValue000 == KWD_NAME_UTILITY_ADD_SUFFIX) {
              addsuffix = ((StringWrapper*)(value))->wrapperValue;
            }
            else if (testValue000 == KWD_NAME_UTILITY_CASE) {
              outputcase = ((Keyword*)(value));
            }
            else if (testValue000 == KWD_NAME_UTILITY_SEPARATOR) {
              outputseparator = ((StringWrapper*)(value))->wrapperValue;
            }
            else {
              { OutputStringStream* stream000 = newOutputStringStream();

                *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
                throw *newStellaException(stream000->theStringReader());
              }
            }
          }
        }
      }
      return (makeMatchingNameFull(original, breakoncap, breakonnumber, breakonseparators, removeprefix, removesuffix, addprefix, addsuffix, outputcase, outputseparator));
    }
  }
}

Cons* decomposeNamestring(const char* namestring, int options, ...) {
  // Keyword options:
  //   :break-on-cap    one of  :YES :NO :CLEVER         default is :CLEVER
  //   :break-on-number one of  :YES :NO :CLEVER         default is :CLEVER
  //   :break-on-separators string                       default is "-_ "
  // 
  //   DECOMPOSE-NAMESTRING returns a cons of STRING-WRAPPERS that are the decomposition of the
  // input STRING.  The arguments are used as follows:
  //   `namestring'       is the input string.
  //   :break-on-cap    is a keyword controlling whether changes in capitalization is used
  //                    to indicate word boundaries.  If :YES, then all capitalization
  //                    changes delineate words.  If :CLEVER, then unbroken runs of
  //                    capitalized letters are treated as acronyms and remain grouped.
  //                    If :NO or NULL, there is no breaking of words based on capitalization.
  //   :break-on-number is a flag controlling whether encountering a number indicates
  //                    a word boundary.  If :YES, then each run of numbers is treated as
  // 		   a word separate from surrounding words.  If :CLEVER, then an 
  // 		   attempt is made to recognize ordinal numbers (ie, 101st) and
  // 		   treat them as separate words.  If :NO or NULL, there is no breaking
  //                    of words when numbers are encountered.
  //   :break-on-separators   A string of characters which constitute word delimiters in
  //                          the input word.  This is used to determine how to break
  //                    the name into individual words.  Defaults are space, '-' and '_'.
  { PropertyList* self000 = newPropertyList();

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
      self000->thePlist = arglist000;
    }
    { PropertyList* plist = self000;
      Keyword* breakoncap = KWD_NAME_UTILITY_CLEVER;
      Keyword* breakonnumber = KWD_NAME_UTILITY_CLEVER;
      const char* breakonseparators = "-_ ";

      vetOptions(plist, getQuotedTree("((:BREAK-ON-CAP :BREAK-ON-NUMBER :BREAK-ON-SEPARATORS) \"/STELLA\")", "/STELLA"));
      { Object* key = NULL;
        Object* value = NULL;
        Cons* iter001 = plist->thePlist;

        for  (; !(iter001 == NIL); 
              iter001 = iter001->rest->rest) {
          key = iter001->value;
          value = iter001->rest->value;
          { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(key));

            if (testValue000 == KWD_NAME_UTILITY_BREAK_ON_CAP) {
              if (((boolean)(value))) {
                breakoncap = ((Keyword*)(value));
              }
              else {
                breakoncap = KWD_NAME_UTILITY_NO;
              }
            }
            else if (testValue000 == KWD_NAME_UTILITY_BREAK_ON_NUMBER) {
              if (((boolean)(value))) {
                breakonnumber = ((Keyword*)(value));
              }
              else {
                breakonnumber = KWD_NAME_UTILITY_NO;
              }
            }
            else if (testValue000 == KWD_NAME_UTILITY_BREAK_ON_SEPARATORS) {
              breakonseparators = ((StringWrapper*)(value))->wrapperValue;
            }
            else {
              { OutputStringStream* stream000 = newOutputStringStream();

                *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
                throw *newStellaException(stream000->theStringReader());
              }
            }
          }
        }
      }
      return (decomposeNamestringFull(namestring, breakoncap, breakonnumber, breakonseparators));
    }
  }
}

const char* composeNamestring(Cons* nameComponents, int options, ...) {
  // `name-components' is a cons to be processed into a namestring.
  // ':prefix' and ':suffix' are strings that will NOT be case-converted.
  // ':case' is one of :UPCASE :TitleCase :titleCaseX :downcase :Capitalize
  //         default is :TitleCase
  // ':separator' is a string that should separate word elements.  It does not
  //        separate the prefix or suffix.  Default is ""
  // ':translation-table' should be a STRING-HASH-TABLE hash table that strings into their
  //        desired printed representation as a string.  In general the argument
  //        will be strings, but that is not strictly necessary.
  // 
  { PropertyList* self000 = newPropertyList();

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
      self000->thePlist = arglist000;
    }
    { PropertyList* plist = self000;
      const char* prefix = "";
      const char* suffix = "";
      Keyword* outputcase = KWD_NAME_UTILITY_TITLECASE;
      const char* outputseparator = "";
      StringHashTable* translationTable = NULL;
      boolean useAcronymHeuristicsP = false;

      vetOptions(plist, getQuotedTree("((:PREFIX :SUFFIX :CASE :SEPARATOR :TRANSLATION-TABLE :USE-ACRONYM-HEURISTICS?) \"/STELLA\")", "/STELLA"));
      { Object* key = NULL;
        Object* value = NULL;
        Cons* iter001 = plist->thePlist;

        for  (; !(iter001 == NIL); 
              iter001 = iter001->rest->rest) {
          key = iter001->value;
          value = iter001->rest->value;
          { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(key));

            if (testValue000 == KWD_NAME_UTILITY_PREFIX) {
              prefix = ((StringWrapper*)(value))->wrapperValue;
            }
            else if (testValue000 == KWD_NAME_UTILITY_SUFFIX) {
              suffix = ((StringWrapper*)(value))->wrapperValue;
            }
            else if (testValue000 == KWD_NAME_UTILITY_CASE) {
              outputcase = ((Keyword*)(value));
            }
            else if (testValue000 == KWD_NAME_UTILITY_SEPARATOR) {
              outputseparator = ((StringWrapper*)(value))->wrapperValue;
            }
            else if (testValue000 == KWD_NAME_UTILITY_TRANSLATION_TABLE) {
              translationTable = ((StringHashTable*)(value));
            }
            else if (testValue000 == KWD_NAME_UTILITY_USE_ACRONYM_HEURISTICSp) {
              useAcronymHeuristicsP = value == TRUE_WRAPPER;
            }
            else {
              { OutputStringStream* stream000 = newOutputStringStream();

                *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
                throw *newStellaException(stream000->theStringReader());
              }
            }
          }
        }
      }
      return (composeNamestringFull(nameComponents, prefix, suffix, outputcase, outputseparator, translationTable, useAcronymHeuristicsP));
    }
  }
}

const char* makeMatchingNameFull(const char* originalname, Keyword* breakoncap, Keyword* breakonnumber, const char* breakonseparators, const char* removeprefix, const char* removesuffix, const char* addprefix, const char* addsuffix, Keyword* outputcase, const char* outputseparator) {
  // Non-keyword version of `make-matching-name', which will probably be
  // easier to use when called from non-Lisp languages.
  { int prefixlength = strlen(removeprefix);
    int suffixlength = strlen(removesuffix);
    const char* resultString = originalname;
    int resultLength = 0;

    if ((prefixlength > 0) &&
        ((prefixlength <= strlen(originalname)) &&
         stringEqlP(removeprefix, stringSubsequence(originalname, 0, prefixlength)))) {
      resultString = stringSubsequence(originalname, prefixlength, NULL_INTEGER);
    }
    resultLength = strlen(resultString);
    if ((suffixlength > 0) &&
        ((suffixlength <= resultLength) &&
         stringEqlP(removesuffix, stringSubsequence(resultString, resultLength - suffixlength, resultLength)))) {
      resultString = stringSubsequence(resultString, 0, resultLength - suffixlength);
    }
    if (stringEqlP(resultString, "")) {
      resultString = originalname;
    }
    resultString = composeNamestringFull(decomposeNamestringFull(resultString, breakoncap, breakonnumber, breakonseparators), addprefix, addsuffix, outputcase, outputseparator, NULL, false);
    if (stringEqlP(resultString, "")) {
      return (originalname);
    }
    else {
      return (resultString);
    }
  }
}

Cons* decomposeNamestringFull(const char* namestring, Keyword* breakOnCap, Keyword* breakOnNumber, const char* breakOnSeparators) {
  // Non-keyword version of `decompose-namestring', which will probably be
  // easier to use when called from non-Lisp languages.
  { int len = strlen(namestring);
    Cons* result = NIL;
    int lag = 0;
    int lead = 0;
    boolean incaprunP = false;
    boolean innumberP = false;

    { char c = NULL_CHARACTER;
      const char* vector000 = namestring;
      int index000 = 0;
      int length000 = strlen(vector000);

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        c = vector000[index000];
        { boolean foundP000 = false;

          { char sep = NULL_CHARACTER;
            const char* vector001 = breakOnSeparators;
            int index001 = 0;
            int length001 = strlen(vector001);

            for  (; index001 < length001; 
                  index001 = index001 + 1) {
              sep = vector001[index001];
              if (sep == c) {
                foundP000 = true;
                break;
              }
            }
          }
          if (foundP000) {
            {
              result = cons(wrapString(stringSubsequence(namestring, lag, lead)), result);
              lag = lead + 1;
              innumberP = false;
              incaprunP = false;
            }
          }
          else {
            if (lag > lead) {
              {
              }
            }
            else {
              if (oCHARACTER_TYPE_TABLEo[(int)(unsigned char) c] == KWD_NAME_UTILITY_DIGIT) {
                {
                  if ((!innumberP) &&
                      (!(breakOnNumber == KWD_NAME_UTILITY_NO))) {
                    if (!(lead == lag)) {
                      result = cons(wrapString(stringSubsequence(namestring, lag, lead)), result);
                      lag = lead;
                    }
                  }
                  else {
                  }
                  incaprunP = false;
                  innumberP = true;
                }
              }
              else {
                if (lowerCaseCharacterP(c)) {
                  {
                    if (innumberP &&
                        (!(breakOnNumber == KWD_NAME_UTILITY_NO))) {
                      if (lead == lag) {
                      }
                      else if (!(breakOnNumber == KWD_NAME_UTILITY_CLEVER)) {
                        result = cons(wrapString(stringSubsequence(namestring, lag, lead)), result);
                        lag = lead;
                      }
                      else if ((lead < (len - 1)) &&
                          ordinalNumberStringP(stringSubsequence(namestring, lag, lead + 2))) {
                        result = cons(wrapString(stringSubsequence(namestring, lag, lead + 2)), result);
                        lag = lead + 2;
                      }
                      else {
                        result = cons(wrapString(stringSubsequence(namestring, lag, lead)), result);
                        lag = lead;
                      }
                    }
                    if (lag > lead) {
                    }
                    else if (breakOnCap == KWD_NAME_UTILITY_NO) {
                    }
                    else if (!(breakOnCap == KWD_NAME_UTILITY_CLEVER)) {
                    }
                    else if (incaprunP) {
                      if (!(lead == (lag + 1))) {
                        result = cons(wrapString(stringSubsequence(namestring, lag, lead - 1)), result);
                        lag = lead - 1;
                      }
                    }
                    innumberP = false;
                    incaprunP = false;
                  }
                }
                else {
                  if (upperCaseCharacterP(c)) {
                    if (innumberP &&
                        (!(breakOnNumber == KWD_NAME_UTILITY_NO))) {
                      if (lead == lag) {
                      }
                      else if (!(breakOnNumber == KWD_NAME_UTILITY_CLEVER)) {
                        result = cons(wrapString(stringSubsequence(namestring, lag, lead)), result);
                        lag = lead;
                      }
                      else if ((lead < (len - 1)) &&
                          ordinalNumberStringP(stringSubsequence(namestring, lag, lead + 2))) {
                        result = cons(wrapString(stringSubsequence(namestring, lag, lead + 2)), result);
                        lag = lead + 2;
                      }
                      else {
                        result = cons(wrapString(stringSubsequence(namestring, lag, lead)), result);
                        lag = lead;
                      }
                    }
                    if (lag > lead) {
                    }
                    else if (breakOnCap == KWD_NAME_UTILITY_NO) {
                    }
                    else if (!(breakOnCap == KWD_NAME_UTILITY_CLEVER)) {
                      if (!(lead == lag)) {
                        result = cons(wrapString(stringSubsequence(namestring, lag, lead)), result);
                        lag = lead;
                      }
                    }
                    else if (incaprunP) {
                    }
                    else {
                      if (!(lead == lag)) {
                        result = cons(wrapString(stringSubsequence(namestring, lag, lead)), result);
                        lag = lead;
                      }
                      incaprunP = true;
                    }
                    innumberP = false;
                  }
                }
              }
            }
          }
        }
        lead = lead + 1;
      }
    }
    if (!(lead < lag)) {
      result = cons(wrapString(stringSubsequence(namestring, lag, NULL_INTEGER)), result);
    }
    return (result->reverse());
  }
}

boolean suffixMatchesP(const char* teststring, const char* suffix) {
  { int stringlength = strlen(teststring);
    int suffixlength = strlen(suffix);

    return ((suffixlength <= stringlength) &&
        stringEqlP(suffix, stringSubsequence(teststring, stringlength - suffixlength, NULL_INTEGER)));
  }
}

boolean ordinalNumberStringP(const char* teststring) {
  { int len = strlen(teststring);
    boolean teenP = (len > 3) &&
        ('1' == teststring[(len - 4)]);
    const char* suffix = "th";

    if (len < 3) {
      return (false);
    }
    { char c = NULL_CHARACTER;
      const char* vector000 = teststring;
      int index000 = 0;
      int length000 = strlen(vector000);
      int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = len - 3;

      for  (; (index000 < length000) &&
                (iter000 <= upperBound000); 
            index000 = index000 + 1,
            iter000 = iter000 + 1) {
        c = vector000[index000];
        i = iter000;
        i = i;
        if (!(oCHARACTER_TYPE_TABLEo[(int)(unsigned char) c] == KWD_NAME_UTILITY_DIGIT)) {
          return (false);
        }
      }
    }
    if (!(teenP)) {
      switch (teststring[(len - 3)]) {
        case '1': 
          suffix = "st";
          break;
        case '2': 
          suffix = "nd";
          break;
        case '3': 
          suffix = "rd";
          break;
        default:
          break;
      }
    }
    return (suffixMatchesP(teststring, suffix));
  }
}

boolean heuristicAcronymP(const char* itemstring) {
  { boolean letterfoundP = false;
    boolean numberfoundP = false;

    { char c = NULL_CHARACTER;
      const char* vector000 = itemstring;
      int index000 = 0;
      int length000 = strlen(vector000);

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        c = vector000[index000];
        if (oCHARACTER_TYPE_TABLEo[(int)(unsigned char) c] == KWD_NAME_UTILITY_DIGIT) {
          numberfoundP = true;
        }
        else if (lowerCaseCharacterP(c) ||
            upperCaseCharacterP(c)) {
          letterfoundP = true;
        }
        else if (getQuotedTree("((#\\. #\\- #\\/) \"/STELLA\")", "/STELLA")->memberP(wrapCharacter(c))) {
          numberfoundP = true;
        }
        else {
          return (false);
        }
      }
    }
    return (numberfoundP &&
        (letterfoundP &&
         (!ordinalNumberStringP(itemstring))));
  }
}

const char* composeNamestringFull(Cons* strings, const char* prefix, const char* suffix, Keyword* outputcase, const char* outputseparator, StringHashTable* translationtable, boolean useacronymheuristicsP) {
  // Non-keyword version of `compose-namestring', which will probably be
  // easier to use when called from non-Lisp languages.
  { int n = 0;
    int i = 0;
    char* out = NULL;
    int separatorLength = ((outputseparator != NULL) ? strlen(outputseparator) : 0);
    boolean firsttimeP = true;
    const char* s = NULL;
    int sLen = 0;

    if (((boolean)(translationtable))) {
      { Cons* temp = strings;

        strings = NIL;
        { StringWrapper* sw = NULL;
          Cons* iter000 = temp;
          Cons* collect000 = NULL;

          for  (; !(iter000 == NIL); 
                iter000 = iter000->rest) {
            sw = ((StringWrapper*)(iter000->value));
            if (((boolean)(translationtable->lookup(sw->wrapperValue)))) {
              if (!((boolean)(collect000))) {
                {
                  collect000 = cons(translationtable->lookup(sw->wrapperValue), NIL);
                  if (strings == NIL) {
                    strings = collect000;
                  }
                  else {
                    addConsToEndOfConsList(strings, collect000);
                  }
                }
              }
              else {
                {
                  collect000->rest = cons(translationtable->lookup(sw->wrapperValue), NIL);
                  collect000 = collect000->rest;
                }
              }
            }
          }
        }
      }
    }
    if (prefix != NULL) {
      n = n + strlen(prefix);
    }
    if (suffix != NULL) {
      n = n + strlen(suffix);
    }
    { StringWrapper* sw = NULL;
      Cons* iter001 = strings;

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        sw = ((StringWrapper*)(iter001->value));
        n = n + strlen((sw->wrapperValue));
      }
    }
    n = n + ((strings->length() - 1) * separatorLength);
    out = makeRawMutableString(n);
    if (prefix != NULL) {
      i = insertString(prefix, 0, NULL_INTEGER, out, i, KWD_NAME_UTILITY_PRESERVE);
    }
    { StringWrapper* sw = NULL;
      Cons* iter002 = strings;

      for (; !(iter002 == NIL); iter002 = iter002->rest) {
        sw = ((StringWrapper*)(iter002->value));
        s = sw->wrapperValue;
        sLen = strlen(s);
        if (!(firsttimeP)) {
          if (separatorLength > 0) {
            i = insertString(outputseparator, 0, separatorLength - 1, out, i, KWD_NAME_UTILITY_PRESERVE);
          }
        }
        if (sLen == 0) {
        }
        else if (useacronymheuristicsP &&
            heuristicAcronymP(s)) {
          i = insertString(s, 0, sLen - 1, out, i, KWD_NAME_UTILITY_PRESERVE);
        }
        else {
          if ((outputcase == KWD_NAME_UTILITY_ALLCAPS) ||
              (outputcase == KWD_NAME_UTILITY_UPCASE)) {
            i = insertString(s, 0, sLen - 1, out, i, KWD_NAME_UTILITY_UPCASE);
          }
          else if (outputcase == KWD_NAME_UTILITY_DOWNCASE) {
            i = insertString(s, 0, sLen - 1, out, i, KWD_NAME_UTILITY_DOWNCASE);
          }
          else if (outputcase == KWD_NAME_UTILITY_TITLECASE) {
            i = insertString(s, 0, sLen - 1, out, i, KWD_NAME_UTILITY_CAPITALIZE);
          }
          else if (outputcase == KWD_NAME_UTILITY_TITLECASEX) {
            if (firsttimeP) {
              i = insertString(s, 0, sLen - 1, out, i, KWD_NAME_UTILITY_DOWNCASE);
            }
            else {
              i = insertString(s, 0, sLen - 1, out, i, KWD_NAME_UTILITY_CAPITALIZE);
            }
          }
          else if (outputcase == KWD_NAME_UTILITY_CAPITALIZE) {
            if (firsttimeP) {
              i = insertString(s, 0, sLen - 1, out, i, KWD_NAME_UTILITY_CAPITALIZE);
            }
            else {
              i = insertString(s, 0, sLen - 1, out, i, KWD_NAME_UTILITY_DOWNCASE);
            }
          }
          else if (outputcase == KWD_NAME_UTILITY_PRESERVE) {
            i = insertString(s, 0, sLen - 1, out, i, KWD_NAME_UTILITY_PRESERVE);
          }
          else {
            { OutputStringStream* stream000 = newOutputStringStream();

              *(stream000->nativeStream) << "`" << outputcase << "'" << " is not a valid case option";
              throw *newStellaException(stream000->theStringReader());
            }
          }
        }
        firsttimeP = false;
      }
    }
    if (suffix != NULL) {
      i = insertString(suffix, 0, NULL_INTEGER, out, i, KWD_NAME_UTILITY_PRESERVE);
    }
    return (out);
  }
}

void startupNameUtility() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      KWD_NAME_UTILITY_CLEVER = ((Keyword*)(internRigidSymbolWrtModule("CLEVER", NULL, 2)));
      KWD_NAME_UTILITY_TITLECASE = ((Keyword*)(internRigidSymbolWrtModule("TITLECASE", NULL, 2)));
      KWD_NAME_UTILITY_BREAK_ON_CAP = ((Keyword*)(internRigidSymbolWrtModule("BREAK-ON-CAP", NULL, 2)));
      KWD_NAME_UTILITY_NO = ((Keyword*)(internRigidSymbolWrtModule("NO", NULL, 2)));
      KWD_NAME_UTILITY_BREAK_ON_NUMBER = ((Keyword*)(internRigidSymbolWrtModule("BREAK-ON-NUMBER", NULL, 2)));
      KWD_NAME_UTILITY_BREAK_ON_SEPARATORS = ((Keyword*)(internRigidSymbolWrtModule("BREAK-ON-SEPARATORS", NULL, 2)));
      KWD_NAME_UTILITY_REMOVE_PREFIX = ((Keyword*)(internRigidSymbolWrtModule("REMOVE-PREFIX", NULL, 2)));
      KWD_NAME_UTILITY_REMOVE_SUFFIX = ((Keyword*)(internRigidSymbolWrtModule("REMOVE-SUFFIX", NULL, 2)));
      KWD_NAME_UTILITY_ADD_PREFIX = ((Keyword*)(internRigidSymbolWrtModule("ADD-PREFIX", NULL, 2)));
      KWD_NAME_UTILITY_ADD_SUFFIX = ((Keyword*)(internRigidSymbolWrtModule("ADD-SUFFIX", NULL, 2)));
      KWD_NAME_UTILITY_CASE = ((Keyword*)(internRigidSymbolWrtModule("CASE", NULL, 2)));
      KWD_NAME_UTILITY_SEPARATOR = ((Keyword*)(internRigidSymbolWrtModule("SEPARATOR", NULL, 2)));
      KWD_NAME_UTILITY_PREFIX = ((Keyword*)(internRigidSymbolWrtModule("PREFIX", NULL, 2)));
      KWD_NAME_UTILITY_SUFFIX = ((Keyword*)(internRigidSymbolWrtModule("SUFFIX", NULL, 2)));
      KWD_NAME_UTILITY_TRANSLATION_TABLE = ((Keyword*)(internRigidSymbolWrtModule("TRANSLATION-TABLE", NULL, 2)));
      KWD_NAME_UTILITY_USE_ACRONYM_HEURISTICSp = ((Keyword*)(internRigidSymbolWrtModule("USE-ACRONYM-HEURISTICS?", NULL, 2)));
      KWD_NAME_UTILITY_DIGIT = ((Keyword*)(internRigidSymbolWrtModule("DIGIT", NULL, 2)));
      KWD_NAME_UTILITY_PRESERVE = ((Keyword*)(internRigidSymbolWrtModule("PRESERVE", NULL, 2)));
      KWD_NAME_UTILITY_ALLCAPS = ((Keyword*)(internRigidSymbolWrtModule("ALLCAPS", NULL, 2)));
      KWD_NAME_UTILITY_UPCASE = ((Keyword*)(internRigidSymbolWrtModule("UPCASE", NULL, 2)));
      KWD_NAME_UTILITY_DOWNCASE = ((Keyword*)(internRigidSymbolWrtModule("DOWNCASE", NULL, 2)));
      KWD_NAME_UTILITY_CAPITALIZE = ((Keyword*)(internRigidSymbolWrtModule("CAPITALIZE", NULL, 2)));
      KWD_NAME_UTILITY_TITLECASEX = ((Keyword*)(internRigidSymbolWrtModule("TITLECASEX", NULL, 2)));
      SYM_NAME_UTILITY_STELLA_STARTUP_NAME_UTILITY = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-NAME-UTILITY", NULL, 0)));
      SYM_NAME_UTILITY_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("MAKE-MATCHING-NAME", "(DEFUN (MAKE-MATCHING-NAME STRING) ((ORIGINAL STRING) |&REST| (OPTIONS OBJECT)) :PUBLIC? TRUE :DOCUMENTATION \"Keyword options:\n  :break-on-cap    one of  :YES :NO :CLEVER         default is :CLEVER\n  :break-on-number one of  :YES :NO :CLEVER         default is :CLEVER\n  :break-on-separators string                       default is \\\"-_ \\\"\n  :remove-prefix   string\n  :remove-suffix   string\n  \n  :case            one of  :UPCASE :TitleCase :titleCaseX :downcase :Capitalize :preserve\n                                                     default is :TitleCase\n  :separator       string                            default is \\\"\\\"\n  :add-prefix      string\n  :add-suffix      string\n\n  MAKE-MATCHING-NAME returns a matching name (a string) for the input name (a string).\nA matching name is constructed by breaking the input into 'words' and then applying\nappropriate transforms.  The arguments are used as follows:\n  `original'         is the input name.  It is a string.\n  :break-on-cap    is a key" "word controlling whether changes in capitalization is used\n                   to indicate word boundaries.  If :YES, then all capitalization\n                   changes delineate words.  If :CLEVER, then unbroken runs of\n                   capitalized letters are treated as acronyms and remain grouped.\n                   If :NO or NULL, there is no breaking of words based on capitalization.\n  :break-on-number is a flag controlling whether encountering a number indicates\n                   a word boundary.  If :YES, then each run of numbers is treated as\n		   a word separate from surrounding words.  If :CLEVER, then an \n		   attempt is made to recognize ordinal numbers (ie, 101st) and\n		   treat them as separate words.  If :NO or NULL, there is no breaking\n                   of words when numbers are encountered.\n  :break-on-separators   A string of characters which constitute word delimiters in\n                         the input word.  This is used to determine how to break\n                   the" " name into individual words.  Defaults are space, '-' and '_'.\n  :remove-prefix   Specifies a prefix or suffix that is stripped from the input\n  :remove-suffix   name before any other processing.  This allows the removal of\n                   any naming convention dictated prefixes or suffixes.\n  :add-prefix      Specifies a prefix or suffix that is added to the output name\n  :add-suffix      after all other processing.  This allows the addition of any\n                   naming convention dictated prefixes or suffixes.\n  :case            The case of the resulting name.  This is applied to the name \n                   before adding prefixes or suffixes.  The two title case options \n                   differ only in how the first word of the name is treated.\n                   :TitleCase capitalizes the first letter of the first word and\n                       also the first letter of all other words.\n                   :TitleCaseX does not capitalizes the first letter of the first\n		       word b" "ut capitalizes the first letter of all subsequent words.\n		   :preserve results in no change in case.\n  :separator       This is a string specifying the word separator to use in the\n                   returned name.  An empty string (the default) means that the\n                   resulting words are concatenated without any separation.  This\n                   normally only makes sense when using one of the title case values\n                   for the case keyword.\")", ((cpp_function_code)(&makeMatchingName)), NULL);
      defineFunctionObject("DECOMPOSE-NAMESTRING", "(DEFUN (DECOMPOSE-NAMESTRING (CONS OF STRING-WRAPPER)) ((NAMESTRING STRING) |&REST| (OPTIONS OBJECT)) :DOCUMENTATION \"Keyword options:\n  :break-on-cap    one of  :YES :NO :CLEVER         default is :CLEVER\n  :break-on-number one of  :YES :NO :CLEVER         default is :CLEVER\n  :break-on-separators string                       default is \\\"-_ \\\"\n\n  DECOMPOSE-NAMESTRING returns a cons of STRING-WRAPPERS that are the decomposition of the\ninput STRING.  The arguments are used as follows:\n  `namestring'       is the input string.\n  :break-on-cap    is a keyword controlling whether changes in capitalization is used\n                   to indicate word boundaries.  If :YES, then all capitalization\n                   changes delineate words.  If :CLEVER, then unbroken runs of\n                   capitalized letters are treated as acronyms and remain grouped.\n                   If :NO or NULL, there is no breaking of words based on capitalization.\n  :break-on-number is a flag controlling whether enco" "untering a number indicates\n                   a word boundary.  If :YES, then each run of numbers is treated as\n		   a word separate from surrounding words.  If :CLEVER, then an \n		   attempt is made to recognize ordinal numbers (ie, 101st) and\n		   treat them as separate words.  If :NO or NULL, there is no breaking\n                   of words when numbers are encountered.\n  :break-on-separators   A string of characters which constitute word delimiters in\n                         the input word.  This is used to determine how to break\n                   the name into individual words.  Defaults are space, '-' and '_'.\")", ((cpp_function_code)(&decomposeNamestring)), NULL);
      defineFunctionObject("COMPOSE-NAMESTRING", "(DEFUN (COMPOSE-NAMESTRING STRING) ((NAME-COMPONENTS (CONS OF STRING-WRAPPER)) |&REST| (OPTIONS OBJECT)) :PUBLIC? TRUE :DOCUMENTATION \"`name-components' is a cons to be processed into a namestring.\n':prefix' and ':suffix' are strings that will NOT be case-converted.\n':case' is one of :UPCASE :TitleCase :titleCaseX :downcase :Capitalize\n        default is :TitleCase\n':separator' is a string that should separate word elements.  It does not\n       separate the prefix or suffix.  Default is \\\"\\\"\n':translation-table' should be a STRING-HASH-TABLE hash table that strings into their\n       desired printed representation as a string.  In general the argument\n       will be strings, but that is not strictly necessary.\n\")", ((cpp_function_code)(&composeNamestring)), NULL);
      defineFunctionObject("MAKE-MATCHING-NAME-FULL", "(DEFUN (MAKE-MATCHING-NAME-FULL STRING) ((ORIGINALNAME STRING) (BREAKONCAP KEYWORD) (BREAKONNUMBER KEYWORD) (BREAKONSEPARATORS STRING) (REMOVEPREFIX STRING) (REMOVESUFFIX STRING) (ADDPREFIX STRING) (ADDSUFFIX STRING) (OUTPUTCASE KEYWORD) (OUTPUTSEPARATOR STRING)) :PUBLIC? TRUE :DOCUMENTATION \"Non-keyword version of `make-matching-name', which will probably be\neasier to use when called from non-Lisp languages.\")", ((cpp_function_code)(&makeMatchingNameFull)), NULL);
      defineFunctionObject("DECOMPOSE-NAMESTRING-FULL", "(DEFUN (DECOMPOSE-NAMESTRING-FULL (CONS OF STRING-WRAPPER)) ((NAMESTRING STRING) (BREAK-ON-CAP KEYWORD) (BREAK-ON-NUMBER KEYWORD) (BREAK-ON-SEPARATORS STRING)) :PUBLIC? TRUE :DOCUMENTATION \"Non-keyword version of `decompose-namestring', which will probably be\neasier to use when called from non-Lisp languages.\")", ((cpp_function_code)(&decomposeNamestringFull)), NULL);
      defineFunctionObject("SUFFIX-MATCHES?", "(DEFUN (SUFFIX-MATCHES? BOOLEAN) ((TESTSTRING STRING) (SUFFIX STRING)))", ((cpp_function_code)(&suffixMatchesP)), NULL);
      defineFunctionObject("ORDINAL-NUMBER-STRING?", "(DEFUN (ORDINAL-NUMBER-STRING? BOOLEAN) ((TESTSTRING STRING)))", ((cpp_function_code)(&ordinalNumberStringP)), NULL);
      defineFunctionObject("HEURISTIC-ACRONYM?", "(DEFUN (HEURISTIC-ACRONYM? BOOLEAN) ((ITEMSTRING STRING)))", ((cpp_function_code)(&heuristicAcronymP)), NULL);
      defineFunctionObject("COMPOSE-NAMESTRING-FULL", "(DEFUN (COMPOSE-NAMESTRING-FULL STRING) ((STRINGS (CONS OF STRING-WRAPPER)) (PREFIX STRING) (SUFFIX STRING) (OUTPUTCASE KEYWORD) (OUTPUTSEPARATOR STRING) (TRANSLATIONTABLE STRING-HASH-TABLE) (USEACRONYMHEURISTICS? BOOLEAN)) :PUBLIC? TRUE :DOCUMENTATION \"Non-keyword version of `compose-namestring', which will probably be\neasier to use when called from non-Lisp languages.\")", ((cpp_function_code)(&composeNamestringFull)), NULL);
      defineFunctionObject("STARTUP-NAME-UTILITY", "(DEFUN STARTUP-NAME-UTILITY () :PUBLIC? TRUE)", ((cpp_function_code)(&startupNameUtility)), NULL);
      { MethodSlot* function = lookupFunction(SYM_NAME_UTILITY_STELLA_STARTUP_NAME_UTILITY);

        setDynamicSlotValue(function->dynamicSlots, SYM_NAME_UTILITY_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupNameUtility"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("STELLA")))));
    }
  }
}

Keyword* KWD_NAME_UTILITY_CLEVER = NULL;

Keyword* KWD_NAME_UTILITY_TITLECASE = NULL;

Keyword* KWD_NAME_UTILITY_BREAK_ON_CAP = NULL;

Keyword* KWD_NAME_UTILITY_NO = NULL;

Keyword* KWD_NAME_UTILITY_BREAK_ON_NUMBER = NULL;

Keyword* KWD_NAME_UTILITY_BREAK_ON_SEPARATORS = NULL;

Keyword* KWD_NAME_UTILITY_REMOVE_PREFIX = NULL;

Keyword* KWD_NAME_UTILITY_REMOVE_SUFFIX = NULL;

Keyword* KWD_NAME_UTILITY_ADD_PREFIX = NULL;

Keyword* KWD_NAME_UTILITY_ADD_SUFFIX = NULL;

Keyword* KWD_NAME_UTILITY_CASE = NULL;

Keyword* KWD_NAME_UTILITY_SEPARATOR = NULL;

Keyword* KWD_NAME_UTILITY_PREFIX = NULL;

Keyword* KWD_NAME_UTILITY_SUFFIX = NULL;

Keyword* KWD_NAME_UTILITY_TRANSLATION_TABLE = NULL;

Keyword* KWD_NAME_UTILITY_USE_ACRONYM_HEURISTICSp = NULL;

Keyword* KWD_NAME_UTILITY_DIGIT = NULL;

Keyword* KWD_NAME_UTILITY_PRESERVE = NULL;

Keyword* KWD_NAME_UTILITY_ALLCAPS = NULL;

Keyword* KWD_NAME_UTILITY_UPCASE = NULL;

Keyword* KWD_NAME_UTILITY_DOWNCASE = NULL;

Keyword* KWD_NAME_UTILITY_CAPITALIZE = NULL;

Keyword* KWD_NAME_UTILITY_TITLECASEX = NULL;

Symbol* SYM_NAME_UTILITY_STELLA_STARTUP_NAME_UTILITY = NULL;

Symbol* SYM_NAME_UTILITY_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
