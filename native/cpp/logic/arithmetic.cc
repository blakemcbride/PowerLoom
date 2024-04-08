//  -*- Mode: C++ -*-

// arithmetic.cc

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
 | Portions created by the Initial Developer are Copyright (C) 1997-2023      |
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

#include "logic/logic-system.hh"

namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

boolean arithmeticEqualTest(NumberWrapper* x, NumberWrapper* y) {
  { Surrogate* testValue000 = safePrimaryType(x);

    if (subtypeOfIntegerP(testValue000)) {
      { NumberWrapper* x000 = x;
        IntegerWrapper* x = ((IntegerWrapper*)(x000));

        { Surrogate* testValue001 = safePrimaryType(y);

          if (subtypeOfIntegerP(testValue001)) {
            { NumberWrapper* y000 = y;
              IntegerWrapper* y = ((IntegerWrapper*)(y000));

              return (x->wrapperValue == y->wrapperValue);
            }
          }
          else if (subtypeOfFloatP(testValue001)) {
            { NumberWrapper* y001 = y;
              FloatWrapper* y = ((FloatWrapper*)(y001));

              return (((double)(x->wrapperValue)) == y->wrapperValue);
            }
          }
          else {
            { OutputStringStream* stream000 = newOutputStringStream();

              *(stream000->nativeStream) << "`" << testValue001 << "'" << " is not a valid case option";
              throw *newStellaException(stream000->theStringReader());
            }
          }
        }
      }
    }
    else if (subtypeOfFloatP(testValue000)) {
      { NumberWrapper* x001 = x;
        FloatWrapper* x = ((FloatWrapper*)(x001));

        { Surrogate* testValue002 = safePrimaryType(y);

          if (subtypeOfIntegerP(testValue002)) {
            { NumberWrapper* y002 = y;
              IntegerWrapper* y = ((IntegerWrapper*)(y002));

              return (x->wrapperValue == ((double)(y->wrapperValue)));
            }
          }
          else if (subtypeOfFloatP(testValue002)) {
            { NumberWrapper* y003 = y;
              FloatWrapper* y = ((FloatWrapper*)(y003));

              return (x->wrapperValue == y->wrapperValue);
            }
          }
          else {
            { OutputStringStream* stream001 = newOutputStringStream();

              *(stream001->nativeStream) << "`" << testValue002 << "'" << " is not a valid case option";
              throw *newStellaException(stream001->theStringReader());
            }
          }
        }
      }
    }
    else {
      { OutputStringStream* stream002 = newOutputStringStream();

        *(stream002->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
        throw *newStellaException(stream002->theStringReader());
      }
    }
  }
}

boolean arithmeticLessTest(NumberWrapper* x, NumberWrapper* y) {
  { Surrogate* testValue000 = safePrimaryType(x);

    if (subtypeOfIntegerP(testValue000)) {
      { NumberWrapper* x000 = x;
        IntegerWrapper* x = ((IntegerWrapper*)(x000));

        { Surrogate* testValue001 = safePrimaryType(y);

          if (subtypeOfIntegerP(testValue001)) {
            { NumberWrapper* y000 = y;
              IntegerWrapper* y = ((IntegerWrapper*)(y000));

              return (x->wrapperValue < y->wrapperValue);
            }
          }
          else if (subtypeOfFloatP(testValue001)) {
            { NumberWrapper* y001 = y;
              FloatWrapper* y = ((FloatWrapper*)(y001));

              return (((double)(x->wrapperValue)) < y->wrapperValue);
            }
          }
          else {
            { OutputStringStream* stream000 = newOutputStringStream();

              *(stream000->nativeStream) << "`" << testValue001 << "'" << " is not a valid case option";
              throw *newStellaException(stream000->theStringReader());
            }
          }
        }
      }
    }
    else if (subtypeOfFloatP(testValue000)) {
      { NumberWrapper* x001 = x;
        FloatWrapper* x = ((FloatWrapper*)(x001));

        { Surrogate* testValue002 = safePrimaryType(y);

          if (subtypeOfIntegerP(testValue002)) {
            { NumberWrapper* y002 = y;
              IntegerWrapper* y = ((IntegerWrapper*)(y002));

              return (x->wrapperValue < ((double)(y->wrapperValue)));
            }
          }
          else if (subtypeOfFloatP(testValue002)) {
            { NumberWrapper* y003 = y;
              FloatWrapper* y = ((FloatWrapper*)(y003));

              return (x->wrapperValue < y->wrapperValue);
            }
          }
          else {
            { OutputStringStream* stream001 = newOutputStringStream();

              *(stream001->nativeStream) << "`" << testValue002 << "'" << " is not a valid case option";
              throw *newStellaException(stream001->theStringReader());
            }
          }
        }
      }
    }
    else {
      { OutputStringStream* stream002 = newOutputStringStream();

        *(stream002->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
        throw *newStellaException(stream002->theStringReader());
      }
    }
  }
}

boolean arithmeticGreaterTest(NumberWrapper* x, NumberWrapper* y) {
  { Surrogate* testValue000 = safePrimaryType(x);

    if (subtypeOfIntegerP(testValue000)) {
      { NumberWrapper* x000 = x;
        IntegerWrapper* x = ((IntegerWrapper*)(x000));

        { Surrogate* testValue001 = safePrimaryType(y);

          if (subtypeOfIntegerP(testValue001)) {
            { NumberWrapper* y000 = y;
              IntegerWrapper* y = ((IntegerWrapper*)(y000));

              return (x->wrapperValue > y->wrapperValue);
            }
          }
          else if (subtypeOfFloatP(testValue001)) {
            { NumberWrapper* y001 = y;
              FloatWrapper* y = ((FloatWrapper*)(y001));

              return (((double)(x->wrapperValue)) > y->wrapperValue);
            }
          }
          else {
            { OutputStringStream* stream000 = newOutputStringStream();

              *(stream000->nativeStream) << "`" << testValue001 << "'" << " is not a valid case option";
              throw *newStellaException(stream000->theStringReader());
            }
          }
        }
      }
    }
    else if (subtypeOfFloatP(testValue000)) {
      { NumberWrapper* x001 = x;
        FloatWrapper* x = ((FloatWrapper*)(x001));

        { Surrogate* testValue002 = safePrimaryType(y);

          if (subtypeOfIntegerP(testValue002)) {
            { NumberWrapper* y002 = y;
              IntegerWrapper* y = ((IntegerWrapper*)(y002));

              return (x->wrapperValue > ((double)(y->wrapperValue)));
            }
          }
          else if (subtypeOfFloatP(testValue002)) {
            { NumberWrapper* y003 = y;
              FloatWrapper* y = ((FloatWrapper*)(y003));

              return (x->wrapperValue > y->wrapperValue);
            }
          }
          else {
            { OutputStringStream* stream001 = newOutputStringStream();

              *(stream001->nativeStream) << "`" << testValue002 << "'" << " is not a valid case option";
              throw *newStellaException(stream001->theStringReader());
            }
          }
        }
      }
    }
    else {
      { OutputStringStream* stream002 = newOutputStringStream();

        *(stream002->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
        throw *newStellaException(stream002->theStringReader());
      }
    }
  }
}

NumberWrapper* plusComputation(NumberWrapper* x, NumberWrapper* y) {
  { double floatresult = NULL_FLOAT;

    { Surrogate* testValue000 = safePrimaryType(x);

      if (subtypeOfIntegerP(testValue000)) {
        { NumberWrapper* x000 = x;
          IntegerWrapper* x = ((IntegerWrapper*)(x000));

          { Surrogate* testValue001 = safePrimaryType(y);

            if (subtypeOfIntegerP(testValue001)) {
              { NumberWrapper* y000 = y;
                IntegerWrapper* y = ((IntegerWrapper*)(y000));

                return (wrapInteger(((int)(x->wrapperValue + y->wrapperValue))));
              }
            }
            else if (subtypeOfFloatP(testValue001)) {
              { NumberWrapper* y001 = y;
                FloatWrapper* y = ((FloatWrapper*)(y001));

                floatresult = x->wrapperValue + y->wrapperValue;
              }
            }
            else {
              { OutputStringStream* stream000 = newOutputStringStream();

                *(stream000->nativeStream) << "`" << testValue001 << "'" << " is not a valid case option";
                throw *newStellaException(stream000->theStringReader());
              }
            }
          }
        }
      }
      else if (subtypeOfFloatP(testValue000)) {
        { NumberWrapper* x001 = x;
          FloatWrapper* x = ((FloatWrapper*)(x001));

          { Surrogate* testValue002 = safePrimaryType(y);

            if (subtypeOfIntegerP(testValue002)) {
              { NumberWrapper* y002 = y;
                IntegerWrapper* y = ((IntegerWrapper*)(y002));

                floatresult = x->wrapperValue + y->wrapperValue;
              }
            }
            else if (subtypeOfFloatP(testValue002)) {
              { NumberWrapper* y003 = y;
                FloatWrapper* y = ((FloatWrapper*)(y003));

                floatresult = x->wrapperValue + y->wrapperValue;
              }
            }
            else {
              { OutputStringStream* stream001 = newOutputStringStream();

                *(stream001->nativeStream) << "`" << testValue002 << "'" << " is not a valid case option";
                throw *newStellaException(stream001->theStringReader());
              }
            }
          }
        }
      }
      else {
        { OutputStringStream* stream002 = newOutputStringStream();

          *(stream002->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream002->theStringReader());
        }
      }
    }
    return (wrapFloat(floatresult));
  }
}

NumberWrapper* minusComputation(NumberWrapper* x, NumberWrapper* y) {
  { double floatresult = NULL_FLOAT;

    { Surrogate* testValue000 = safePrimaryType(x);

      if (subtypeOfIntegerP(testValue000)) {
        { NumberWrapper* x000 = x;
          IntegerWrapper* x = ((IntegerWrapper*)(x000));

          { Surrogate* testValue001 = safePrimaryType(y);

            if (subtypeOfIntegerP(testValue001)) {
              { NumberWrapper* y000 = y;
                IntegerWrapper* y = ((IntegerWrapper*)(y000));

                return (wrapInteger(((int)(x->wrapperValue - y->wrapperValue))));
              }
            }
            else if (subtypeOfFloatP(testValue001)) {
              { NumberWrapper* y001 = y;
                FloatWrapper* y = ((FloatWrapper*)(y001));

                floatresult = x->wrapperValue - y->wrapperValue;
              }
            }
            else {
              { OutputStringStream* stream000 = newOutputStringStream();

                *(stream000->nativeStream) << "`" << testValue001 << "'" << " is not a valid case option";
                throw *newStellaException(stream000->theStringReader());
              }
            }
          }
        }
      }
      else if (subtypeOfFloatP(testValue000)) {
        { NumberWrapper* x001 = x;
          FloatWrapper* x = ((FloatWrapper*)(x001));

          { Surrogate* testValue002 = safePrimaryType(y);

            if (subtypeOfIntegerP(testValue002)) {
              { NumberWrapper* y002 = y;
                IntegerWrapper* y = ((IntegerWrapper*)(y002));

                floatresult = x->wrapperValue - y->wrapperValue;
              }
            }
            else if (subtypeOfFloatP(testValue002)) {
              { NumberWrapper* y003 = y;
                FloatWrapper* y = ((FloatWrapper*)(y003));

                floatresult = x->wrapperValue - y->wrapperValue;
              }
            }
            else {
              { OutputStringStream* stream001 = newOutputStringStream();

                *(stream001->nativeStream) << "`" << testValue002 << "'" << " is not a valid case option";
                throw *newStellaException(stream001->theStringReader());
              }
            }
          }
        }
      }
      else {
        { OutputStringStream* stream002 = newOutputStringStream();

          *(stream002->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream002->theStringReader());
        }
      }
    }
    return (wrapFloat(floatresult));
  }
}

NumberWrapper* timesComputation(NumberWrapper* x, NumberWrapper* y) {
  { double floatresult = NULL_FLOAT;

    { Surrogate* testValue000 = safePrimaryType(x);

      if (subtypeOfIntegerP(testValue000)) {
        { NumberWrapper* x000 = x;
          IntegerWrapper* x = ((IntegerWrapper*)(x000));

          { Surrogate* testValue001 = safePrimaryType(y);

            if (subtypeOfIntegerP(testValue001)) {
              { NumberWrapper* y000 = y;
                IntegerWrapper* y = ((IntegerWrapper*)(y000));

                return (wrapInteger(((int)(x->wrapperValue * y->wrapperValue))));
              }
            }
            else if (subtypeOfFloatP(testValue001)) {
              { NumberWrapper* y001 = y;
                FloatWrapper* y = ((FloatWrapper*)(y001));

                floatresult = x->wrapperValue * y->wrapperValue;
              }
            }
            else {
              { OutputStringStream* stream000 = newOutputStringStream();

                *(stream000->nativeStream) << "`" << testValue001 << "'" << " is not a valid case option";
                throw *newStellaException(stream000->theStringReader());
              }
            }
          }
        }
      }
      else if (subtypeOfFloatP(testValue000)) {
        { NumberWrapper* x001 = x;
          FloatWrapper* x = ((FloatWrapper*)(x001));

          { Surrogate* testValue002 = safePrimaryType(y);

            if (subtypeOfIntegerP(testValue002)) {
              { NumberWrapper* y002 = y;
                IntegerWrapper* y = ((IntegerWrapper*)(y002));

                floatresult = x->wrapperValue * y->wrapperValue;
              }
            }
            else if (subtypeOfFloatP(testValue002)) {
              { NumberWrapper* y003 = y;
                FloatWrapper* y = ((FloatWrapper*)(y003));

                floatresult = x->wrapperValue * y->wrapperValue;
              }
            }
            else {
              { OutputStringStream* stream001 = newOutputStringStream();

                *(stream001->nativeStream) << "`" << testValue002 << "'" << " is not a valid case option";
                throw *newStellaException(stream001->theStringReader());
              }
            }
          }
        }
      }
      else {
        { OutputStringStream* stream002 = newOutputStringStream();

          *(stream002->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream002->theStringReader());
        }
      }
    }
    return (wrapFloat(floatresult));
  }
}

NumberWrapper* divideComputation(NumberWrapper* x, NumberWrapper* y) {
  try {
    { double floatresult = NULL_FLOAT;

      { Surrogate* testValue000 = safePrimaryType(x);

        if (subtypeOfIntegerP(testValue000)) {
          { NumberWrapper* x000 = x;
            IntegerWrapper* x = ((IntegerWrapper*)(x000));

            { Surrogate* testValue001 = safePrimaryType(y);

              if (subtypeOfIntegerP(testValue001)) {
                { NumberWrapper* y000 = y;
                  IntegerWrapper* y = ((IntegerWrapper*)(y000));

                  if (((x->wrapperValue) % (y->wrapperValue)) == 0) {
                    return (wrapInteger(((x->wrapperValue) / (y->wrapperValue))));
                  }
                  else {
                    floatresult = ((double)(x->wrapperValue)) / ((double)(y->wrapperValue));
                  }
                }
              }
              else if (subtypeOfFloatP(testValue001)) {
                { NumberWrapper* y001 = y;
                  FloatWrapper* y = ((FloatWrapper*)(y001));

                  floatresult = x->wrapperValue / y->wrapperValue;
                }
              }
              else {
                { OutputStringStream* stream000 = newOutputStringStream();

                  *(stream000->nativeStream) << "`" << testValue001 << "'" << " is not a valid case option";
                  throw *newStellaException(stream000->theStringReader());
                }
              }
            }
          }
        }
        else if (subtypeOfFloatP(testValue000)) {
          { NumberWrapper* x001 = x;
            FloatWrapper* x = ((FloatWrapper*)(x001));

            { Surrogate* testValue002 = safePrimaryType(y);

              if (subtypeOfIntegerP(testValue002)) {
                { NumberWrapper* y002 = y;
                  IntegerWrapper* y = ((IntegerWrapper*)(y002));

                  floatresult = x->wrapperValue / y->wrapperValue;
                }
              }
              else if (subtypeOfFloatP(testValue002)) {
                { NumberWrapper* y003 = y;
                  FloatWrapper* y = ((FloatWrapper*)(y003));

                  floatresult = x->wrapperValue / y->wrapperValue;
                }
              }
              else {
                { OutputStringStream* stream001 = newOutputStringStream();

                  *(stream001->nativeStream) << "`" << testValue002 << "'" << " is not a valid case option";
                  throw *newStellaException(stream001->theStringReader());
                }
              }
            }
          }
        }
        else {
          { OutputStringStream* stream002 = newOutputStringStream();

            *(stream002->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
            throw *newStellaException(stream002->theStringReader());
          }
        }
      }
      return (wrapFloat(floatresult));
    }
  }
  catch (std::exception ) {
    return (NULL);
  }
}

NumberWrapper* sqrtComputation(NumberWrapper* x) {
  { double floatresult = NULL_FLOAT;
    int integerresult = NULL_INTEGER;

    { Surrogate* testValue000 = safePrimaryType(x);

      if (subtypeOfIntegerP(testValue000)) {
        { NumberWrapper* x000 = x;
          IntegerWrapper* x = ((IntegerWrapper*)(x000));

          floatresult = ::sqrt((((double)(x->wrapperValue))));
          integerresult = ((int)(floatresult));
          if (floatresult == ((double)(integerresult))) {
            return (wrapInteger(integerresult));
          }
          else {
            return (wrapFloat(floatresult));
          }
        }
      }
      else if (subtypeOfFloatP(testValue000)) {
        { NumberWrapper* x001 = x;
          FloatWrapper* x = ((FloatWrapper*)(x001));

          floatresult = ::sqrt((x->wrapperValue));
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
    return (wrapFloat(floatresult));
  }
}

NumberWrapper* negateComputation(NumberWrapper* x) {
  { Surrogate* testValue000 = safePrimaryType(x);

    if (subtypeOfIntegerP(testValue000)) {
      { NumberWrapper* x000 = x;
        IntegerWrapper* x = ((IntegerWrapper*)(x000));

        return (wrapInteger(0 - unwrapInteger(x)));
      }
    }
    else if (subtypeOfFloatP(testValue000)) {
      { NumberWrapper* x001 = x;
        FloatWrapper* x = ((FloatWrapper*)(x001));

        return (wrapFloat(0.0 - unwrapFloat(x)));
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

NumberWrapper* absComputation(NumberWrapper* x) {
  { Surrogate* testValue000 = safePrimaryType(x);

    if (subtypeOfIntegerP(testValue000)) {
      { NumberWrapper* x000 = x;
        IntegerWrapper* x = ((IntegerWrapper*)(x000));

        if (unwrapInteger(x) < 0) {
          return (wrapInteger(0 - unwrapInteger(x)));
        }
        else {
          return (x);
        }
      }
    }
    else if (subtypeOfFloatP(testValue000)) {
      { NumberWrapper* x001 = x;
        FloatWrapper* x = ((FloatWrapper*)(x001));

        if (unwrapFloat(x) < 0.0) {
          return (wrapFloat(0.0 - unwrapFloat(x)));
        }
        else {
          return (x);
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

IntegerWrapper* floorComputation(NumberWrapper* x) {
  { Surrogate* testValue000 = safePrimaryType(x);

    if (subtypeOfIntegerP(testValue000)) {
      { NumberWrapper* x000 = x;
        IntegerWrapper* x = ((IntegerWrapper*)(x000));

        return (wrapInteger(stella::floor(x->wrapperValue)));
      }
    }
    else if (subtypeOfFloatP(testValue000)) {
      { NumberWrapper* x001 = x;
        FloatWrapper* x = ((FloatWrapper*)(x001));

        return (wrapInteger(stella::floor(x->wrapperValue)));
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

IntegerWrapper* ceilingComputation(NumberWrapper* x) {
  { Surrogate* testValue000 = safePrimaryType(x);

    if (subtypeOfIntegerP(testValue000)) {
      { NumberWrapper* x000 = x;
        IntegerWrapper* x = ((IntegerWrapper*)(x000));

        return (wrapInteger(stella::ceiling(x->wrapperValue)));
      }
    }
    else if (subtypeOfFloatP(testValue000)) {
      { NumberWrapper* x001 = x;
        FloatWrapper* x = ((FloatWrapper*)(x001));

        return (wrapInteger(stella::ceiling(x->wrapperValue)));
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

Object* plusConstraint(IntegerWrapper* missingArgument, NumberWrapper* x1, NumberWrapper* x2, NumberWrapper* x3) {
  { Object* value = NULL;

    switch (missingArgument->wrapperValue) {
      case -1: 
        value = (arithmeticEqualTest(plusComputation(x1, x2), x3) ? TRUE_WRAPPER : FALSE_WRAPPER);
        break;
      case 0: 
        value = minusComputation(x3, x2);
        break;
      case 1: 
        value = minusComputation(x3, x1);
        break;
      case 2: 
        value = plusComputation(x1, x2);
        break;
      default:
        break;
    }
    return (value);
  }
}

Object* minusConstraint(IntegerWrapper* missingArgument, NumberWrapper* x1, NumberWrapper* x2, NumberWrapper* x3) {
  { Object* value = NULL;

    switch (missingArgument->wrapperValue) {
      case -1: 
        value = (arithmeticEqualTest(minusComputation(x1, x2), x3) ? TRUE_WRAPPER : FALSE_WRAPPER);
        break;
      case 0: 
        value = plusComputation(x2, x3);
        break;
      case 1: 
        value = minusComputation(x1, x3);
        break;
      case 2: 
        value = minusComputation(x1, x2);
        break;
      default:
        break;
    }
    return (value);
  }
}

Object* timesConstraint(IntegerWrapper* missingArgument, NumberWrapper* x1, NumberWrapper* x2, NumberWrapper* x3) {
  { Object* value = NULL;

    switch (missingArgument->wrapperValue) {
      case -1: 
        value = (arithmeticEqualTest(timesComputation(x1, x2), x3) ? TRUE_WRAPPER : FALSE_WRAPPER);
        break;
      case 0: 
        value = divideComputation(x3, x2);
        break;
      case 1: 
        value = divideComputation(x3, x1);
        break;
      case 2: 
        value = timesComputation(x1, x2);
        break;
      default:
        break;
    }
    return (value);
  }
}

Object* divideConstraint(IntegerWrapper* missingArgument, NumberWrapper* x1, NumberWrapper* x2, NumberWrapper* x3) {
  { Object* value = NULL;

    switch (missingArgument->wrapperValue) {
      case -1: 
        { NumberWrapper* ratio = divideComputation(x1, x2);

          if (((boolean)(ratio))) {
            value = (arithmeticEqualTest(ratio, x3) ? TRUE_WRAPPER : FALSE_WRAPPER);
          }
          else {
            value = FALSE_WRAPPER;
          }
        }
        break;
      case 0: 
        value = timesComputation(x2, x3);
        break;
      case 1: 
        value = divideComputation(x1, x3);
        break;
      case 2: 
        value = divideComputation(x1, x2);
        break;
      default:
        break;
    }
    return (value);
  }
}

Object* negateConstraint(IntegerWrapper* missingArgument, NumberWrapper* x1, NumberWrapper* x2) {
  { Object* value = NULL;

    switch (missingArgument->wrapperValue) {
      case -1: 
        value = (arithmeticEqualTest(x1, negateComputation(x2)) ? TRUE_WRAPPER : FALSE_WRAPPER);
        break;
      case 0: 
        value = negateComputation(x2);
        break;
      case 1: 
        value = negateComputation(x1);
        break;
      default:
        break;
    }
    return (value);
  }
}

Object* sqrtConstraint(IntegerWrapper* missingArgument, NumberWrapper* x1, NumberWrapper* x2) {
  { Object* value = NULL;

    switch (missingArgument->wrapperValue) {
      case -1: 
        value = (arithmeticEqualTest(timesComputation(x2, x2), x1) ? TRUE_WRAPPER : FALSE_WRAPPER);
        break;
      case 0: 
        value = timesComputation(x2, x2);
        break;
      case 1: 
        if (arithmeticLessTest(x1, wrapInteger(0))) {
          value = NULL;
        }
        else {
          value = sqrtComputation(x1);
        }
        break;
      default:
        break;
    }
    return (value);
  }
}

FloatWrapper* logComputation(NumberWrapper* x) {
  { Surrogate* testValue000 = safePrimaryType(x);

    if (subtypeOfFloatP(testValue000)) {
      { NumberWrapper* x000 = x;
        FloatWrapper* x = ((FloatWrapper*)(x000));

        return (((x->wrapperValue > 0) ? wrapFloat(::log((x->wrapperValue))) : NULL));
      }
    }
    else if (subtypeOfIntegerP(testValue000)) {
      { NumberWrapper* x001 = x;
        IntegerWrapper* x = ((IntegerWrapper*)(x001));

        return (((x->wrapperValue > 0) ? wrapFloat(::log((x->numberWrapperToFloat()))) : NULL));
      }
    }
    else if (subtypeOfLongIntegerP(testValue000)) {
      { NumberWrapper* x002 = x;
        LongIntegerWrapper* x = ((LongIntegerWrapper*)(x002));

        return (((x->wrapperValue > 0) ? wrapFloat(::log((x->numberWrapperToFloat()))) : NULL));
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

FloatWrapper* log10Computation(NumberWrapper* x) {
  { Surrogate* testValue000 = safePrimaryType(x);

    if (subtypeOfFloatP(testValue000)) {
      { NumberWrapper* x000 = x;
        FloatWrapper* x = ((FloatWrapper*)(x000));

        return (((x->wrapperValue > 0) ? wrapFloat(::log((x->wrapperValue)) * RECIPROCAL_NL10) : NULL));
      }
    }
    else if (subtypeOfIntegerP(testValue000)) {
      { NumberWrapper* x001 = x;
        IntegerWrapper* x = ((IntegerWrapper*)(x001));

        return (((x->wrapperValue > 0) ? wrapFloat(::log((x->numberWrapperToFloat())) * RECIPROCAL_NL10) : NULL));
      }
    }
    else if (subtypeOfLongIntegerP(testValue000)) {
      { NumberWrapper* x002 = x;
        LongIntegerWrapper* x = ((LongIntegerWrapper*)(x002));

        return (((x->wrapperValue > 0) ? wrapFloat(::log((x->numberWrapperToFloat())) * RECIPROCAL_NL10) : NULL));
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

FloatWrapper* expComputation(NumberWrapper* x) {
  { Surrogate* testValue000 = safePrimaryType(x);

    if (subtypeOfFloatP(testValue000)) {
      { NumberWrapper* x000 = x;
        FloatWrapper* x = ((FloatWrapper*)(x000));

        return (wrapFloat(::exp((x->wrapperValue))));
      }
    }
    else if (subtypeOfIntegerP(testValue000)) {
      { NumberWrapper* x001 = x;
        IntegerWrapper* x = ((IntegerWrapper*)(x001));

        return (wrapFloat(::exp((x->numberWrapperToFloat()))));
      }
    }
    else if (subtypeOfLongIntegerP(testValue000)) {
      { NumberWrapper* x002 = x;
        LongIntegerWrapper* x = ((LongIntegerWrapper*)(x002));

        return (wrapFloat(::exp((x->numberWrapperToFloat()))));
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

FloatWrapper* exptComputation(NumberWrapper* x, NumberWrapper* n) {
  { Surrogate* testValue000 = safePrimaryType(x);

    if (subtypeOfFloatP(testValue000)) {
      { NumberWrapper* x000 = x;
        FloatWrapper* x = ((FloatWrapper*)(x000));

        return (wrapFloat(::pow((x->wrapperValue),(coerceToFloat(n)))));
      }
    }
    else if (subtypeOfIntegerP(testValue000)) {
      { NumberWrapper* x001 = x;
        IntegerWrapper* x = ((IntegerWrapper*)(x001));

        return (wrapFloat(::pow((x->numberWrapperToFloat()),(coerceToFloat(n)))));
      }
    }
    else if (subtypeOfLongIntegerP(testValue000)) {
      { NumberWrapper* x002 = x;
        LongIntegerWrapper* x = ((LongIntegerWrapper*)(x002));

        return (wrapFloat(::pow((x->numberWrapperToFloat()),(coerceToFloat(n)))));
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

Object* logConstraint(IntegerWrapper* missingArgument, NumberWrapper* x, NumberWrapper* log) {
  { Object* value = NULL;

    switch (missingArgument->wrapperValue) {
      case -1: 
        value = ((arithmeticEqualTest(logComputation(x), log) ||
            arithmeticEqualTest(x, expComputation(log))) ? TRUE_WRAPPER : FALSE_WRAPPER);
        break;
      case 0: 
        value = expComputation(log);
        break;
      case 1: 
        value = logComputation(x);
        break;
      default:
        break;
    }
    return (value);
  }
}

Object* log10Constraint(IntegerWrapper* missingArgument, NumberWrapper* x, NumberWrapper* log) {
  { Object* value = NULL;

    switch (missingArgument->wrapperValue) {
      case -1: 
        value = ((arithmeticEqualTest(log10Computation(x), log) ||
            arithmeticEqualTest(x, exptComputation(wrapFloat(10.0), log))) ? TRUE_WRAPPER : FALSE_WRAPPER);
        break;
      case 0: 
        value = exptComputation(wrapFloat(10.0), log);
        break;
      case 1: 
        value = log10Computation(x);
        break;
      default:
        break;
    }
    return (value);
  }
}

Object* expConstraint(IntegerWrapper* missingArgument, NumberWrapper* x, NumberWrapper* y) {
  { Object* value = NULL;

    switch (missingArgument->wrapperValue) {
      case -1: 
        value = ((arithmeticEqualTest(expComputation(x), y) ||
            arithmeticEqualTest(x, logComputation(y))) ? TRUE_WRAPPER : FALSE_WRAPPER);
        break;
      case 0: 
        value = logComputation(y);
        break;
      case 1: 
        value = expComputation(x);
        break;
      default:
        break;
    }
    return (value);
  }
}

IntegerInterval* newIntegerInterval() {
  { IntegerInterval* self = NULL;

    self = new IntegerInterval();
    self->dynamicSlots = newKeyValueList();
    self->surrogateValueInverse = NULL;
    self->intervalUpperBound = NULL_INTEGER;
    self->intervalLowerBound = NULL_INTEGER;
    return (self);
  }
}

Surrogate* IntegerInterval::primaryType() {
  { IntegerInterval* self = this;

    return (SGT_ARITHMETIC_PL_KERNEL_KB_INTEGER_INTERVAL);
  }
}

Object* accessIntegerIntervalSlotValue(IntegerInterval* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_ARITHMETIC_PL_KERNEL_KB_INTERVAL_LOWER_BOUND) {
    if (setvalueP) {
      self->intervalLowerBound = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->intervalLowerBound);
    }
  }
  else if (slotname == SYM_ARITHMETIC_PL_KERNEL_KB_INTERVAL_UPPER_BOUND) {
    if (setvalueP) {
      self->intervalUpperBound = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->intervalUpperBound);
    }
  }
  else {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, slotname, value, NULL);
    }
    else {
      value = self->dynamicSlots->lookup(slotname);
    }
  }
  return (value);
}

IntervalCache* newIntervalCache() {
  { IntervalCache* self = NULL;

    self = new IntervalCache();
    self->dynamicSlots = newKeyValueList();
    self->surrogateValueInverse = NULL;
    self->strictUpperBoundP = false;
    self->strictLowerBoundP = false;
    self->upperBound = NULL;
    self->lowerBound = NULL;
    self->intervalMember = NULL;
    self->homeContext = NULL;
    return (self);
  }
}

Surrogate* IntervalCache::primaryType() {
  { IntervalCache* self = this;

    return (SGT_ARITHMETIC_PL_KERNEL_KB_INTERVAL_CACHE);
  }
}

Object* accessIntervalCacheSlotValue(IntervalCache* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_ARITHMETIC_STELLA_HOME_CONTEXT) {
    if (setvalueP) {
      self->homeContext = ((Context*)(value));
    }
    else {
      value = self->homeContext;
    }
  }
  else if (slotname == SYM_ARITHMETIC_LOGIC_INTERVAL_MEMBER) {
    if (setvalueP) {
      self->intervalMember = ((LogicObject*)(value));
    }
    else {
      value = self->intervalMember;
    }
  }
  else if (slotname == SYM_ARITHMETIC_STELLA_LOWER_BOUND) {
    if (setvalueP) {
      self->lowerBound = value;
    }
    else {
      value = self->lowerBound;
    }
  }
  else if (slotname == SYM_ARITHMETIC_STELLA_UPPER_BOUND) {
    if (setvalueP) {
      self->upperBound = value;
    }
    else {
      value = self->upperBound;
    }
  }
  else if (slotname == SYM_ARITHMETIC_LOGIC_STRICT_LOWER_BOUNDp) {
    if (setvalueP) {
      self->strictLowerBoundP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->strictLowerBoundP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_ARITHMETIC_LOGIC_STRICT_UPPER_BOUNDp) {
    if (setvalueP) {
      self->strictUpperBoundP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->strictUpperBoundP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, slotname, value, NULL);
    }
    else {
      value = self->dynamicSlots->lookup(slotname);
    }
  }
  return (value);
}

void IntervalCache::printObject(std::ostream* stream) {
  { IntervalCache* self = this;

    {
      *(stream) << "|cache-of: " << self->intervalMember << " ";
      printInterval(stream, self->lowerBound, self->strictLowerBoundP, self->upperBound, self->strictUpperBoundP);
      *(stream) << "|";
    }
  }
}

void printInterval(std::ostream* stream, Object* lower, boolean strictLowerP, Object* upper, boolean strictUpperP) {
  if (strictLowerP) {
    *(stream) << "(";
  }
  else {
    *(stream) << "[";
  }
  if (((boolean)(lower))) {
    *(stream) << lower;
  }
  else {
    *(stream) << "?";
  }
  *(stream) << ",";
  if (((boolean)(upper))) {
    *(stream) << upper;
  }
  else {
    *(stream) << "?";
  }
  if (strictUpperP) {
    *(stream) << ")";
  }
  else {
    *(stream) << "]";
  }
}

IntervalCache* createIntervalCache(LogicObject* intervalmember) {
  { IntervalCache* intervalcache = newIntervalCache();

    intervalcache->intervalMember = intervalmember;
    intervalcache->homeContext = oCONTEXTo;
    assertBinaryValue(SGT_ARITHMETIC_PL_KERNEL_KB_INTERVAL_CACHE_OF, intervalmember, intervalcache);
    return (intervalcache);
  }
}

IntervalCache* getIntervalCache(LogicObject* self) {
  { Object* intervalcache = accessBinaryValue(self, SGT_ARITHMETIC_PL_KERNEL_KB_INTERVAL_CACHE_OF);

    if (((boolean)(intervalcache)) &&
        (!skolemP(intervalcache))) {
      { IntervalCache* thiscache = ((IntervalCache*)(intervalcache));
        IntervalCache* copycache = NULL;
        Proposition* proposition = NULL;

        if (thiscache->homeContext == oCONTEXTo) {
          return (thiscache);
        }
        { IntervalCache* self000 = newIntervalCache();

          self000->homeContext = oCONTEXTo;
          self000->intervalMember = self;
          self000->lowerBound = thiscache->lowerBound;
          self000->upperBound = thiscache->upperBound;
          self000->strictLowerBoundP = thiscache->strictLowerBoundP;
          self000->strictUpperBoundP = thiscache->strictUpperBoundP;
          copycache = self000;
        }
        { Proposition* value000 = NULL;

          { Proposition* p = NULL;
            Iterator* iter000 = unfilteredDependentPropositions(self, SGT_ARITHMETIC_PL_KERNEL_KB_INTERVAL_CACHE_OF)->allocateIterator();

            for (; iter000->nextP(); ) {
              p = ((Proposition*)(iter000->value));
              if (((Surrogate*)(p->operatoR)) == SGT_ARITHMETIC_PL_KERNEL_KB_INTERVAL_CACHE_OF) {
                value000 = p;
                break;
              }
            }
          }
          proposition = value000;
        }
        equateValues(proposition, valueOf((proposition->arguments->theArray)[(proposition->arguments->length() - 1)]), copycache);
        return (copycache);
      }
    }
    else {
      return (createIntervalCache(self));
    }
  }
}

void signalIntervalClash(IntervalCache* interval) {
  interval->intervalMember->markAsIncoherent();
  { const char* message000 = NULL;

    { 
      BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
      message000 = stringConcatenate("Clash in interval values ", "`", 3, stringify(interval), "'", "\n");
    }
    { const char* message = message000;
      IntervalClash* clash = newIntervalClash(message);

      clash->context = oCONTEXTo;
      clash->intervalMember = interval->intervalMember;
      clash->lowerBound = interval->lowerBound;
      clash->upperBound = interval->upperBound;
      clash->strictLowerBoundP = interval->strictLowerBoundP;
      clash->strictUpperBoundP = interval->strictUpperBoundP;
      throw *clash;
    }
  }
}

void evaluateAdjacentInequalities(LogicObject* self) {
  { Proposition* dep = NULL;
    Iterator* iter000 = allSpecializingDependentPropositions(self, SGT_ARITHMETIC_PL_KERNEL_KB_INEQUALITY);

    for (; iter000->nextP(); ) {
      dep = ((Proposition*)(iter000->value));
      { boolean alwaysP000 = true;

        { Object* arg = NULL;
          Vector* vector000 = dep->arguments;
          int index000 = 0;
          int length000 = vector000->length();

          for  (; index000 < length000; 
                index000 = index000 + 1) {
            arg = (vector000->theArray)[index000];
            if (!(isaP(valueOf(arg), SGT_ARITHMETIC_LOGIC_LOGIC_OBJECT) ||
                (!trueP(dep)))) {
              alwaysP000 = false;
              break;
            }
          }
        }
        if (alwaysP000) {
          postForEvaluation(dep, oCONTEXTo);
        }
      }
    }
  }
}

boolean IntervalCache::integerValuedMemberP() {
  { IntervalCache* interval = this;

    { LogicObject* member = interval->intervalMember;

      return (isaP(member, SGT_ARITHMETIC_LOGIC_SKOLEM) &&
          subtypeOfP(((Skolem*)(member))->skolemType, SGT_ARITHMETIC_STELLA_INTEGER));
    }
  }
}

IntegerWrapper* IntervalCache::integerLowerBound() {
  { IntervalCache* interval = this;

    { Object* lb = interval->lowerBound;

      if (((boolean)(lb))) {
        { Surrogate* testValue000 = safePrimaryType(lb);

          if (subtypeOfIntegerP(testValue000)) {
            { Object* lb000 = lb;
              IntegerWrapper* lb = ((IntegerWrapper*)(lb000));

              if (interval->strictLowerBoundP) {
                return (wrapInteger(unwrapInteger(lb) + 1));
              }
              else {
                return (lb);
              }
            }
          }
          else if (subtypeOfFloatP(testValue000)) {
            { Object* lb001 = lb;
              FloatWrapper* lb = ((FloatWrapper*)(lb001));

              if (interval->strictLowerBoundP) {
                if (integerValuedP(unwrapFloat(lb))) {
                  return (wrapInteger(stella::floor(unwrapFloat(lb)) + 1));
                }
                else {
                  return (wrapInteger(stella::ceiling(unwrapFloat(lb))));
                }
              }
              else {
                return (wrapInteger(stella::ceiling(unwrapFloat(lb))));
              }
            }
          }
          else {
            return (NULL);
          }
        }
      }
      return (NULL);
    }
  }
}

IntegerWrapper* IntervalCache::integerUpperBound() {
  { IntervalCache* interval = this;

    { Object* ub = interval->upperBound;

      if (((boolean)(ub))) {
        { Surrogate* testValue000 = safePrimaryType(ub);

          if (subtypeOfIntegerP(testValue000)) {
            { Object* ub000 = ub;
              IntegerWrapper* ub = ((IntegerWrapper*)(ub000));

              if (interval->strictUpperBoundP) {
                return (wrapInteger(unwrapInteger(ub) - 1));
              }
              else {
                return (ub);
              }
            }
          }
          else if (subtypeOfFloatP(testValue000)) {
            { Object* ub001 = ub;
              FloatWrapper* ub = ((FloatWrapper*)(ub001));

              if (interval->strictUpperBoundP) {
                if (integerValuedP(unwrapFloat(ub))) {
                  return (wrapInteger(stella::floor(unwrapFloat(ub)) - 1));
                }
                else {
                  return (wrapInteger(stella::floor(unwrapFloat(ub))));
                }
              }
              else {
                return (wrapInteger(stella::floor(unwrapFloat(ub))));
              }
            }
          }
          else {
            return (NULL);
          }
        }
      }
      return (NULL);
    }
  }
}

void IntervalCache::evaluateTighterIntegerInterval() {
  { IntervalCache* interval = this;

    { IntegerWrapper* lb = interval->integerLowerBound();
      IntegerWrapper* ub = interval->integerUpperBound();

      if (((boolean)(lb)) &&
          (((boolean)(ub)) &&
           eqlP(lb, ub))) {
        equateValues(NULL, interval->intervalMember, lb);
      }
    }
  }
}

void IntervalCache::evaluateTighterInterval() {
  { IntervalCache* interval = this;

    if (((boolean)(interval->lowerBound)) &&
        ((boolean)(interval->upperBound))) {
      if (eqlP(interval->lowerBound, interval->upperBound)) {
        if (interval->strictLowerBoundP ||
            interval->strictUpperBoundP) {
          signalIntervalClash(interval);
        }
        else {
          equateValues(NULL, interval->intervalMember, interval->lowerBound);
        }
      }
      else {
        try {
          if (compareIntervalBoundsP(SGT_ARITHMETIC_PL_KERNEL_KB_g, interval->lowerBound, interval->upperBound)) {
            signalIntervalClash(interval);
          }
          if (interval->integerValuedMemberP()) {
            interval->evaluateTighterIntegerInterval();
          }
        }
        catch (IncompatibleQuantityException ) {
          signalIntervalClash(interval);
        }
      }
    }
    evaluateAdjacentInequalities(interval->intervalMember);
  }
}

void IntervalCache::propagateInequalityToIntervalCache(Object* value, Surrogate* operatoR) {
  { IntervalCache* self = this;

    if (nullLiteralWrapperP(value)) {
      return;
    }
    if (!(isaP(value, SGT_ARITHMETIC_STELLA_NUMBER_WRAPPER) ||
        isaP(value, SGT_ARITHMETIC_LOGIC_QUANTITY_LOGIC_WRAPPER))) {
      return;
    }
    { boolean tighterintervalP = false;

      try {
        if (operatoR == SGT_ARITHMETIC_PL_KERNEL_KB_g) {
          if ((!((boolean)(self->lowerBound))) ||
              (compareIntervalBoundsP(SGT_ARITHMETIC_PL_KERNEL_KB_g, value, self->lowerBound) ||
               (eqlP(value, self->lowerBound) &&
                (!self->strictLowerBoundP)))) {
            self->lowerBound = value;
            self->strictLowerBoundP = true;
            tighterintervalP = true;
          }
        }
        else if (operatoR == SGT_ARITHMETIC_PL_KERNEL_KB_ge) {
          if ((!((boolean)(self->lowerBound))) ||
              compareIntervalBoundsP(SGT_ARITHMETIC_PL_KERNEL_KB_g, value, self->lowerBound)) {
            self->lowerBound = value;
            self->strictLowerBoundP = false;
            tighterintervalP = true;
          }
        }
        else if (operatoR == SGT_ARITHMETIC_PL_KERNEL_KB_l) {
          if ((!((boolean)(self->upperBound))) ||
              (compareIntervalBoundsP(SGT_ARITHMETIC_PL_KERNEL_KB_l, value, self->upperBound) ||
               ((value == self->upperBound) &&
                (!self->strictUpperBoundP)))) {
            self->upperBound = value;
            self->strictUpperBoundP = true;
            tighterintervalP = true;
          }
        }
        else if (operatoR == SGT_ARITHMETIC_PL_KERNEL_KB_el) {
          if ((!((boolean)(self->upperBound))) ||
              compareIntervalBoundsP(SGT_ARITHMETIC_PL_KERNEL_KB_l, value, self->upperBound)) {
            self->upperBound = value;
            self->strictUpperBoundP = false;
            tighterintervalP = true;
          }
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << operatoR << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
        }
      }
      catch (IncompatibleQuantityException ) {
        signalIntervalClash(self);
      }
      if (tighterintervalP) {
        self->evaluateTighterInterval();
      }
    }
  }
}

Surrogate* inverseInequalityOperator(Surrogate* operatoR) {
  if (operatoR == SGT_ARITHMETIC_PL_KERNEL_KB_g) {
    return (SGT_ARITHMETIC_PL_KERNEL_KB_l);
  }
  else if (operatoR == SGT_ARITHMETIC_PL_KERNEL_KB_l) {
    return (SGT_ARITHMETIC_PL_KERNEL_KB_g);
  }
  else if (operatoR == SGT_ARITHMETIC_PL_KERNEL_KB_ge) {
    return (SGT_ARITHMETIC_PL_KERNEL_KB_el);
  }
  else if (operatoR == SGT_ARITHMETIC_PL_KERNEL_KB_el) {
    return (SGT_ARITHMETIC_PL_KERNEL_KB_ge);
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << operatoR << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

void unifyIntervalCaches(IntervalCache* cache1, IntervalCache* cache2, Surrogate* operatoR) {
  { boolean dummy1;
    boolean dummy2;
    boolean dummy3;
    boolean dummy4;

    if ((operatoR == SGT_ARITHMETIC_PL_KERNEL_KB_g) ||
        (operatoR == SGT_ARITHMETIC_PL_KERNEL_KB_ge)) {
      cache1->propagateInequalityToIntervalCache(accessIntervalCacheBounds(cache2, KWD_ARITHMETIC_LOWER_BOUND, dummy1), operatoR);
      cache2->propagateInequalityToIntervalCache(accessIntervalCacheBounds(cache1, KWD_ARITHMETIC_UPPER_BOUND, dummy2), inverseInequalityOperator(operatoR));
    }
    else if ((operatoR == SGT_ARITHMETIC_PL_KERNEL_KB_l) ||
        (operatoR == SGT_ARITHMETIC_PL_KERNEL_KB_el)) {
      cache1->propagateInequalityToIntervalCache(accessIntervalCacheBounds(cache2, KWD_ARITHMETIC_UPPER_BOUND, dummy3), operatoR);
      cache2->propagateInequalityToIntervalCache(accessIntervalCacheBounds(cache1, KWD_ARITHMETIC_LOWER_BOUND, dummy4), inverseInequalityOperator(operatoR));
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << operatoR << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

Object* accessIntervalBounds(Object* x, Keyword* lowerorupper, boolean& _Return1) {
  { Surrogate* testValue000 = safePrimaryType(x);

    if (subtypeOfP(testValue000, SGT_ARITHMETIC_STELLA_NUMBER_WRAPPER)) {
      { Object* x000 = x;
        NumberWrapper* x = ((NumberWrapper*)(x000));

        _Return1 = false;
        return (x);
      }
    }
    else if (subtypeOfP(testValue000, SGT_ARITHMETIC_LOGIC_QUANTITY_LOGIC_WRAPPER)) {
      { Object* x001 = x;
        QuantityLogicWrapper* x = ((QuantityLogicWrapper*)(x001));

        _Return1 = false;
        return (x);
      }
    }
    else {
      return (accessIntervalCacheBounds(((IntervalCache*)(accessBinaryValue(x, SGT_ARITHMETIC_PL_KERNEL_KB_INTERVAL_CACHE_OF))), lowerorupper, _Return1));
    }
  }
}

Object* accessIntervalCacheBounds(IntervalCache* intervalcache, Keyword* lowerorupper, boolean& _Return1) {
  if (!((boolean)(intervalcache))) {
    _Return1 = false;
    return (NULL);
  }
  else {
    if (lowerorupper == KWD_ARITHMETIC_LOWER_BOUND) {
      _Return1 = intervalcache->strictLowerBoundP;
      return (intervalcache->lowerBound);
    }
    else if (lowerorupper == KWD_ARITHMETIC_UPPER_BOUND) {
      _Return1 = intervalcache->strictUpperBoundP;
      return (intervalcache->upperBound);
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << lowerorupper << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

boolean compareIntervalBoundsP(Surrogate* relation, Object* x, Object* y) {
  if (nullLiteralWrapperP(x) ||
      nullLiteralWrapperP(y)) {
    return (false);
  }
  if (relation == SGT_ARITHMETIC_STELLA_e) {
    return (eqlP(x, y));
  }
  { Surrogate* testValue000 = safePrimaryType(x);

    if (subtypeOfP(testValue000, SGT_ARITHMETIC_STELLA_NUMBER_WRAPPER)) {
      { Object* x000 = x;
        NumberWrapper* x = ((NumberWrapper*)(x000));

        { Surrogate* testValue001 = safePrimaryType(y);

          if (subtypeOfP(testValue001, SGT_ARITHMETIC_STELLA_NUMBER_WRAPPER)) {
            { Object* y000 = y;
              NumberWrapper* y = ((NumberWrapper*)(y000));

              { double floatX = x->numberWrapperToFloat();
                double floatY = y->numberWrapperToFloat();

                if (relation == SGT_ARITHMETIC_PL_KERNEL_KB_el) {
                  return (floatX <= floatY);
                }
                else if (relation == SGT_ARITHMETIC_PL_KERNEL_KB_l) {
                  return (floatX < floatY);
                }
                else if (relation == SGT_ARITHMETIC_PL_KERNEL_KB_ge) {
                  return (floatX >= floatY);
                }
                else if (relation == SGT_ARITHMETIC_PL_KERNEL_KB_g) {
                  return (floatX > floatY);
                }
                else {
                  { OutputStringStream* stream000 = newOutputStringStream();

                    *(stream000->nativeStream) << "`" << relation << "'" << " is not a valid case option";
                    throw *newStellaException(stream000->theStringReader());
                  }
                }
              }
            }
          }
          else if (subtypeOfP(testValue001, SGT_ARITHMETIC_LOGIC_QUANTITY_LOGIC_WRAPPER)) {
            { Object* y001 = y;
              QuantityLogicWrapper* y = ((QuantityLogicWrapper*)(y001));

              { stella::Quantity* quantityY = y->wrapperValue;
                stella::Quantity* quantityX = quantityY->coerceTo(x);

                if (relation == SGT_ARITHMETIC_PL_KERNEL_KB_el) {
                  return (quantityX->lessEqualP(quantityY));
                }
                else if (relation == SGT_ARITHMETIC_PL_KERNEL_KB_l) {
                  return (quantityX->lessP(quantityY));
                }
                else if (relation == SGT_ARITHMETIC_PL_KERNEL_KB_ge) {
                  return (quantityX->greaterEqualP(quantityY));
                }
                else if (relation == SGT_ARITHMETIC_PL_KERNEL_KB_g) {
                  return (quantityX->greaterP(quantityY));
                }
                else {
                  { OutputStringStream* stream001 = newOutputStringStream();

                    *(stream001->nativeStream) << "`" << relation << "'" << " is not a valid case option";
                    throw *newStellaException(stream001->theStringReader());
                  }
                }
              }
            }
          }
          else {
            { OutputStringStream* stream002 = newOutputStringStream();

              *(stream002->nativeStream) << "`" << testValue001 << "'" << " is not a valid case option";
              throw *newStellaException(stream002->theStringReader());
            }
          }
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_ARITHMETIC_LOGIC_QUANTITY_LOGIC_WRAPPER)) {
      { Object* x001 = x;
        QuantityLogicWrapper* x = ((QuantityLogicWrapper*)(x001));

        { Surrogate* testValue002 = safePrimaryType(y);

          if (subtypeOfP(testValue002, SGT_ARITHMETIC_STELLA_NUMBER_WRAPPER)) {
            { Object* y002 = y;
              NumberWrapper* y = ((NumberWrapper*)(y002));

              { stella::Quantity* quantityX = x->wrapperValue;
                stella::Quantity* quantityY = quantityX->coerceTo(y);

                if (relation == SGT_ARITHMETIC_PL_KERNEL_KB_el) {
                  return (quantityX->lessEqualP(quantityY));
                }
                else if (relation == SGT_ARITHMETIC_PL_KERNEL_KB_l) {
                  return (quantityX->lessP(quantityY));
                }
                else if (relation == SGT_ARITHMETIC_PL_KERNEL_KB_ge) {
                  return (quantityX->greaterEqualP(quantityY));
                }
                else if (relation == SGT_ARITHMETIC_PL_KERNEL_KB_g) {
                  return (quantityX->greaterP(quantityY));
                }
                else {
                  { OutputStringStream* stream003 = newOutputStringStream();

                    *(stream003->nativeStream) << "`" << relation << "'" << " is not a valid case option";
                    throw *newStellaException(stream003->theStringReader());
                  }
                }
              }
            }
          }
          else if (subtypeOfP(testValue002, SGT_ARITHMETIC_LOGIC_QUANTITY_LOGIC_WRAPPER)) {
            { Object* y003 = y;
              QuantityLogicWrapper* y = ((QuantityLogicWrapper*)(y003));

              if (relation == SGT_ARITHMETIC_PL_KERNEL_KB_el) {
                return (x->wrapperValue->lessEqualP(y->wrapperValue));
              }
              else if (relation == SGT_ARITHMETIC_PL_KERNEL_KB_l) {
                return (x->wrapperValue->lessP(y->wrapperValue));
              }
              else if (relation == SGT_ARITHMETIC_PL_KERNEL_KB_ge) {
                return (x->wrapperValue->greaterEqualP(y->wrapperValue));
              }
              else if (relation == SGT_ARITHMETIC_PL_KERNEL_KB_g) {
                return (x->wrapperValue->greaterP(y->wrapperValue));
              }
              else {
                { OutputStringStream* stream004 = newOutputStringStream();

                  *(stream004->nativeStream) << "`" << relation << "'" << " is not a valid case option";
                  throw *newStellaException(stream004->theStringReader());
                }
              }
            }
          }
          else {
            { OutputStringStream* stream005 = newOutputStringStream();

              *(stream005->nativeStream) << "`" << testValue002 << "'" << " is not a valid case option";
              throw *newStellaException(stream005->theStringReader());
            }
          }
        }
      }
    }
    else {
      { OutputStringStream* stream006 = newOutputStringStream();

        *(stream006->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
        throw *newStellaException(stream006->theStringReader());
      }
    }
  }
}

boolean nullNumberP(NumberWrapper* self) {
  if (!((boolean)(self))) {
    return (true);
  }
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfIntegerP(testValue000)) {
      { NumberWrapper* self000 = self;
        IntegerWrapper* self = ((IntegerWrapper*)(self000));

        return (self->wrapperValue == NULL_INTEGER);
      }
    }
    else if (subtypeOfFloatP(testValue000)) {
      { NumberWrapper* self001 = self;
        FloatWrapper* self = ((FloatWrapper*)(self001));

        return (self->wrapperValue == NULL_FLOAT);
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

boolean nullLiteralWrapperP(Object* self) {
  if (!((boolean)(self))) {
    return (true);
  }
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfIntegerP(testValue000)) {
      { Object* self000 = self;
        IntegerWrapper* self = ((IntegerWrapper*)(self000));

        return (self->wrapperValue == NULL_INTEGER);
      }
    }
    else if (subtypeOfFloatP(testValue000)) {
      { Object* self001 = self;
        FloatWrapper* self = ((FloatWrapper*)(self001));

        return (self->wrapperValue == NULL_FLOAT);
      }
    }
    else if (subtypeOfP(testValue000, SGT_ARITHMETIC_LOGIC_QUANTITY_LOGIC_WRAPPER)) {
      { Object* self002 = self;
        QuantityLogicWrapper* self = ((QuantityLogicWrapper*)(self002));

        return (!((boolean)(self->wrapperValue)));
      }
    }
    else if (subtypeOfStringP(testValue000)) {
      { Object* self003 = self;
        StringWrapper* self = ((StringWrapper*)(self003));

        return (self->wrapperValue == NULL);
      }
    }
    else if (subtypeOfCharacterP(testValue000)) {
      { Object* self004 = self;
        CharacterWrapper* self = ((CharacterWrapper*)(self004));

        return (self->wrapperValue == NULL_CHARACTER);
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

boolean satisfiesIntervalBoundsP(Object* object, Object* value) {
  { Object* lb = NULL;
    boolean strictlowerP = false;
    Object* ub = NULL;
    boolean strictupperP = false;
    boolean answer = true;

    lb = accessIntervalBounds(object, KWD_ARITHMETIC_LOWER_BOUND, strictlowerP);
    ub = accessIntervalBounds(object, KWD_ARITHMETIC_UPPER_BOUND, strictupperP);
    if (nullLiteralWrapperP(value)) {
      return (false);
    }
    if (!(nullLiteralWrapperP(lb))) {
      if (strictlowerP) {
        answer = compareIntervalBoundsP(SGT_ARITHMETIC_PL_KERNEL_KB_l, lb, value);
      }
      else {
        answer = compareIntervalBoundsP(SGT_ARITHMETIC_PL_KERNEL_KB_el, lb, value);
      }
    }
    if (!(nullLiteralWrapperP(ub))) {
      if (strictupperP) {
        answer = answer &&
            compareIntervalBoundsP(SGT_ARITHMETIC_PL_KERNEL_KB_l, value, ub);
      }
      else {
        answer = answer &&
            compareIntervalBoundsP(SGT_ARITHMETIC_PL_KERNEL_KB_el, value, ub);
      }
    }
    return (answer);
  }
}

Keyword* lessSpecialistHelper(ControlFrame* frame, Surrogate* relation, Object* xarg, Object* yarg) {
  { Object* x = argumentBoundTo(xarg);
    Object* y = argumentBoundTo(yarg);
    Object* xbound = NULL;
    boolean strictxP = false;
    Object* ybound = NULL;
    boolean strictyP = false;
    boolean successP = false;

    if (!((boolean)(y))) {
      if (!((boolean)(x))) {
        return (KWD_ARITHMETIC_TERMINAL_FAILURE);
      }
      xbound = accessIntervalBounds(x, KWD_ARITHMETIC_UPPER_BOUND, strictxP);
      if ((!nullLiteralWrapperP(xbound)) &&
          ((relation == SGT_ARITHMETIC_PL_KERNEL_KB_el) ||
           isaP(xbound, SGT_ARITHMETIC_STELLA_INTEGER_WRAPPER))) {
        if (relation == SGT_ARITHMETIC_PL_KERNEL_KB_l) {
          xbound = wrapInteger(((IntegerWrapper*)(xbound))->wrapperValue + 1);
        }
        successP = bindVariableToValueP(((PatternVariable*)(yarg)), xbound, true);
      }
      return (selectProofResult(successP, false, false));
    }
    if (!((boolean)(x))) {
      ybound = accessIntervalBounds(y, KWD_ARITHMETIC_LOWER_BOUND, strictyP);
      if ((!nullNumberP(((NumberWrapper*)(ybound)))) &&
          ((relation == SGT_ARITHMETIC_PL_KERNEL_KB_el) ||
           isaP(ybound, SGT_ARITHMETIC_STELLA_INTEGER_WRAPPER))) {
        if (relation == SGT_ARITHMETIC_PL_KERNEL_KB_l) {
          ybound = wrapInteger(((IntegerWrapper*)(ybound))->wrapperValue - 1);
        }
        successP = bindVariableToValueP(((PatternVariable*)(xarg)), ybound, true);
      }
      return (selectProofResult(successP, false, false));
    }
    { boolean successP = false;

      xbound = accessIntervalBounds(x, KWD_ARITHMETIC_UPPER_BOUND, strictxP);
      ybound = accessIntervalBounds(y, KWD_ARITHMETIC_LOWER_BOUND, strictyP);
      try {
        if (relation == SGT_ARITHMETIC_PL_KERNEL_KB_l) {
          successP = ((strictxP ||
              strictyP) &&
              compareIntervalBoundsP(SGT_ARITHMETIC_PL_KERNEL_KB_el, xbound, ybound)) ||
              compareIntervalBoundsP(SGT_ARITHMETIC_PL_KERNEL_KB_l, xbound, ybound);
        }
        else if (relation == SGT_ARITHMETIC_PL_KERNEL_KB_el) {
          successP = compareIntervalBoundsP(relation, xbound, ybound);
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << relation << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
        }
      }
      catch (IncompatibleQuantityException ) {
        setFrameTruthValue(frame, UNKNOWN_TRUTH_VALUE);
        return (KWD_ARITHMETIC_TERMINAL_FAILURE);
      }
      if (successP) {
        setFrameTruthValue(frame, TRUE_TRUTH_VALUE);
        return (KWD_ARITHMETIC_FINAL_SUCCESS);
      }
      xbound = accessIntervalBounds(x, KWD_ARITHMETIC_LOWER_BOUND, strictxP);
      ybound = accessIntervalBounds(y, KWD_ARITHMETIC_UPPER_BOUND, strictyP);
      try {
        if (relation == SGT_ARITHMETIC_PL_KERNEL_KB_el) {
          successP = ((strictxP ||
              strictyP) &&
              compareIntervalBoundsP(SGT_ARITHMETIC_PL_KERNEL_KB_el, ybound, xbound)) ||
              compareIntervalBoundsP(SGT_ARITHMETIC_PL_KERNEL_KB_l, ybound, xbound);
        }
        else if (relation == SGT_ARITHMETIC_PL_KERNEL_KB_l) {
          successP = compareIntervalBoundsP(SGT_ARITHMETIC_PL_KERNEL_KB_el, ybound, xbound);
        }
        else {
          { OutputStringStream* stream001 = newOutputStringStream();

            *(stream001->nativeStream) << "`" << relation << "'" << " is not a valid case option";
            throw *newStellaException(stream001->theStringReader());
          }
        }
      }
      catch (IncompatibleQuantityException ) {
        setFrameTruthValue(frame, UNKNOWN_TRUTH_VALUE);
        return (KWD_ARITHMETIC_TERMINAL_FAILURE);
      }
      if (successP) {
        setFrameTruthValue(frame, FALSE_TRUTH_VALUE);
        return (KWD_ARITHMETIC_TERMINAL_FAILURE);
      }
    }
    if (skolemP(x) &&
        skolemP(y)) {
      return (KWD_ARITHMETIC_FAILURE);
    }
    else {
      return (KWD_ARITHMETIC_TERMINAL_FAILURE);
    }
  }
}

Keyword* inequalitySpecialist(ControlFrame* frame, Keyword* lastmove) {
  lastmove = lastmove;
  { Proposition* proposition = frame->proposition;
    Surrogate* relation = ((Surrogate*)(proposition->operatoR));

    if (oREVERSEPOLARITYpo) {
      { 
        BIND_STELLA_SPECIAL(oREVERSEPOLARITYpo, boolean, false);
        if (relation == SGT_ARITHMETIC_PL_KERNEL_KB_l) {
          return (lessSpecialistHelper(frame, SGT_ARITHMETIC_PL_KERNEL_KB_el, (proposition->arguments->theArray)[1], (proposition->arguments->theArray)[0]));
        }
        else if (relation == SGT_ARITHMETIC_PL_KERNEL_KB_el) {
          return (lessSpecialistHelper(frame, SGT_ARITHMETIC_PL_KERNEL_KB_l, (proposition->arguments->theArray)[1], (proposition->arguments->theArray)[0]));
        }
        else if (relation == SGT_ARITHMETIC_PL_KERNEL_KB_g) {
          return (lessSpecialistHelper(frame, SGT_ARITHMETIC_PL_KERNEL_KB_el, (proposition->arguments->theArray)[0], (proposition->arguments->theArray)[1]));
        }
        else if (relation == SGT_ARITHMETIC_PL_KERNEL_KB_ge) {
          return (lessSpecialistHelper(frame, SGT_ARITHMETIC_PL_KERNEL_KB_l, (proposition->arguments->theArray)[0], (proposition->arguments->theArray)[1]));
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << relation << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
        }
      }
    }
    else {
      if (relation == SGT_ARITHMETIC_PL_KERNEL_KB_l) {
        return (lessSpecialistHelper(frame, SGT_ARITHMETIC_PL_KERNEL_KB_l, (proposition->arguments->theArray)[0], (proposition->arguments->theArray)[1]));
      }
      else if (relation == SGT_ARITHMETIC_PL_KERNEL_KB_el) {
        return (lessSpecialistHelper(frame, SGT_ARITHMETIC_PL_KERNEL_KB_el, (proposition->arguments->theArray)[0], (proposition->arguments->theArray)[1]));
      }
      else if (relation == SGT_ARITHMETIC_PL_KERNEL_KB_g) {
        return (lessSpecialistHelper(frame, SGT_ARITHMETIC_PL_KERNEL_KB_l, (proposition->arguments->theArray)[1], (proposition->arguments->theArray)[0]));
      }
      else if (relation == SGT_ARITHMETIC_PL_KERNEL_KB_ge) {
        return (lessSpecialistHelper(frame, SGT_ARITHMETIC_PL_KERNEL_KB_el, (proposition->arguments->theArray)[1], (proposition->arguments->theArray)[0]));
      }
      else {
        { OutputStringStream* stream001 = newOutputStringStream();

          *(stream001->nativeStream) << "`" << relation << "'" << " is not a valid case option";
          throw *newStellaException(stream001->theStringReader());
        }
      }
    }
  }
}

void inequalityEvaluator(Proposition* self) {
  if (!(trueP(self))) {
    return;
  }
  { Object* arg1 = (self->arguments->theArray)[0];
    Object* arg2 = (self->arguments->theArray)[1];
    Object* value1 = valueOf(arg1);
    Object* value2 = valueOf(arg2);
    boolean skolem1P = isaP(value1, SGT_ARITHMETIC_LOGIC_LOGIC_OBJECT);
    boolean skolem2P = isaP(value2, SGT_ARITHMETIC_LOGIC_LOGIC_OBJECT);
    Surrogate* operatoR = ((Surrogate*)(self->operatoR));

    if (eqlP(value1, value2)) {
      if (!eqlP(arg1, value1)) {
        if (!eqlP(arg2, value2)) {
          unifyIntervalCaches(getIntervalCache(((LogicObject*)(arg1))), getIntervalCache(((LogicObject*)(arg2))), SGT_ARITHMETIC_PL_KERNEL_KB_el);
          unifyIntervalCaches(getIntervalCache(((LogicObject*)(arg1))), getIntervalCache(((LogicObject*)(arg2))), SGT_ARITHMETIC_PL_KERNEL_KB_ge);
          value2 = arg2;
          skolem2P = true;
        }
        else {
          getIntervalCache(((LogicObject*)(arg1)))->propagateInequalityToIntervalCache(value2, SGT_ARITHMETIC_PL_KERNEL_KB_el);
          getIntervalCache(((LogicObject*)(arg1)))->propagateInequalityToIntervalCache(value2, SGT_ARITHMETIC_PL_KERNEL_KB_ge);
        }
        value1 = arg1;
        skolem1P = true;
      }
      else if (!eqlP(arg2, value2)) {
        if (!eqlP(arg1, value1)) {
          unifyIntervalCaches(getIntervalCache(((LogicObject*)(arg2))), getIntervalCache(((LogicObject*)(arg1))), SGT_ARITHMETIC_PL_KERNEL_KB_el);
          unifyIntervalCaches(getIntervalCache(((LogicObject*)(arg2))), getIntervalCache(((LogicObject*)(arg1))), SGT_ARITHMETIC_PL_KERNEL_KB_ge);
          value1 = arg1;
          skolem1P = true;
        }
        else {
          getIntervalCache(((LogicObject*)(arg2)))->propagateInequalityToIntervalCache(value1, SGT_ARITHMETIC_PL_KERNEL_KB_el);
          getIntervalCache(((LogicObject*)(arg2)))->propagateInequalityToIntervalCache(value1, SGT_ARITHMETIC_PL_KERNEL_KB_ge);
        }
        value2 = arg2;
        skolem2P = true;
      }
    }
    if (skolem1P) {
      if (skolem2P) {
        unifyIntervalCaches(getIntervalCache(((LogicObject*)(value1))), getIntervalCache(((LogicObject*)(value2))), operatoR);
      }
      else {
        getIntervalCache(((LogicObject*)(value1)))->propagateInequalityToIntervalCache(value2, operatoR);
      }
    }
    else {
      if (skolem2P) {
        getIntervalCache(((LogicObject*)(value2)))->propagateInequalityToIntervalCache(value1, inverseInequalityOperator(operatoR));
      }
      else {
        if (compareIntervalBoundsP(operatoR, value1, value2)) {
          assignTruthValue(self, TRUE_WRAPPER);
        }
        else if (trueP(self)) {
          signalTruthValueClash(self);
        }
        else {
          assignTruthValue(self, FALSE_WRAPPER);
        }
      }
    }
  }
}

StringWrapper* stringConcatenateComputation(Object* x, Cons* yargs) {
  { 
    BIND_STELLA_SPECIAL(oPRINTMODEo, Keyword*, KWD_ARITHMETIC_ORIGINAL);
    { OutputStringStream* out = newOutputStringStream();

      *(out->nativeStream) << pli::objectToString(x);
      { Object* arg = NULL;
        Cons* iter000 = yargs;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          arg = iter000->value;
          *(out->nativeStream) << pli::objectToString(arg);
        }
      }
      return (wrapString(out->theStringReader()));
    }
  }
}

Keyword* subsequenceSpecialist(ControlFrame* frame, Keyword* lastmove) {
  lastmove = lastmove;
  { Vector* arguments = frame->proposition->arguments;
    Object* superarg = (arguments->theArray)[0];
    Object* p1Arg = (arguments->theArray)[1];
    Object* p2Arg = (arguments->theArray)[2];
    Object* subarg = (arguments->theArray)[3];
    Iterator* iterator = ((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_ARITHMETIC_STELLA_ITERATOR, NULL)));

    if (!((boolean)(iterator))) {
      { Object* superargvalue = argumentBoundTo(superarg);
        const char* super = (stringP(superargvalue) ? unwrapString(((StringWrapper*)(superargvalue))) : pli::objectToString(superargvalue));
        int superlength = NULL_INTEGER;
        Object* p1Argvalue = argumentBoundTo(p1Arg);
        int p1 = NULL_INTEGER;
        Object* p2Argvalue = argumentBoundTo(p2Arg);
        int p2 = NULL_INTEGER;
        Object* subargvalue = argumentBoundTo(subarg);
        const char* sub = (stringP(subargvalue) ? unwrapString(((StringWrapper*)(subargvalue))) : pli::objectToString(subargvalue));
        int sublength = ((sub != NULL) ? strlen(sub) : ((int)(NULL_INTEGER)));

        if (super == NULL) {
          return (KWD_ARITHMETIC_FAILURE);
        }
        superlength = strlen(super);
        if (((boolean)(p1Argvalue))) {
          if (integerP(p1Argvalue)) {
            p1 = ((IntegerWrapper*)(p1Argvalue))->wrapperValue;
          }
          else {
            return (KWD_ARITHMETIC_TERMINAL_FAILURE);
          }
          if (p1 < 0) {
            p1 = superlength + p1 + 1;
          }
          if ((p1 < 0) ||
              (p1 > superlength)) {
            return (KWD_ARITHMETIC_TERMINAL_FAILURE);
          }
        }
        if (((boolean)(p2Argvalue))) {
          if (integerP(p2Argvalue)) {
            p2 = ((IntegerWrapper*)(p2Argvalue))->wrapperValue;
          }
          else {
            return (KWD_ARITHMETIC_TERMINAL_FAILURE);
          }
          if (p2 < 0) {
            p2 = superlength + p2 + 1;
          }
          if ((p2 > superlength) ||
              ((p2 < 0) ||
               ((p1 != NULL_INTEGER) &&
                (p1 > p2)))) {
            return (KWD_ARITHMETIC_TERMINAL_FAILURE);
          }
        }
        if (sub == NULL) {
          if ((p1 != NULL_INTEGER) &&
              (p2 != NULL_INTEGER)) {
            return (selectProofResult(bindArgumentToValueP(subarg, wrapString(stringSubsequence(super, p1, p2)), true), false, true));
          }
          else {
            return (KWD_ARITHMETIC_FAILURE);
          }
        }
        else if (p1 == NULL_INTEGER) {
          if (p2 == NULL_INTEGER) {
            setDynamicSlotValue(frame->dynamicSlots, SYM_ARITHMETIC_STELLA_ITERATOR, newSubstringPositionIterator(super, sub), NULL);
          }
          else {
            if (sublength > p2) {
              return (KWD_ARITHMETIC_TERMINAL_FAILURE);
            }
            else if (stringEqlP(stringSubsequence(super, p2 - sublength, p2), sub)) {
              return (selectProofResult(bindArgumentToValueP(p1Arg, wrapInteger(p2 - sublength), true), false, true));
            }
            else {
              return (KWD_ARITHMETIC_TERMINAL_FAILURE);
            }
          }
        }
        else if (p2 == NULL_INTEGER) {
          if ((p1 + sublength) > superlength) {
            return (KWD_ARITHMETIC_TERMINAL_FAILURE);
          }
          else if (stringEqlP(sub, stringSubsequence(super, p1, p1 + sublength))) {
            return (selectProofResult(bindArgumentToValueP(p2Arg, wrapInteger(p1 + sublength), true), false, true));
          }
          else {
            return (KWD_ARITHMETIC_TERMINAL_FAILURE);
          }
        }
        else {
          { boolean matchP = bindArgumentToValueP(subarg, wrapString(stringSubsequence(super, p1, p2)), true);

            setFrameTruthValue(frame, (matchP ? TRUE_TRUTH_VALUE : FALSE_TRUTH_VALUE));
            return (selectProofResult(matchP, false, true));
          }
        }
      }
    }
    iterator = ((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_ARITHMETIC_STELLA_ITERATOR, NULL)));
    if (iterator->nextP() &&
        (bindArgumentToValueP(p1Arg, ((Cons*)(iterator->value))->value, true) &&
         bindArgumentToValueP(p2Arg, ((Cons*)(iterator->value))->rest->value, true))) {
      return (KWD_ARITHMETIC_CONTINUING_SUCCESS);
    }
    else {
      return (KWD_ARITHMETIC_TERMINAL_FAILURE);
    }
  }
}

const char* normalizeStringComputationArgs(Object* x, Object* start, Object* end, boolean coerceP, int& _Return1, int& _Return2) {
  if (!(integerP(start) &&
      integerP(end))) {
    { const char* _Return0 = NULL;

      _Return1 = NULL_INTEGER;
      _Return2 = NULL_INTEGER;
      return (_Return0);
    }
  }
  { int thestart = ((IntegerWrapper*)(start))->wrapperValue;
    int theend = ((IntegerWrapper*)(end))->wrapperValue;
    const char* name = (stringP(x) ? ((StringWrapper*)(x))->wrapperValue : objectNameString(x));
    int namelength = 0;

    if ((name == NULL) &&
        coerceP) {
      name = pli::objectToString(x);
    }
    if (!(name != NULL)) {
      { const char* _Return0 = NULL;

        _Return1 = NULL_INTEGER;
        _Return2 = NULL_INTEGER;
        return (_Return0);
      }
    }
    namelength = strlen(name);
    if (thestart < 0) {
      thestart = namelength + thestart + 1;
    }
    if (thestart < 0) {
      { const char* _Return0 = NULL;

        _Return1 = NULL_INTEGER;
        _Return2 = NULL_INTEGER;
        return (_Return0);
      }
    }
    if (theend < 0) {
      theend = namelength + theend + 1;
    }
    if ((theend < 0) ||
        (theend > namelength)) {
      { const char* _Return0 = NULL;

        _Return1 = NULL_INTEGER;
        _Return2 = NULL_INTEGER;
        return (_Return0);
      }
    }
    else {
      _Return1 = thestart;
      _Return2 = theend;
      return (name);
    }
  }
}

IntegerWrapper* stringMatchComputationHelper(Object* pattern, Object* x, Object* start, Object* end, boolean ignoreCaseP) {
  if (!(stringP(pattern))) {
    return (NULL);
  }
  { const char* thepattern = ((StringWrapper*)(pattern))->wrapperValue;
    int matchposition = NULL_INTEGER;

    { const char* name = NULL;
      int thestart = NULL_INTEGER;
      int theend = NULL_INTEGER;

      name = normalizeStringComputationArgs(x, start, end, false, thestart, theend);
      if (name == NULL) {
        return (NULL);
      }
      if (ignoreCaseP) {
        matchposition = stringSearchIgnoreCase(name, thepattern, thestart);
      }
      else {
        matchposition = stringSearch(name, thepattern, thestart);
      }
      if ((matchposition != NULL_INTEGER) &&
          ((matchposition + strlen(thepattern)) <= theend)) {
        return (wrapInteger(matchposition));
      }
      else {
        return (NULL);
      }
    }
  }
}

IntegerWrapper* stringMatchComputation(Object* pattern, Object* x, Object* start, Object* end) {
  return (stringMatchComputationHelper(pattern, x, start, end, false));
}

IntegerWrapper* stringMatchIgnoreCaseComputation(Object* pattern, Object* x, Object* start, Object* end) {
  return (stringMatchComputationHelper(pattern, x, start, end, true));
}

StringWrapper* stringUpcaseComputation(Object* x, Object* start, Object* end) {
  { const char* name = NULL;
    int thestart = NULL_INTEGER;
    int theend = NULL_INTEGER;

    name = normalizeStringComputationArgs(x, start, end, false, thestart, theend);
    if (name == NULL) {
      return (NULL);
    }
    if ((thestart == 0) &&
        (theend == strlen(name))) {
      return (wrapString(stella::stringUpcase(name)));
    }
    else {
      return (wrapString(stringConcatenate(stringSubsequence(name, 0, thestart), stella::stringUpcase(stringSubsequence(name, thestart, theend)), 1, stringSubsequence(name, theend, NULL_INTEGER))));
    }
  }
}

StringWrapper* stringDowncaseComputation(Object* x, Object* start, Object* end) {
  { const char* name = NULL;
    int thestart = NULL_INTEGER;
    int theend = NULL_INTEGER;

    name = normalizeStringComputationArgs(x, start, end, false, thestart, theend);
    if (name == NULL) {
      return (NULL);
    }
    if ((thestart == 0) &&
        (theend == strlen(name))) {
      return (wrapString(stella::stringDowncase(name)));
    }
    else {
      return (wrapString(stringConcatenate(stringSubsequence(name, 0, thestart), stella::stringDowncase(stringSubsequence(name, thestart, theend)), 1, stringSubsequence(name, theend, NULL_INTEGER))));
    }
  }
}

StringWrapper* stringCapitalizeComputation(Object* x, Object* start, Object* end) {
  { const char* name = NULL;
    int thestart = NULL_INTEGER;
    int theend = NULL_INTEGER;

    name = normalizeStringComputationArgs(x, start, end, false, thestart, theend);
    if (name == NULL) {
      return (NULL);
    }
    if ((thestart == 0) &&
        (theend == strlen(name))) {
      return (wrapString(stella::stringCapitalize(name)));
    }
    else {
      return (wrapString(stringConcatenate(stringSubsequence(name, 0, thestart), stella::stringCapitalize(stringSubsequence(name, thestart, theend)), 1, stringSubsequence(name, theend, NULL_INTEGER))));
    }
  }
}

StringWrapper* stringReplaceComputation(Object* x, Object* from, Object* to, Object* start, Object* end) {
  { const char* name = NULL;
    int thestart = NULL_INTEGER;
    int theend = NULL_INTEGER;

    name = normalizeStringComputationArgs(x, start, end, false, thestart, theend);
    if ((name == NULL) ||
        ((!stringP(from)) ||
         (!stringP(to)))) {
      return (NULL);
    }
    if ((thestart == 0) &&
        (theend == strlen(name))) {
      return (wrapString(replaceSubstrings(name, ((StringWrapper*)(to))->wrapperValue, ((StringWrapper*)(from))->wrapperValue)));
    }
    else {
      return (wrapString(stringConcatenate(stringSubsequence(name, 0, thestart), replaceSubstrings(stringSubsequence(name, thestart, theend), ((StringWrapper*)(to))->wrapperValue, ((StringWrapper*)(from))->wrapperValue), 1, stringSubsequence(name, theend, NULL_INTEGER))));
    }
  }
}

IntegerWrapper* stringCompareComputationHelper(Object* o1, Object* o2, Object* start1, Object* end1, Object* start2, Object* end2, boolean ignorecaseP) {
  { const char* name1 = NULL;
    int thestart1 = NULL_INTEGER;
    int theend1 = NULL_INTEGER;

    name1 = normalizeStringComputationArgs(o1, start1, end1, false, thestart1, theend1);
    if (name1 == NULL) {
      return (NULL);
    }
    { const char* name2 = NULL;
      int thestart2 = NULL_INTEGER;
      int theend2 = NULL_INTEGER;

      name2 = normalizeStringComputationArgs(o2, start2, end2, false, thestart2, theend2);
      if (name2 == NULL) {
        return (NULL);
      }
      if ((thestart1 > 0) ||
          (theend1 < strlen(name1))) {
        name1 = stringSubsequence(name1, thestart1, theend1);
      }
      if ((thestart2 > 0) ||
          (theend2 < strlen(name2))) {
        name2 = stringSubsequence(name2, thestart2, theend2);
      }
      return (wrapInteger(stella::stringCompare(name1, name2, !ignorecaseP)));
    }
  }
}

IntegerWrapper* stringCompareComputation(Object* o1, Object* o2, Object* start1, Object* end1, Object* start2, Object* end2) {
  return (stringCompareComputationHelper(o1, o2, start1, end1, start2, end2, false));
}

IntegerWrapper* stringCompareIgnoreCaseComputation(Object* o1, Object* o2, Object* start1, Object* end1, Object* start2, Object* end2) {
  return (stringCompareComputationHelper(o1, o2, start1, end1, start2, end2, true));
}

NumberWrapper* stringToNumberComputation(Object* x, Object* start, Object* end) {
  { const char* name = NULL;
    int thestart = NULL_INTEGER;
    int theend = NULL_INTEGER;

    name = normalizeStringComputationArgs(x, start, end, false, thestart, theend);
    if (name == NULL) {
      return (NULL);
    }
    if ((thestart > 0) ||
        (theend < strlen(name))) {
      name = stringSubsequence(name, thestart, theend);
    }
    try {
      return (wrapIntegerValue(parseLongInteger(name)));
    }
    catch (std::exception ) {
    }
    try {
      return (wrapFloat(parseFloat(name)));
    }
    catch (std::exception ) {
    }
    return (NULL);
  }
}

IntegerWrapper* lengthComputation(Object* x) {
  { Surrogate* testValue000 = safePrimaryType(x);

    if (subtypeOfStringP(testValue000)) {
      { Object* x000 = x;
        StringWrapper* x = ((StringWrapper*)(x000));

        return (wrapInteger(strlen((x->wrapperValue))));
      }
    }
    else if (subtypeOfP(testValue000, SGT_ARITHMETIC_LOGIC_SKOLEM)) {
      { Object* x001 = x;
        Skolem* x = ((Skolem*)(x001));

        if (enumeratedListP(x) ||
            enumeratedSetP(x)) {
          return (wrapInteger(x->definingProposition->arguments->length() - 1));
        }
        else if (logicalCollectionP(x)) {
          { stella::List* listvalue = assertedCollectionMembers(x, true);

            if (((boolean)(listvalue))) {
              return (wrapInteger(listvalue->length()));
            }
          }
        }
      }
    }
    else {
    }
  }
  return (NULL);
}

void helpStartupArithmetic1() {
  {
    SGT_ARITHMETIC_PL_KERNEL_KB_INTEGER_INTERVAL = ((Surrogate*)(internRigidSymbolWrtModule("INTEGER-INTERVAL", NULL, 1)));
    SYM_ARITHMETIC_PL_KERNEL_KB_INTERVAL_LOWER_BOUND = ((Symbol*)(internRigidSymbolWrtModule("INTERVAL-LOWER-BOUND", NULL, 0)));
    SYM_ARITHMETIC_PL_KERNEL_KB_INTERVAL_UPPER_BOUND = ((Symbol*)(internRigidSymbolWrtModule("INTERVAL-UPPER-BOUND", NULL, 0)));
    SGT_ARITHMETIC_PL_KERNEL_KB_INTERVAL_CACHE = ((Surrogate*)(internRigidSymbolWrtModule("INTERVAL-CACHE", NULL, 1)));
    SYM_ARITHMETIC_STELLA_HOME_CONTEXT = ((Symbol*)(internRigidSymbolWrtModule("HOME-CONTEXT", getStellaModule("/STELLA", true), 0)));
    SYM_ARITHMETIC_LOGIC_INTERVAL_MEMBER = ((Symbol*)(internRigidSymbolWrtModule("INTERVAL-MEMBER", getStellaModule("/LOGIC", true), 0)));
    SYM_ARITHMETIC_STELLA_LOWER_BOUND = ((Symbol*)(internRigidSymbolWrtModule("LOWER-BOUND", getStellaModule("/STELLA", true), 0)));
    SYM_ARITHMETIC_STELLA_UPPER_BOUND = ((Symbol*)(internRigidSymbolWrtModule("UPPER-BOUND", getStellaModule("/STELLA", true), 0)));
    SYM_ARITHMETIC_LOGIC_STRICT_LOWER_BOUNDp = ((Symbol*)(internRigidSymbolWrtModule("STRICT-LOWER-BOUND?", getStellaModule("/LOGIC", true), 0)));
    SYM_ARITHMETIC_LOGIC_STRICT_UPPER_BOUNDp = ((Symbol*)(internRigidSymbolWrtModule("STRICT-UPPER-BOUND?", getStellaModule("/LOGIC", true), 0)));
    SGT_ARITHMETIC_PL_KERNEL_KB_INTERVAL_CACHE_OF = ((Surrogate*)(internRigidSymbolWrtModule("INTERVAL-CACHE-OF", NULL, 1)));
    SGT_ARITHMETIC_PL_KERNEL_KB_INEQUALITY = ((Surrogate*)(internRigidSymbolWrtModule("INEQUALITY", NULL, 1)));
    SGT_ARITHMETIC_LOGIC_LOGIC_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("LOGIC-OBJECT", getStellaModule("/LOGIC", true), 1)));
    SGT_ARITHMETIC_LOGIC_SKOLEM = ((Surrogate*)(internRigidSymbolWrtModule("SKOLEM", getStellaModule("/LOGIC", true), 1)));
    SGT_ARITHMETIC_STELLA_INTEGER = ((Surrogate*)(internRigidSymbolWrtModule("INTEGER", getStellaModule("/STELLA", true), 1)));
    SGT_ARITHMETIC_PL_KERNEL_KB_g = ((Surrogate*)(internRigidSymbolWrtModule(">", NULL, 1)));
    SGT_ARITHMETIC_STELLA_NUMBER_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("NUMBER-WRAPPER", getStellaModule("/STELLA", true), 1)));
    SGT_ARITHMETIC_LOGIC_QUANTITY_LOGIC_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("QUANTITY-LOGIC-WRAPPER", getStellaModule("/LOGIC", true), 1)));
    SGT_ARITHMETIC_PL_KERNEL_KB_ge = ((Surrogate*)(internRigidSymbolWrtModule(">=", NULL, 1)));
    SGT_ARITHMETIC_PL_KERNEL_KB_l = ((Surrogate*)(internRigidSymbolWrtModule("<", NULL, 1)));
    SGT_ARITHMETIC_PL_KERNEL_KB_el = ((Surrogate*)(internRigidSymbolWrtModule("=<", NULL, 1)));
    KWD_ARITHMETIC_LOWER_BOUND = ((Keyword*)(internRigidSymbolWrtModule("LOWER-BOUND", NULL, 2)));
    KWD_ARITHMETIC_UPPER_BOUND = ((Keyword*)(internRigidSymbolWrtModule("UPPER-BOUND", NULL, 2)));
    SGT_ARITHMETIC_STELLA_e = ((Surrogate*)(internRigidSymbolWrtModule("=", getStellaModule("/STELLA", true), 1)));
    KWD_ARITHMETIC_TERMINAL_FAILURE = ((Keyword*)(internRigidSymbolWrtModule("TERMINAL-FAILURE", NULL, 2)));
    SGT_ARITHMETIC_STELLA_INTEGER_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("INTEGER-WRAPPER", getStellaModule("/STELLA", true), 1)));
    KWD_ARITHMETIC_FINAL_SUCCESS = ((Keyword*)(internRigidSymbolWrtModule("FINAL-SUCCESS", NULL, 2)));
    KWD_ARITHMETIC_FAILURE = ((Keyword*)(internRigidSymbolWrtModule("FAILURE", NULL, 2)));
    KWD_ARITHMETIC_ORIGINAL = ((Keyword*)(internRigidSymbolWrtModule("ORIGINAL", NULL, 2)));
    SYM_ARITHMETIC_STELLA_ITERATOR = ((Symbol*)(internRigidSymbolWrtModule("ITERATOR", getStellaModule("/STELLA", true), 0)));
    KWD_ARITHMETIC_CONTINUING_SUCCESS = ((Keyword*)(internRigidSymbolWrtModule("CONTINUING-SUCCESS", NULL, 2)));
    SYM_ARITHMETIC_PL_KERNEL_KB_STARTUP_ARITHMETIC = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-ARITHMETIC", NULL, 0)));
    SYM_ARITHMETIC_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
  }
}

void helpStartupArithmetic2() {
  {
    defineFunctionObject("ARITHMETIC-EQUAL-TEST", "(DEFUN (ARITHMETIC-EQUAL-TEST BOOLEAN) ((X NUMBER-WRAPPER) (Y NUMBER-WRAPPER)) :PUBLIC? TRUE)", ((cpp_function_code)(&arithmeticEqualTest)), NULL);
    defineFunctionObject("ARITHMETIC-LESS-TEST", "(DEFUN (ARITHMETIC-LESS-TEST BOOLEAN) ((X NUMBER-WRAPPER) (Y NUMBER-WRAPPER)) :PUBLIC? TRUE)", ((cpp_function_code)(&arithmeticLessTest)), NULL);
    defineFunctionObject("ARITHMETIC-GREATER-TEST", "(DEFUN (ARITHMETIC-GREATER-TEST BOOLEAN) ((X NUMBER-WRAPPER) (Y NUMBER-WRAPPER)) :PUBLIC? TRUE)", ((cpp_function_code)(&arithmeticGreaterTest)), NULL);
    defineFunctionObject("PLUS-COMPUTATION", "(DEFUN (PLUS-COMPUTATION NUMBER-WRAPPER) ((X NUMBER-WRAPPER) (Y NUMBER-WRAPPER)) :PUBLIC? TRUE)", ((cpp_function_code)(&plusComputation)), NULL);
    defineFunctionObject("MINUS-COMPUTATION", "(DEFUN (MINUS-COMPUTATION NUMBER-WRAPPER) ((X NUMBER-WRAPPER) (Y NUMBER-WRAPPER)) :PUBLIC? TRUE)", ((cpp_function_code)(&minusComputation)), NULL);
    defineFunctionObject("TIMES-COMPUTATION", "(DEFUN (TIMES-COMPUTATION NUMBER-WRAPPER) ((X NUMBER-WRAPPER) (Y NUMBER-WRAPPER)) :PUBLIC? TRUE)", ((cpp_function_code)(&timesComputation)), NULL);
    defineFunctionObject("DIVIDE-COMPUTATION", "(DEFUN (DIVIDE-COMPUTATION NUMBER-WRAPPER) ((X NUMBER-WRAPPER) (Y NUMBER-WRAPPER)) :PUBLIC? TRUE)", ((cpp_function_code)(&divideComputation)), NULL);
    defineFunctionObject("SQRT-COMPUTATION", "(DEFUN (SQRT-COMPUTATION NUMBER-WRAPPER) ((X NUMBER-WRAPPER)) :PUBLIC? TRUE)", ((cpp_function_code)(&sqrtComputation)), NULL);
    defineFunctionObject("NEGATE-COMPUTATION", "(DEFUN (NEGATE-COMPUTATION NUMBER-WRAPPER) ((X NUMBER-WRAPPER)) :PUBLIC? TRUE)", ((cpp_function_code)(&negateComputation)), NULL);
    defineFunctionObject("ABS-COMPUTATION", "(DEFUN (ABS-COMPUTATION NUMBER-WRAPPER) ((X NUMBER-WRAPPER)) :PUBLIC? TRUE)", ((cpp_function_code)(&absComputation)), NULL);
    defineFunctionObject("FLOOR-COMPUTATION", "(DEFUN (FLOOR-COMPUTATION INTEGER-WRAPPER) ((X NUMBER-WRAPPER)) :PUBLIC? TRUE)", ((cpp_function_code)(&floorComputation)), NULL);
    defineFunctionObject("CEILING-COMPUTATION", "(DEFUN (CEILING-COMPUTATION INTEGER-WRAPPER) ((X NUMBER-WRAPPER)) :PUBLIC? TRUE)", ((cpp_function_code)(&ceilingComputation)), NULL);
    defineFunctionObject("PLUS-CONSTRAINT", "(DEFUN (PLUS-CONSTRAINT OBJECT) ((MISSING-ARGUMENT INTEGER-WRAPPER) (X1 NUMBER-WRAPPER) (X2 NUMBER-WRAPPER) (X3 NUMBER-WRAPPER)))", ((cpp_function_code)(&plusConstraint)), NULL);
    defineFunctionObject("MINUS-CONSTRAINT", "(DEFUN (MINUS-CONSTRAINT OBJECT) ((MISSING-ARGUMENT INTEGER-WRAPPER) (X1 NUMBER-WRAPPER) (X2 NUMBER-WRAPPER) (X3 NUMBER-WRAPPER)))", ((cpp_function_code)(&minusConstraint)), NULL);
    defineFunctionObject("TIMES-CONSTRAINT", "(DEFUN (TIMES-CONSTRAINT OBJECT) ((MISSING-ARGUMENT INTEGER-WRAPPER) (X1 NUMBER-WRAPPER) (X2 NUMBER-WRAPPER) (X3 NUMBER-WRAPPER)))", ((cpp_function_code)(&timesConstraint)), NULL);
    defineFunctionObject("DIVIDE-CONSTRAINT", "(DEFUN (DIVIDE-CONSTRAINT OBJECT) ((MISSING-ARGUMENT INTEGER-WRAPPER) (X1 NUMBER-WRAPPER) (X2 NUMBER-WRAPPER) (X3 NUMBER-WRAPPER)))", ((cpp_function_code)(&divideConstraint)), NULL);
    defineFunctionObject("NEGATE-CONSTRAINT", "(DEFUN (NEGATE-CONSTRAINT OBJECT) ((MISSING-ARGUMENT INTEGER-WRAPPER) (X1 NUMBER-WRAPPER) (X2 NUMBER-WRAPPER)))", ((cpp_function_code)(&negateConstraint)), NULL);
    defineFunctionObject("SQRT-CONSTRAINT", "(DEFUN (SQRT-CONSTRAINT OBJECT) ((MISSING-ARGUMENT INTEGER-WRAPPER) (X1 NUMBER-WRAPPER) (X2 NUMBER-WRAPPER)))", ((cpp_function_code)(&sqrtConstraint)), NULL);
    defineFunctionObject("LOG-COMPUTATION", "(DEFUN (LOG-COMPUTATION FLOAT-WRAPPER) ((X NUMBER-WRAPPER)) :PUBLIC? TRUE)", ((cpp_function_code)(&logComputation)), NULL);
    defineFunctionObject("LOG10-COMPUTATION", "(DEFUN (LOG10-COMPUTATION FLOAT-WRAPPER) ((X NUMBER-WRAPPER)) :PUBLIC? TRUE)", ((cpp_function_code)(&log10Computation)), NULL);
    defineFunctionObject("EXP-COMPUTATION", "(DEFUN (EXP-COMPUTATION FLOAT-WRAPPER) ((X NUMBER-WRAPPER)) :PUBLIC? TRUE)", ((cpp_function_code)(&expComputation)), NULL);
    defineFunctionObject("EXPT-COMPUTATION", "(DEFUN (EXPT-COMPUTATION FLOAT-WRAPPER) ((X NUMBER-WRAPPER) (N NUMBER-WRAPPER)) :PUBLIC? TRUE)", ((cpp_function_code)(&exptComputation)), NULL);
    defineFunctionObject("LOG-CONSTRAINT", "(DEFUN (LOG-CONSTRAINT OBJECT) ((MISSING-ARGUMENT INTEGER-WRAPPER) (X NUMBER-WRAPPER) (LOG NUMBER-WRAPPER)))", ((cpp_function_code)(&logConstraint)), NULL);
    defineFunctionObject("LOG10-CONSTRAINT", "(DEFUN (LOG10-CONSTRAINT OBJECT) ((MISSING-ARGUMENT INTEGER-WRAPPER) (X NUMBER-WRAPPER) (LOG NUMBER-WRAPPER)))", ((cpp_function_code)(&log10Constraint)), NULL);
    defineFunctionObject("EXP-CONSTRAINT", "(DEFUN (EXP-CONSTRAINT OBJECT) ((MISSING-ARGUMENT INTEGER-WRAPPER) (X NUMBER-WRAPPER) (Y NUMBER-WRAPPER)))", ((cpp_function_code)(&expConstraint)), NULL);
    defineFunctionObject("PRINT-INTERVAL", "(DEFUN PRINT-INTERVAL ((STREAM NATIVE-OUTPUT-STREAM) (LOWER OBJECT) (STRICT-LOWER? BOOLEAN) (UPPER OBJECT) (STRICT-UPPER? BOOLEAN)))", ((cpp_function_code)(&printInterval)), NULL);
    defineFunctionObject("CREATE-INTERVAL-CACHE", "(DEFUN (CREATE-INTERVAL-CACHE INTERVAL-CACHE) ((INTERVALMEMBER LOGIC-OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&createIntervalCache)), NULL);
    defineFunctionObject("GET-INTERVAL-CACHE", "(DEFUN (GET-INTERVAL-CACHE INTERVAL-CACHE) ((SELF LOGIC-OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&getIntervalCache)), NULL);
    defineFunctionObject("SIGNAL-INTERVAL-CLASH", "(DEFUN SIGNAL-INTERVAL-CLASH ((INTERVAL INTERVAL-CACHE)))", ((cpp_function_code)(&signalIntervalClash)), NULL);
    defineFunctionObject("EVALUATE-ADJACENT-INEQUALITIES", "(DEFUN EVALUATE-ADJACENT-INEQUALITIES ((SELF LOGIC-OBJECT)))", ((cpp_function_code)(&evaluateAdjacentInequalities)), NULL);
    defineMethodObject("(DEFMETHOD (INTEGER-VALUED-MEMBER? BOOLEAN) ((INTERVAL INTERVAL-CACHE)))", wrapMethodCode(((cpp_method_code)(&IntervalCache::integerValuedMemberP))), NULL);
    defineMethodObject("(DEFMETHOD (INTEGER-LOWER-BOUND INTEGER-WRAPPER) ((INTERVAL INTERVAL-CACHE)))", wrapMethodCode(((cpp_method_code)(&IntervalCache::integerLowerBound))), NULL);
    defineMethodObject("(DEFMETHOD (INTEGER-UPPER-BOUND INTEGER-WRAPPER) ((INTERVAL INTERVAL-CACHE)))", wrapMethodCode(((cpp_method_code)(&IntervalCache::integerUpperBound))), NULL);
    defineMethodObject("(DEFMETHOD EVALUATE-TIGHTER-INTEGER-INTERVAL ((INTERVAL INTERVAL-CACHE)))", wrapMethodCode(((cpp_method_code)(&IntervalCache::evaluateTighterIntegerInterval))), NULL);
    defineMethodObject("(DEFMETHOD EVALUATE-TIGHTER-INTERVAL ((INTERVAL INTERVAL-CACHE)))", wrapMethodCode(((cpp_method_code)(&IntervalCache::evaluateTighterInterval))), NULL);
    defineMethodObject("(DEFMETHOD PROPAGATE-INEQUALITY-TO-INTERVAL-CACHE ((SELF INTERVAL-CACHE) (VALUE OBJECT) (OPERATOR SURROGATE)))", wrapMethodCode(((cpp_method_code)(&IntervalCache::propagateInequalityToIntervalCache))), NULL);
    defineFunctionObject("INVERSE-INEQUALITY-OPERATOR", "(DEFUN (INVERSE-INEQUALITY-OPERATOR SURROGATE) ((OPERATOR SURROGATE)))", ((cpp_function_code)(&inverseInequalityOperator)), NULL);
    defineFunctionObject("UNIFY-INTERVAL-CACHES", "(DEFUN UNIFY-INTERVAL-CACHES ((CACHE1 INTERVAL-CACHE) (CACHE2 INTERVAL-CACHE) (OPERATOR SURROGATE)))", ((cpp_function_code)(&unifyIntervalCaches)), NULL);
    defineFunctionObject("ACCESS-INTERVAL-BOUNDS", "(DEFUN (ACCESS-INTERVAL-BOUNDS OBJECT BOOLEAN) ((X OBJECT) (LOWERORUPPER KEYWORD)))", ((cpp_function_code)(&accessIntervalBounds)), NULL);
    defineFunctionObject("ACCESS-INTERVAL-CACHE-BOUNDS", "(DEFUN (ACCESS-INTERVAL-CACHE-BOUNDS OBJECT BOOLEAN) ((INTERVALCACHE INTERVAL-CACHE) (LOWERORUPPER KEYWORD)))", ((cpp_function_code)(&accessIntervalCacheBounds)), NULL);
    defineFunctionObject("COMPARE-INTERVAL-BOUNDS?", "(DEFUN (COMPARE-INTERVAL-BOUNDS? BOOLEAN) ((RELATION SURROGATE) (X OBJECT) (Y OBJECT)))", ((cpp_function_code)(&compareIntervalBoundsP)), NULL);
    defineFunctionObject("NULL-NUMBER?", "(DEFUN (NULL-NUMBER? BOOLEAN) ((SELF NUMBER-WRAPPER)) :PUBLIC? TRUE)", ((cpp_function_code)(&nullNumberP)), NULL);
    defineFunctionObject("NULL-LITERAL-WRAPPER?", "(DEFUN (NULL-LITERAL-WRAPPER? BOOLEAN) ((SELF OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&nullLiteralWrapperP)), NULL);
    defineFunctionObject("SATISFIES-INTERVAL-BOUNDS?", "(DEFUN (SATISFIES-INTERVAL-BOUNDS? BOOLEAN) ((OBJECT OBJECT) (VALUE OBJECT)))", ((cpp_function_code)(&satisfiesIntervalBoundsP)), NULL);
    defineFunctionObject("LESS-SPECIALIST-HELPER", "(DEFUN (LESS-SPECIALIST-HELPER KEYWORD) ((FRAME CONTROL-FRAME) (RELATION SURROGATE) (XARG OBJECT) (YARG OBJECT)))", ((cpp_function_code)(&lessSpecialistHelper)), NULL);
    defineFunctionObject("INEQUALITY-SPECIALIST", "(DEFUN (INEQUALITY-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&inequalitySpecialist)), NULL);
    defineFunctionObject("INEQUALITY-EVALUATOR", "(DEFUN INEQUALITY-EVALUATOR ((SELF PROPOSITION)))", ((cpp_function_code)(&inequalityEvaluator)), NULL);
    defineFunctionObject("STRING-CONCATENATE-COMPUTATION", "(DEFUN (STRING-CONCATENATE-COMPUTATION STRING-WRAPPER) ((X OBJECT) (YARGS CONS)))", ((cpp_function_code)(((StringWrapper*  (*) (Object*, Cons*))(&stringConcatenateComputation)))), NULL);
    defineFunctionObject("SUBSEQUENCE-SPECIALIST", "(DEFUN (SUBSEQUENCE-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&subsequenceSpecialist)), NULL);
    defineFunctionObject("NORMALIZE-STRING-COMPUTATION-ARGS", "(DEFUN (NORMALIZE-STRING-COMPUTATION-ARGS STRING INTEGER INTEGER) ((X OBJECT) (START OBJECT) (END OBJECT) (COERCE? BOOLEAN)))", ((cpp_function_code)(&normalizeStringComputationArgs)), NULL);
    defineFunctionObject("STRING-MATCH-COMPUTATION-HELPER", "(DEFUN (STRING-MATCH-COMPUTATION-HELPER INTEGER-WRAPPER) ((PATTERN OBJECT) (X OBJECT) (START OBJECT) (END OBJECT) (IGNORE-CASE? BOOLEAN)))", ((cpp_function_code)(((IntegerWrapper*  (*) (Object*, Object*, Object*, Object*, boolean))(&stringMatchComputationHelper)))), NULL);
    defineFunctionObject("STRING-MATCH-COMPUTATION", "(DEFUN (STRING-MATCH-COMPUTATION INTEGER-WRAPPER) ((PATTERN OBJECT) (X OBJECT) (START OBJECT) (END OBJECT)))", ((cpp_function_code)(((IntegerWrapper*  (*) (Object*, Object*, Object*, Object*))(&stringMatchComputation)))), NULL);
    defineFunctionObject("STRING-MATCH-IGNORE-CASE-COMPUTATION", "(DEFUN (STRING-MATCH-IGNORE-CASE-COMPUTATION INTEGER-WRAPPER) ((PATTERN OBJECT) (X OBJECT) (START OBJECT) (END OBJECT)))", ((cpp_function_code)(((IntegerWrapper*  (*) (Object*, Object*, Object*, Object*))(&stringMatchIgnoreCaseComputation)))), NULL);
    defineFunctionObject("STRING-UPCASE-COMPUTATION", "(DEFUN (STRING-UPCASE-COMPUTATION STRING-WRAPPER) ((X OBJECT) (START OBJECT) (END OBJECT)))", ((cpp_function_code)(((StringWrapper*  (*) (Object*, Object*, Object*))(&stringUpcaseComputation)))), NULL);
    defineFunctionObject("STRING-DOWNCASE-COMPUTATION", "(DEFUN (STRING-DOWNCASE-COMPUTATION STRING-WRAPPER) ((X OBJECT) (START OBJECT) (END OBJECT)))", ((cpp_function_code)(((StringWrapper*  (*) (Object*, Object*, Object*))(&stringDowncaseComputation)))), NULL);
    defineFunctionObject("STRING-CAPITALIZE-COMPUTATION", "(DEFUN (STRING-CAPITALIZE-COMPUTATION STRING-WRAPPER) ((X OBJECT) (START OBJECT) (END OBJECT)))", ((cpp_function_code)(((StringWrapper*  (*) (Object*, Object*, Object*))(&stringCapitalizeComputation)))), NULL);
    defineFunctionObject("STRING-REPLACE-COMPUTATION", "(DEFUN (STRING-REPLACE-COMPUTATION STRING-WRAPPER) ((X OBJECT) (FROM OBJECT) (TO OBJECT) (START OBJECT) (END OBJECT)))", ((cpp_function_code)(((StringWrapper*  (*) (Object*, Object*, Object*, Object*, Object*))(&stringReplaceComputation)))), NULL);
    defineFunctionObject("STRING-COMPARE-COMPUTATION-HELPER", "(DEFUN (STRING-COMPARE-COMPUTATION-HELPER INTEGER-WRAPPER) ((O1 OBJECT) (O2 OBJECT) (START1 OBJECT) (END1 OBJECT) (START2 OBJECT) (END2 OBJECT) (IGNORECASE? BOOLEAN)))", ((cpp_function_code)(((IntegerWrapper*  (*) (Object*, Object*, Object*, Object*, Object*, Object*, boolean))(&stringCompareComputationHelper)))), NULL);
    defineFunctionObject("STRING-COMPARE-COMPUTATION", "(DEFUN (STRING-COMPARE-COMPUTATION INTEGER-WRAPPER) ((O1 OBJECT) (O2 OBJECT) (START1 OBJECT) (END1 OBJECT) (START2 OBJECT) (END2 OBJECT)))", ((cpp_function_code)(((IntegerWrapper*  (*) (Object*, Object*, Object*, Object*, Object*, Object*))(&stringCompareComputation)))), NULL);
    defineFunctionObject("STRING-COMPARE-IGNORE-CASE-COMPUTATION", "(DEFUN (STRING-COMPARE-IGNORE-CASE-COMPUTATION INTEGER-WRAPPER) ((O1 OBJECT) (O2 OBJECT) (START1 OBJECT) (END1 OBJECT) (START2 OBJECT) (END2 OBJECT)))", ((cpp_function_code)(((IntegerWrapper*  (*) (Object*, Object*, Object*, Object*, Object*, Object*))(&stringCompareIgnoreCaseComputation)))), NULL);
  }
}

void startupArithmetic() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/PL-KERNEL-KB", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupArithmetic1();
    }
    if (currentStartupTimePhaseP(5)) {
      { stella::Class* clasS = defineClassFromStringifiedSource("INTEGER-INTERVAL", "(DEFCLASS INTEGER-INTERVAL (THING) :DOCUMENTATION \"An interval of integers\" :SLOTS ((INTERVAL-LOWER-BOUND :TYPE INTEGER) (INTERVAL-UPPER-BOUND :TYPE INTEGER)))");

        clasS->classConstructorCode = ((cpp_function_code)(&newIntegerInterval));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessIntegerIntervalSlotValue));
      }
      { stella::Class* clasS = defineClassFromStringifiedSource("INTERVAL-CACHE", "(DEFCLASS INTERVAL-CACHE (THING) :PUBLIC? TRUE :PUBLIC-SLOTS ((HOME-CONTEXT :TYPE CONTEXT) (INTERVAL-MEMBER :TYPE LOGIC-OBJECT) (LOWER-BOUND :TYPE OBJECT) (UPPER-BOUND :TYPE OBJECT) (STRICT-LOWER-BOUND? :TYPE BOOLEAN) (STRICT-UPPER-BOUND? :TYPE BOOLEAN)) :PRINT-FORM (PROGN (PRINT-STREAM STREAM \"|cache-of: \" (INTERVAL-MEMBER SELF) \" \") (PRINT-INTERVAL STREAM (LOWER-BOUND SELF) (STRICT-LOWER-BOUND? SELF) (UPPER-BOUND SELF) (STRICT-UPPER-BOUND? SELF)) (PRINT-STREAM STREAM \"|\")))");

        clasS->classConstructorCode = ((cpp_function_code)(&newIntervalCache));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessIntervalCacheSlotValue));
      }
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupArithmetic2();
      defineFunctionObject("STRING-TO-NUMBER-COMPUTATION", "(DEFUN (STRING-TO-NUMBER-COMPUTATION NUMBER-WRAPPER) ((X OBJECT) (START OBJECT) (END OBJECT)))", ((cpp_function_code)(((NumberWrapper*  (*) (Object*, Object*, Object*))(&stringToNumberComputation)))), NULL);
      defineFunctionObject("LENGTH-COMPUTATION", "(DEFUN (LENGTH-COMPUTATION INTEGER-WRAPPER) ((X OBJECT)))", ((cpp_function_code)(&lengthComputation)), NULL);
      defineFunctionObject("STARTUP-ARITHMETIC", "(DEFUN STARTUP-ARITHMETIC () :PUBLIC? TRUE)", ((cpp_function_code)(&startupArithmetic)), NULL);
      { MethodSlot* function = lookupFunction(SYM_ARITHMETIC_PL_KERNEL_KB_STARTUP_ARITHMETIC);

        setDynamicSlotValue(function->dynamicSlots, SYM_ARITHMETIC_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupArithmetic"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("PL-KERNEL")))));
    }
  }
}

Surrogate* SGT_ARITHMETIC_PL_KERNEL_KB_INTEGER_INTERVAL = NULL;

Symbol* SYM_ARITHMETIC_PL_KERNEL_KB_INTERVAL_LOWER_BOUND = NULL;

Symbol* SYM_ARITHMETIC_PL_KERNEL_KB_INTERVAL_UPPER_BOUND = NULL;

Surrogate* SGT_ARITHMETIC_PL_KERNEL_KB_INTERVAL_CACHE = NULL;

Symbol* SYM_ARITHMETIC_STELLA_HOME_CONTEXT = NULL;

Symbol* SYM_ARITHMETIC_LOGIC_INTERVAL_MEMBER = NULL;

Symbol* SYM_ARITHMETIC_STELLA_LOWER_BOUND = NULL;

Symbol* SYM_ARITHMETIC_STELLA_UPPER_BOUND = NULL;

Symbol* SYM_ARITHMETIC_LOGIC_STRICT_LOWER_BOUNDp = NULL;

Symbol* SYM_ARITHMETIC_LOGIC_STRICT_UPPER_BOUNDp = NULL;

Surrogate* SGT_ARITHMETIC_PL_KERNEL_KB_INTERVAL_CACHE_OF = NULL;

Surrogate* SGT_ARITHMETIC_PL_KERNEL_KB_INEQUALITY = NULL;

Surrogate* SGT_ARITHMETIC_LOGIC_LOGIC_OBJECT = NULL;

Surrogate* SGT_ARITHMETIC_LOGIC_SKOLEM = NULL;

Surrogate* SGT_ARITHMETIC_STELLA_INTEGER = NULL;

Surrogate* SGT_ARITHMETIC_PL_KERNEL_KB_g = NULL;

Surrogate* SGT_ARITHMETIC_STELLA_NUMBER_WRAPPER = NULL;

Surrogate* SGT_ARITHMETIC_LOGIC_QUANTITY_LOGIC_WRAPPER = NULL;

Surrogate* SGT_ARITHMETIC_PL_KERNEL_KB_ge = NULL;

Surrogate* SGT_ARITHMETIC_PL_KERNEL_KB_l = NULL;

Surrogate* SGT_ARITHMETIC_PL_KERNEL_KB_el = NULL;

Keyword* KWD_ARITHMETIC_LOWER_BOUND = NULL;

Keyword* KWD_ARITHMETIC_UPPER_BOUND = NULL;

Surrogate* SGT_ARITHMETIC_STELLA_e = NULL;

Keyword* KWD_ARITHMETIC_TERMINAL_FAILURE = NULL;

Surrogate* SGT_ARITHMETIC_STELLA_INTEGER_WRAPPER = NULL;

Keyword* KWD_ARITHMETIC_FINAL_SUCCESS = NULL;

Keyword* KWD_ARITHMETIC_FAILURE = NULL;

Keyword* KWD_ARITHMETIC_ORIGINAL = NULL;

Symbol* SYM_ARITHMETIC_STELLA_ITERATOR = NULL;

Keyword* KWD_ARITHMETIC_CONTINUING_SUCCESS = NULL;

Symbol* SYM_ARITHMETIC_PL_KERNEL_KB_STARTUP_ARITHMETIC = NULL;

Symbol* SYM_ARITHMETIC_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace pl_kernel_kb
