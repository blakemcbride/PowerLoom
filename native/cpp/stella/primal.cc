//  -*- Mode: C++ -*-

// primal.cc

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

// A float approximation of the mathematical constant pi.
double PI = 3.141592653589793;

int NULL_INTEGER = std::numeric_limits<int>::min();

short int NULL_SHORT_INTEGER = std::numeric_limits<short int>::min();

long long int NULL_LONG_INTEGER = std::numeric_limits<long long int>::min();

unsigned short int NULL_UNSIGNED_SHORT_INTEGER = std::numeric_limits<unsigned short int>::min();

unsigned long int NULL_UNSIGNED_LONG_INTEGER = std::numeric_limits<unsigned long long int>::min();

double NULL_FLOAT = std::numeric_limits<double>::infinity() != 0 ?
                    -std::numeric_limits<double>::infinity() :
                    // work around a problem in g++ 3.2.2 where infinity()==0:
                    NULL_INTEGER / (double)ceiling(-0.42);

float NULL_SINGLE_FLOAT = -std::numeric_limits<float>::infinity();

double NULL_DOUBLE_FLOAT = -std::numeric_limits<double>::infinity();

char NULL_CHARACTER = '\0';

char NULL_BYTE = 255;

char NULL_OCTET = 255;

const char* lispNullArraySymbolString(int rank) {
  switch (rank) {
    case 1: 
      return ("STELLA::NULL-1D-ARRAY");
    case 2: 
      return ("STELLA::NULL-2D-ARRAY");
    case 3: 
      return ("STELLA::NULL-3D-ARRAY");
    case 4: 
      return ("STELLA::NULL-4D-ARRAY");
    case 5: 
      return ("STELLA::NULL-5D-ARRAY");
    default:
      return ("STELLA::NULL");
  }
}

int MOST_POSITIVE_INTEGER = std::numeric_limits<int>::max();

int MOST_NEGATIVE_INTEGER = NULL_INTEGER;

long long int MOST_POSITIVE_LONG_INTEGER = std::numeric_limits<long long int>::max();

long long int MOST_NEGATIVE_LONG_INTEGER = NULL_LONG_INTEGER;

double MOST_POSITIVE_FLOAT = std::numeric_limits<double>::max();

double MOST_NEGATIVE_FLOAT = 0 - MOST_POSITIVE_FLOAT;

double LEAST_POSITIVE_FLOAT = std::numeric_limits<double>::min();

double LEAST_NEGATIVE_FLOAT = NULL_FLOAT;

void printNumericConstants() {
  std::cout << "MOST-POSITIVE-INTEGER:             " << MOST_POSITIVE_INTEGER << std::endl << "MOST-NEGATIVE-INTEGER:            " << MOST_NEGATIVE_INTEGER << std::endl << "NULL-INTEGER:                     " << NULL_INTEGER << std::endl << "MOST-POSITIVE-LONG-INTEGER:        " << MOST_POSITIVE_LONG_INTEGER << std::endl << "MOST-NEGATIVE-LONG-INTEGER:       " << MOST_NEGATIVE_LONG_INTEGER << std::endl << "NULL-LONG-INTEGER:                " << NULL_LONG_INTEGER << std::endl << "MOST-POSITIVE-FLOAT:               " << MOST_POSITIVE_FLOAT << std::endl << "MOST-NEGATIVE-FLOAT:              " << MOST_NEGATIVE_FLOAT << std::endl << "LEAST-POSITIVE-FLOAT:              " << LEAST_POSITIVE_FLOAT << std::endl << "LEAST-NEGATIVE-FLOAT:             " << LEAST_NEGATIVE_FLOAT << std::endl << "NULL-FLOAT:                       " << NULL_FLOAT << std::endl << "*INTEGER-MSB-MASK*:                " << oINTEGER_MSB_MASKo << std::endl << "*INTEGER-UNSIGNED-BITS-MASK*:      " << oINTEGER_UNSIGNED_BITS_MASKo << std::endl << "*LONG-INTEGER-MSB-MASK*:           " << oLONG_INTEGER_MSB_MASKo << std::endl << "*LONG-INTEGER-UNSIGNED-BITS-MASK*: " << oLONG_INTEGER_UNSIGNED_BITS_MASKo << std::endl << "LONG-INTEGER-BIT-WIDTH:            " << LONG_INTEGER_BIT_WIDTH << std::endl << "il(MOST-POSITIVE-INTEGER):         " << integerLength(((long long int)(MOST_POSITIVE_INTEGER))) << std::endl << "il(MOST-POSITIVE-LONG-INTEGER):    " << integerLength(MOST_POSITIVE_LONG_INTEGER) << std::endl << "il(MOST-NEGATIVE-INTEGER):         " << integerLength(((long long int)(MOST_NEGATIVE_INTEGER))) << std::endl << "il(MOST-NEGATIVE-LONG-INTEGER):    " << integerLength(MOST_NEGATIVE_LONG_INTEGER) << std::endl;
}

boolean eqlP(Object* x, Object* y) {
  // Return true if `x' and `y' are `eq?' or equivalent literals
  // such as strings that also might be wrapped in non-identical wrappers.  For
  // the case where `x' or `y' are plain literals such as strings or integers, the
  // STELLA translator substitutes the equality test appropriate for the particular
  // target language and does not actually call this function.  For cases where
  // `x' or `y' are known to be of type STANDARD-OBJECT, the STELLA translator
  // substitutes the faster `eq?' test inline.
  return (((!((boolean)(x))) ? (!((boolean)(y))) : ((x == y) ||
      x->objectEqlP(y))));
}

boolean equalP(Object* x, Object* y) {
  // Return true if `x' and `y' are `eql?' or considered equal
  // by a user-defined `object-equal?' method.  This implements a fully extensible
  // equality test similar to Java's `equals' method.  Note that writers of custom
  // `object-equal?' methods must also implement a corresponding `equal-hash-code'
  // method.
  return (((!((boolean)(x))) ? (!((boolean)(y))) : ((x == y) ||
      x->objectEqualP(y))));
}

boolean Object::objectEqualP(Object* y) {
  // Return true if `x' and `y' are `eq?'.
  { Object* x = this;

    return (x == y);
  }
}

boolean Wrapper::objectEqualP(Object* y) {
  // Return true if `x' and `y' are literal wrappers whose
  // literals are considered `eql?'.
  { Wrapper* x = this;

    return (x->objectEqlP(y));
  }
}

boolean integerZeroP(int x) {
  // Return true if `x' is 0.
  return ((!x));
}

boolean longIntegerZeroP(long long int x) {
  // Return true if `x' is 0.
  return ((!x));
}

boolean integerPlusP(int x) {
  // Return true if `x' is greater than 0.
  return ((x > 0));
}

boolean longIntegerPlusP(long long int x) {
  // Return true if `x' is greater than 0.
  return ((x > 0));
}

boolean integerEvenP(int x) {
  // Return true if `x' is an even number.
  return (!(x % 2));
}

boolean longIntegerEvenP(long long int x) {
  // Return true if `x' is an even number.
  return (!(x % 2));
}

boolean integerOddP(int x) {
  // Return true if `x' is an odd number.
  return ((x % 2));
}

boolean longIntegerOddP(long long int x) {
  // Return true if `x' is an odd number.
  return ((x % 2));
}

int integerDiv(int x, int y) {
  // Return the integer quotient from dividing `x' by `y'.
  return ((x / y));
}

long long int longIntegerDiv(long long int x, long long int y) {
  // Return the integer quotient from dividing `x' by `y'.
  return ((x / y));
}

int integerRem(int x, int y) {
  // Return the remainder from dividing `x' by `y'.  The
  // sign of the result is always the same as the sign of `x'.  This has slightly
  // different behavior than the `mod' function, and has less overhead in C++ and
  // Java, which don't have direct support for a true modulus function.
  return ((x % y));
}

long long int longIntegerRem(long long int x, long long int y) {
  // Return the remainder from dividing `x' by `y'.  The
  // sign of the result is always the same as the sign of `x'.  This has slightly
  // different behavior than the `mod' function, and has less overhead in C++ and
  // Java, which don't have direct support for a true modulus function.
  return ((x % y));
}

double frem(double x, double y) {
  // Return the floating point remainder from dividing `x' by `y'.  The
  // sign of the result is always the same as the sign of `x'.  This has slightly
  // different behavior than the `mod' function, and has less overhead in C++ and
  // Java, which don't have direct support for a true modulus function.
  return (fmod(x, y));
}

int integerMod(int x, int modulus) {
  // True modulus.  Return the result of `x' mod `modulo'.
  // Note: In C++ and Java, `mod' has more overhead than the similar
  // function `rem'.  The  answers returned by `mod' and `rem' are only
  // different when the signs of `x' and `modulo' are different.
  { int remainder = (x % modulus);

    if (remainder > 0) {
      if (modulus < 0) {
        remainder = modulus + remainder;
      }
    }
    else if (remainder < 0) {
      if (modulus > 0) {
        remainder = modulus + remainder;
      }
    }
    return (remainder);
  }
}

long long int longIntegerMod(long long int x, long long int modulus) {
  // True modulus.  Return the result of `x' mod `modulo'.
  // Note: In C++ and Java, `mod' has more overhead than the similar
  // function `rem'.  The  answers returned by `mod' and `rem' are only
  // different when the signs of `x' and `modulo' are different.
  { long long int remainder = (x % modulus);

    if (remainder > 0) {
      if (modulus < 0) {
        remainder = modulus + remainder;
      }
    }
    else if (remainder < 0) {
      if (modulus > 0) {
        remainder = modulus + remainder;
      }
    }
    return (remainder);
  }
}

double fmod(double x, double modulus) {
  // True modulus for floats.  Return the result of `x' mod `modulo'.
  // Note: In C++ and Java, `mod' has more overhead than the similar
  // function `rem'.  The  answers returned by `mod' and `rem' are only
  // different when the signs of `x' and `modulo' are different.
  { double remainder = fmod(x, modulus);

    if (remainder > 0.0) {
      if (modulus < 0.0) {
        remainder = modulus + remainder;
      }
    }
    else if (remainder < 0.0) {
      if (modulus > 0.0) {
        remainder = modulus + remainder;
      }
    }
    return (remainder);
  }
}

long long int gcd(long long int x, long long int y) {
  // Return the greatest common divisor of `x' and `y'.
  if (x < 0) {
    x = 0 - x;
  }
  if (y < 0) {
    y = 0 - y;
  }
  { long long int temp = 0l;

    while (!(y == 0)) {
      temp = (x % y);
      x = y;
      y = temp;
    }
    return (x);
  }
}

boolean regularIntegerValuedP(long long int x) {
  // Return `true' if `x' can be represented by a regular integer.
  return ((x >= NULL_INTEGER) &&
      (x <= MOST_POSITIVE_INTEGER));
}

boolean integerValuedP(double x) {
  // Returns `true' if `x' is the floating point representation of an integer.
  return (x == ::floor(x));
}

Cons* floatToBase60(double x, boolean allIntegersP) {
  // Returns a cons of `x' in a base-60 form.  That means
  // the first value will be the integer part of `x', the next value
  // the iteger value of the fraction part of `x' times 60 and the
  // third value the fraction part of `x' time 3600.  If `all-integers?'
  // is `true', then the last value will be rounded to an integer.
  // This can be used to convert from decimal degree values to Degree-Minute-Second
  // or from decimal hours to Hour-Minute-Second format.
  { int degree = stella::floor(x);
    int minute = stella::floor((x - degree) * 60.0);
    double fsecond = ((x * 3600.0) - (degree * 3600.0)) - (minute * 60.0);

    if (allIntegersP) {
      return (consList(3, wrapInteger(degree), wrapInteger(minute), wrapInteger(stella::round(fsecond))));
    }
    else {
      return (consList(3, wrapInteger(degree), wrapInteger(minute), wrapFloat(fsecond)));
    }
  }
}

double base60ToFloat(Cons* l) {
  // Converts (x y z) into a float.  The return value
  // is x + y/60 + z/3600.
  // This can be used to convert from Degree-Minute-Second to decimal degrees
  // or from Hour-Minute-Second format to decimal hours.
  { NumberWrapper* dvalue = ((NumberWrapper*)(l->value));
    NumberWrapper* mvalue = ((NumberWrapper*)(l->rest->value));
    NumberWrapper* svalue = ((NumberWrapper*)(l->rest->rest->value));
    double d = 0.0;

    { Surrogate* testValue000 = safePrimaryType(dvalue);

      if (subtypeOfFloatP(testValue000)) {
        { NumberWrapper* dvalue000 = dvalue;
          FloatWrapper* dvalue = ((FloatWrapper*)(dvalue000));

          d = dvalue->wrapperValue;
        }
      }
      else if (subtypeOfIntegerP(testValue000)) {
        { NumberWrapper* dvalue001 = dvalue;
          IntegerWrapper* dvalue = ((IntegerWrapper*)(dvalue001));

          d = dvalue->numberWrapperToFloat();
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
    { Surrogate* testValue001 = safePrimaryType(mvalue);

      if (subtypeOfFloatP(testValue001)) {
        { NumberWrapper* mvalue000 = mvalue;
          FloatWrapper* mvalue = ((FloatWrapper*)(mvalue000));

          d = d + (mvalue->wrapperValue / 60.0);
        }
      }
      else if (subtypeOfIntegerP(testValue001)) {
        { NumberWrapper* mvalue001 = mvalue;
          IntegerWrapper* mvalue = ((IntegerWrapper*)(mvalue001));

          d = d + (mvalue->wrapperValue / 60.0);
        }
      }
      else {
        { OutputStringStream* stream001 = newOutputStringStream();

          *(stream001->nativeStream) << "`" << testValue001 << "'" << " is not a valid case option";
          throw *newStellaException(stream001->theStringReader());
        }
      }
    }
    { Surrogate* testValue002 = safePrimaryType(svalue);

      if (subtypeOfFloatP(testValue002)) {
        { NumberWrapper* svalue000 = svalue;
          FloatWrapper* svalue = ((FloatWrapper*)(svalue000));

          d = d + (svalue->wrapperValue / 3600.0);
        }
      }
      else if (subtypeOfIntegerP(testValue002)) {
        { NumberWrapper* svalue001 = svalue;
          IntegerWrapper* svalue = ((IntegerWrapper*)(svalue001));

          d = d + (svalue->wrapperValue / 3600.0);
        }
      }
      else {
        { OutputStringStream* stream002 = newOutputStringStream();

          *(stream002->nativeStream) << "`" << testValue002 << "'" << " is not a valid case option";
          throw *newStellaException(stream002->theStringReader());
        }
      }
    }
    return (d);
  }
}

int random(int n) {
  // Generate a random integer in the interval [0..n-1].
  // The random number generator is seeded based on the current time every
  // time STELLA starts up; however, your mileage may vary depending on
  // the native language implementation.
  { int rnum = ::random() % n;

    return (rnum);
  }
}

void seedRandomNumberGenerator() {
  // Seeds the random number generator based on the current time.
  ::srandom(time(NULL));;
}

void seedRandomNumberGenerator2() {
  // Seeds the random number generator based on the current time and /dev/urandom if it is available.
  { boolean dummy1;

    { long long int seed = time(NULL);
      long long int mask = 281474976710655l;

      { InputFileStream* in = NULL;

        try {
          in = openInputFile("/dev/urandom", 2, KWD_PRIMAL_IF_NOT_EXISTS, KWD_PRIMAL_ABORT);
          if (((boolean)(in))) {
            { int i = NULL_INTEGER;
              int iter000 = 1;
              int upperBound000 = 8;

              for  (; iter000 <= upperBound000; 
                    iter000 = iter000 + 1) {
                i = iter000;
                i = i;
                seed = (((seed ^ (((long long int)((int)(unsigned char) (readCharacter(in, dummy1))))))) << 8);
              }
            }
            seed = (seed & mask);
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
      ::srandom((unsigned int)seed);;
    }
  }
}

double sqrt(double n) {
  // Return the square root of `n'.
  return (::sqrt(n));
}

double cos(double n) {
  // Return the cosine of `n' radians.
  return (::cos(n));
}

double sin(double n) {
  // Return the sine of `n' radians.
  return (::sin(n));
}

double tan(double n) {
  // Return the tangent of `n' radians.
  return (::tan(n));
}

double acos(double n) {
  // Return the arccosine of `n' in radians.
  return (::acos(n));
}

double asin(double n) {
  // Return the arcsine of `n' in radians.
  return (::asin(n));
}

double atan(double n) {
  // Return the arc tangent of `n' in radians.
  return (::atan(n));
}

double atan2(double x, double y) {
  // Return the arc tangent of `x' / `y' in radians.
  return (::atan2(x,y));
}

// 1 / (log 2) Reciprocal of the Log base e of 2.
// Used for log 2 conversions.
double RECIPROCAL_NL2 = NULL_FLOAT;

// 1 / (log 10) Reciprocal of the Log base e of 10.
// Used for log 10 conversions.
double RECIPROCAL_NL10 = NULL_FLOAT;

double log(double n) {
  // Return the natural logarithm (base e) of `n'.
  return (::log(n));
}

double log2(double n) {
  // Return the logarithm (base 2) of `n'.
  return (::log(n) * RECIPROCAL_NL2);
}

double log10(double n) {
  // Return the logarithm (base 10) of `n'.
  return (::log(n) * RECIPROCAL_NL10);
}

double exp(double n) {
  // Return the e to the power `n'.
  return (::exp(n));
}

double expt(double x, double y) {
  // Return `x' ^ `y'.
  return (::pow(x,y));
}

int integerMin(int x, int y) {
  // Return the minimum of `x' and `y'.  If either is NULL, return the other.
  return (((x > y) ? (((y == NULL_INTEGER) ? x : y)) : (((x == NULL_INTEGER) ? y : x))));
}

long long int longIntegerMin(long long int x, long long int y) {
  // Return the minimum of `x' and `y'.  If either is NULL, return the other.
  return (((x > y) ? (((y == NULL_LONG_INTEGER) ? x : y)) : (((x == NULL_LONG_INTEGER) ? y : x))));
}

double floatMin(double x, double y) {
  // Return the minimum of `x' and `y'.  If either is NULL, return the other.
  return (((x > y) ? (((y == NULL_FLOAT) ? x : y)) : (((x == NULL_FLOAT) ? y : x))));
}

NumberWrapper* NumberWrapper::min(NumberWrapper* y) {
  // Return the minimum of `x' and `y'.  If `y' is NULL, return `x'.
  { NumberWrapper* x = this;

    { Surrogate* testValue000 = safePrimaryType(x);

      if (subtypeOfIntegerP(testValue000)) {
        { NumberWrapper* x000 = x;
          IntegerWrapper* x = ((IntegerWrapper*)(x000));

          { Surrogate* testValue001 = safePrimaryType(y);

            if (subtypeOfIntegerP(testValue001)) {
              { NumberWrapper* y000 = y;
                IntegerWrapper* y = ((IntegerWrapper*)(y000));

                if ((!((boolean)(y))) ||
                    (x->wrapperValue <= y->wrapperValue)) {
                  return (x);
                }
                else {
                  return (y);
                }
              }
            }
            else if (subtypeOfLongIntegerP(testValue001)) {
              { NumberWrapper* y001 = y;
                LongIntegerWrapper* y = ((LongIntegerWrapper*)(y001));

                if ((!((boolean)(y))) ||
                    (x->wrapperValue <= y->wrapperValue)) {
                  return (x);
                }
                else {
                  return (y);
                }
              }
            }
            else if (subtypeOfFloatP(testValue001)) {
              { NumberWrapper* y002 = y;
                FloatWrapper* y = ((FloatWrapper*)(y002));

                if ((!((boolean)(y))) ||
                    (x->wrapperValue <= y->wrapperValue)) {
                  return (x);
                }
                else {
                  return (y);
                }
              }
            }
            else {
              return (x);
            }
          }
        }
      }
      else if (subtypeOfLongIntegerP(testValue000)) {
        { NumberWrapper* x001 = x;
          LongIntegerWrapper* x = ((LongIntegerWrapper*)(x001));

          { Surrogate* testValue002 = safePrimaryType(y);

            if (subtypeOfIntegerP(testValue002)) {
              { NumberWrapper* y003 = y;
                IntegerWrapper* y = ((IntegerWrapper*)(y003));

                if ((!((boolean)(y))) ||
                    (x->wrapperValue <= y->wrapperValue)) {
                  return (x);
                }
                else {
                  return (y);
                }
              }
            }
            else if (subtypeOfLongIntegerP(testValue002)) {
              { NumberWrapper* y004 = y;
                LongIntegerWrapper* y = ((LongIntegerWrapper*)(y004));

                if ((!((boolean)(y))) ||
                    (x->wrapperValue <= y->wrapperValue)) {
                  return (x);
                }
                else {
                  return (y);
                }
              }
            }
            else if (subtypeOfFloatP(testValue002)) {
              { NumberWrapper* y005 = y;
                FloatWrapper* y = ((FloatWrapper*)(y005));

                if ((!((boolean)(y))) ||
                    (x->wrapperValue <= y->wrapperValue)) {
                  return (x);
                }
                else {
                  return (y);
                }
              }
            }
            else {
              return (x);
            }
          }
        }
      }
      else if (subtypeOfFloatP(testValue000)) {
        { NumberWrapper* x002 = x;
          FloatWrapper* x = ((FloatWrapper*)(x002));

          { Surrogate* testValue003 = safePrimaryType(y);

            if (subtypeOfIntegerP(testValue003)) {
              { NumberWrapper* y006 = y;
                IntegerWrapper* y = ((IntegerWrapper*)(y006));

                if ((!((boolean)(y))) ||
                    (x->wrapperValue <= y->wrapperValue)) {
                  return (x);
                }
                else {
                  return (y);
                }
              }
            }
            else if (subtypeOfLongIntegerP(testValue003)) {
              { NumberWrapper* y007 = y;
                LongIntegerWrapper* y = ((LongIntegerWrapper*)(y007));

                if ((!((boolean)(y))) ||
                    (x->wrapperValue <= y->wrapperValue)) {
                  return (x);
                }
                else {
                  return (y);
                }
              }
            }
            else if (subtypeOfFloatP(testValue003)) {
              { NumberWrapper* y008 = y;
                FloatWrapper* y = ((FloatWrapper*)(y008));

                if ((!((boolean)(y))) ||
                    (x->wrapperValue <= y->wrapperValue)) {
                  return (x);
                }
                else {
                  return (y);
                }
              }
            }
            else {
              return (x);
            }
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
}

int integerMax(int x, int y) {
  // Return the maximum of `x' and `y'.  If either is NULL, return the other.
  return (((x > y) ? x : y));
}

long long int longIntegerMax(long long int x, long long int y) {
  // Return the maximum of `x' and `y'.  If either is NULL, return the other.
  return (((x > y) ? x : y));
}

double floatMax(double x, double y) {
  // Return the maximum of `x' and `y'.  If either is NULL, return the other.
  return (((x > y) ? x : y));
}

NumberWrapper* NumberWrapper::max(NumberWrapper* y) {
  // Return the maximum of `x' and `y'.  If `y' is NULL, return `x'.
  { NumberWrapper* x = this;

    { Surrogate* testValue000 = safePrimaryType(x);

      if (subtypeOfIntegerP(testValue000)) {
        { NumberWrapper* x000 = x;
          IntegerWrapper* x = ((IntegerWrapper*)(x000));

          { Surrogate* testValue001 = safePrimaryType(y);

            if (subtypeOfIntegerP(testValue001)) {
              { NumberWrapper* y000 = y;
                IntegerWrapper* y = ((IntegerWrapper*)(y000));

                if ((!((boolean)(y))) ||
                    (x->wrapperValue >= y->wrapperValue)) {
                  return (x);
                }
                else {
                  return (y);
                }
              }
            }
            else if (subtypeOfLongIntegerP(testValue001)) {
              { NumberWrapper* y001 = y;
                LongIntegerWrapper* y = ((LongIntegerWrapper*)(y001));

                if ((!((boolean)(y))) ||
                    (x->wrapperValue >= y->wrapperValue)) {
                  return (x);
                }
                else {
                  return (y);
                }
              }
            }
            else if (subtypeOfFloatP(testValue001)) {
              { NumberWrapper* y002 = y;
                FloatWrapper* y = ((FloatWrapper*)(y002));

                if ((!((boolean)(y))) ||
                    (x->wrapperValue >= y->wrapperValue)) {
                  return (x);
                }
                else {
                  return (y);
                }
              }
            }
            else {
              return (x);
            }
          }
        }
      }
      else if (subtypeOfLongIntegerP(testValue000)) {
        { NumberWrapper* x001 = x;
          LongIntegerWrapper* x = ((LongIntegerWrapper*)(x001));

          { Surrogate* testValue002 = safePrimaryType(y);

            if (subtypeOfIntegerP(testValue002)) {
              { NumberWrapper* y003 = y;
                IntegerWrapper* y = ((IntegerWrapper*)(y003));

                if ((!((boolean)(y))) ||
                    (x->wrapperValue >= y->wrapperValue)) {
                  return (x);
                }
                else {
                  return (y);
                }
              }
            }
            else if (subtypeOfLongIntegerP(testValue002)) {
              { NumberWrapper* y004 = y;
                LongIntegerWrapper* y = ((LongIntegerWrapper*)(y004));

                if ((!((boolean)(y))) ||
                    (x->wrapperValue >= y->wrapperValue)) {
                  return (x);
                }
                else {
                  return (y);
                }
              }
            }
            else if (subtypeOfFloatP(testValue002)) {
              { NumberWrapper* y005 = y;
                FloatWrapper* y = ((FloatWrapper*)(y005));

                if ((!((boolean)(y))) ||
                    (x->wrapperValue >= y->wrapperValue)) {
                  return (x);
                }
                else {
                  return (y);
                }
              }
            }
            else {
              return (x);
            }
          }
        }
      }
      else if (subtypeOfFloatP(testValue000)) {
        { NumberWrapper* x002 = x;
          FloatWrapper* x = ((FloatWrapper*)(x002));

          { Surrogate* testValue003 = safePrimaryType(y);

            if (subtypeOfIntegerP(testValue003)) {
              { NumberWrapper* y006 = y;
                IntegerWrapper* y = ((IntegerWrapper*)(y006));

                if ((!((boolean)(y))) ||
                    (x->wrapperValue >= y->wrapperValue)) {
                  return (x);
                }
                else {
                  return (y);
                }
              }
            }
            else if (subtypeOfLongIntegerP(testValue003)) {
              { NumberWrapper* y007 = y;
                LongIntegerWrapper* y = ((LongIntegerWrapper*)(y007));

                if ((!((boolean)(y))) ||
                    (x->wrapperValue >= y->wrapperValue)) {
                  return (x);
                }
                else {
                  return (y);
                }
              }
            }
            else if (subtypeOfFloatP(testValue003)) {
              { NumberWrapper* y008 = y;
                FloatWrapper* y = ((FloatWrapper*)(y008));

                if ((!((boolean)(y))) ||
                    (x->wrapperValue >= y->wrapperValue)) {
                  return (x);
                }
                else {
                  return (y);
                }
              }
            }
            else {
              return (x);
            }
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
}

int integerAbs(int x) {
  // Return the absolute value of `x'.
  return (((x < 0) ? (0 - x) : x));
}

long long int longIntegerAbs(long long int x) {
  // Return the absolute value of `x'.
  return (((x < 0) ? (0 - x) : x));
}

double floatAbs(double x) {
  // Return the absolute value of `x'.
  return (((x < 0.0) ? (0.0 - x) : x));
}

int characterCode(char ch) {
  // Return the 8-bit ASCII code of `ch' as an integer.
  return ((int)(unsigned char) ch);
}

char codeCharacter(int code) {
  // Return the character encoded by `code' (0 <= `code' <= 255).
  return ((char) code);
}

char characterDowncase(char ch) {
  // If `ch' is lowercase, return its uppercase version,
  // otherwise, return 'ch' unmodified.
  return (oCHARACTER_DOWNCASE_TABLEo[((int)(unsigned char) ch)]);
}

char characterUpcase(char ch) {
  // If `ch' is uppercase, return its lowercase version,
  // otherwise, return 'ch' unmodified.  If only the first character of
  // a sequence of characters is to be capitalized, `character-capitalize'
  // should be used instead.
  return (oCHARACTER_UPCASE_TABLEo[((int)(unsigned char) ch)]);
}

char characterCapitalize(char ch) {
  // Return the capitalized character for `ch'.  This is generally the same
  // as the uppercase character, except for obscure non-English characters in Java.  It should
  // be used if only the first character of a sequence of characters is to be capitalized.
  return (oCHARACTER_UPCASE_TABLEo[((int)(unsigned char) ch)]);
}

DEFINE_STELLA_SPECIAL(oTRANSIENTOBJECTSpo, boolean , false);

boolean stringEqlP(const char* x, const char* y) {
  // Return true if `x' and `y' are equal strings or are both undefined.  This
  // test is substituted automatically by the STELLA translator if `eql?' is applied
  // to strings.
  if (x == NULL) {
    return (y == NULL);
  }
  else {
    return ((y != NULL) &&
        !strcmp(x, y));
  }
}

boolean stringEqualP(const char* x, const char* y) {
  // Return true if `x' and `y' are equal strings ignoring character case or
  // are both undefined.
  if (x == NULL) {
    return (y == NULL);
  }
  else {
    return ((y != NULL) &&
        (strcasecmp(x, y) == 0));
  }
}

int stringCompare(const char* x, const char* y, boolean caseSensitiveP) {
  // Compare `x' and `y' lexicographically, and return -1, 0, 
  // or 1, depending on whether `x' is less than, equal, or greater than `y'.
  // If `case-sensitive?' is true, then case does matter for the comparison
  if (caseSensitiveP) {
    return (strcmp(x, y));
  }
  else {
    return (strcasecmp(x, y));
  }
}

boolean stringEmptyP(const char* x) {
  // Return true if `x' is the empty string ""
  return (stringEqlP(x, ""));
}

boolean stringNonEmptyP(const char* x) {
  // Return true if `x' is not the empty string ""
  return (!stringEqlP(x, ""));
}

boolean StringWrapper::emptyP() {
  // Return true if `x' is the wrapped empty string ""
  { StringWrapper* x = this;

    return (stringEqlP(x->wrapperValue, ""));
  }
}

boolean StringWrapper::nonEmptyP() {
  // Return true if `x' is not the wrapped empty string ""
  { StringWrapper* x = this;

    return (!stringEqlP(x->wrapperValue, ""));
  }
}

boolean blankStringP(const char* string) {
  // Return true if `string' is either NULL, empty, or only
  // contains white space characters.
  { boolean testValue000 = false;

    if (string == NULL) {
      testValue000 = true;
    }
    else {
      if (stringEqlP(string, "")) {
        testValue000 = true;
      }
      else {
        { boolean alwaysP000 = true;

          { char chaR = NULL_CHARACTER;
            const char* vector000 = string;
            int index000 = 0;
            int length000 = strlen(vector000);

            for  (; index000 < length000; 
                  index000 = index000 + 1) {
              chaR = vector000[index000];
              if (!(oCHARACTER_TYPE_TABLEo[(int)(unsigned char) chaR] == KWD_PRIMAL_WHITE_SPACE)) {
                alwaysP000 = false;
                break;
              }
            }
          }
          testValue000 = alwaysP000;
        }
      }
    }
    { boolean value000 = testValue000;

      return (value000);
    }
  }
}

boolean stringL(const char* x, const char* y) {
  // Return true if `x' is lexicographically < `y', considering case.
  return (stringCompare(x, y, true) < 0);
}

boolean stringLE(const char* x, const char* y) {
  // Return true if `x' is lexicographically <= `y', considering case.
  return (stringCompare(x, y, true) <= 0);
}

boolean stringGE(const char* x, const char* y) {
  // Return true if `x' is lexicographically >= `y', considering case.
  return (stringCompare(x, y, true) >= 0);
}

boolean stringG(const char* x, const char* y) {
  // Return true if `x' is lexicographically > `y', considering case.
  return (stringCompare(x, y, true) > 0);
}

boolean stringLessP(const char* x, const char* y) {
  // Return true if `x' is lexicographically < `y', ignoring case.
  return (stringCompare(x, y, false) < 0);
}

boolean stringLessEqualP(const char* x, const char* y) {
  // Return true if `x' is lexicographically <= `y', ignoring case.
  return (stringCompare(x, y, false) <= 0);
}

boolean stringGreaterEqualP(const char* x, const char* y) {
  // Return true if `x' is lexicographically >= `y', ignoring case.
  return (stringCompare(x, y, false) >= 0);
}

boolean stringGreaterP(const char* x, const char* y) {
  // Return true if `x' is lexicographically > `y', ignoring case.
  return (stringCompare(x, y, false) > 0);
}

int stringCompareCaseNormalized(const char* x, const char* y) {
  // Compare `x' and `y' and return -1, 0, or 1, depending on whether
  // `x' is less than, equal, or greater than `y' relative to the :ascii-case-normalized
  // collation.  In this collation `a < A < b' which gives strings that only differ in case a
  // definite order while otherwise behaving identically to :ascii-case-insensitive.  This is
  // similar to using a Java Collator for Locale.US with strength set to TERTIARY (which see).
  { int xlength = strlen(x);
    int ylength = strlen(y);
    char xch = NULL_CHARACTER;
    char ych = NULL_CHARACTER;

    { int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = stella::integerMin(xlength, ylength) - 1;

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        i = iter000;
        xch = x[i];
        ych = y[i];
        if (!(xch == ych)) {
          { char xchdown = oCHARACTER_DOWNCASE_TABLEo[((int)(unsigned char) xch)];
            char ychdown = oCHARACTER_DOWNCASE_TABLEo[((int)(unsigned char) ych)];

            if (xchdown == ychdown) {
              if ((int)(unsigned char) xch < (int)(unsigned char) ych) {
                return (1);
              }
              else {
                return (-1);
              }
            }
            else {
              if ((int)(unsigned char) xchdown < (int)(unsigned char) ychdown) {
                return (-1);
              }
              else {
                return (1);
              }
            }
          }
        }
      }
    }
    if (xlength == ylength) {
      return (0);
    }
    else if (xlength < ylength) {
      return (-1);
    }
    else {
      return (1);
    }
  }
}

int compareStrings(const char* x, const char* y, Keyword* collation) {
  // Compare `x' and `y' and return -1, 0, or 1, depending on whether
  // `x' is less than, equal, or greater than `y' relative to `collation'.  Currently
  // supported values for `collation' are :ascii-case-sensitive, :ascii-case-insensitive
  // :ascii-case-normalized.  The first two correspond to `string-compare' called with
  // the appropriate third argument.  :ascii-case-normalized calls the function
  // `string-compare-case-normalized' (which see).
  if (collation == KWD_PRIMAL_ASCII_CASE_SENSITIVE) {
    return (stringCompare(x, y, true));
  }
  else if (collation == KWD_PRIMAL_ASCII_CASE_INSENSITIVE) {
    return (stringCompare(x, y, false));
  }
  else if (collation == KWD_PRIMAL_ASCII_CASE_NORMALIZED) {
    return (stringCompareCaseNormalized(x, y));
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "compare-strings: unsupported collation: " << "`" << collation << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

int safeCompareStrings(const char* x, const char* y, Keyword* collation) {
  // Variant of `compare-strings' that also tolerates NULL values.
  // NULL sorts after everything else in any collation.
  if (x == NULL) {
    if (y == NULL) {
      return (0);
    }
    else {
      return (1);
    }
  }
  else if (y == NULL) {
    return (-1);
  }
  else {
    return (compareStrings(x, y, collation));
  }
}

char* makeMutableString(int size, char initchar) {
  // Return a new mutable string filled with `size' `initchar's.
  return (native_make_mutable_string(size, initchar));
}

char* makeRawMutableString(int size) {
  // Return a new uninitialized mutable string of `size'.
  { char* s = NULL;

    s = new (PointerFreeGC) char[size+1]; s[size]='\0';
    return (s);
  }
}

const char* stringConcatenate(const char* string1, const char* string2, int otherstrings, ...) {
  // Return a new string representing the concatenation
  // of `string1', `string2', and `otherStrings'.  The two mandatory parameters
  // allow us to optimize the common binary case by not relying on the somewhat
  // less efficient variable arguments mechanism.
  if (otherstrings == 0) {
    return (stringConcatenate(string1, string2));
  }
  { char* result = NULL;
    int length = strlen(string1) + strlen(string2);
    int index = 0;

    { va_list iter000;
      int iter000Count = otherstrings;
      const char* string = NULL;

      va_start(iter000, otherstrings);
            for  (; (iter000Count--) > 0; ) {
        string = va_arg(iter000, const char*);
        length = length + strlen(string);
      }
      va_end(iter000);
    }
    result = makeRawMutableString(length);
    { char ch = NULL_CHARACTER;
      const char* vector000 = string1;
      int index000 = 0;
      int length000 = strlen(vector000);

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        ch = vector000[index000];
        result[index] = ch;
        index = index + 1;
      }
    }
    { char ch = NULL_CHARACTER;
      const char* vector001 = string2;
      int index001 = 0;
      int length001 = strlen(vector001);

      for  (; index001 < length001; 
            index001 = index001 + 1) {
        ch = vector001[index001];
        result[index] = ch;
        index = index + 1;
      }
    }
    { va_list iter001;
      int iter001Count = otherstrings;
      const char* string = NULL;

      va_start(iter001, otherstrings);
            for  (; (iter001Count--) > 0; ) {
        string = va_arg(iter001, const char*);
        { char ch = NULL_CHARACTER;
          const char* vector002 = string;
          int index002 = 0;
          int length002 = strlen(vector002);

          for  (; index002 < length002; 
                index002 = index002 + 1) {
            ch = vector002[index002];
            result[index] = ch;
            index = index + 1;
          }
        }
      }
      va_end(iter001);
    }
    return (result);
  }
}

extern "C" const char* stella_stringCopy(const char* string) {
  // C-callable wrapper for `stringCopy'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(stringCopy(string)));
    return (((const char*)(oC_API_RESULT_BUFFERo)));
  }
}

extern "C" char* stella_mutableStringCopy(char* string) {
  // C-callable wrapper for `mutableStringCopy'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(mutableStringCopy(string)));
    return (((char*)(oC_API_RESULT_BUFFERo)));
  }
}

char* helpSubstituteCharacters(char* self, const char* newChars, const char* oldChars) {
  { int pos = NULL_INTEGER;

    { int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = strlen(self) - 1;

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        i = iter000;
        pos = stringPosition(oldChars, self[i], 0);
        if (pos != NULL_INTEGER) {
          self[i] = (newChars[pos]);
        }
      }
    }
    return (self);
  }
}

char* mutableStringSubstituteCharacters(char* self, const char* newChars, const char* oldChars) {
  // Substitute all occurences of of a member of `old-chars' with the 
  // corresponding member of `new-chars' in the string `self'.  IMPORTANT:  The return
  // value should be used instead of relying on destructive substitution, since the
  // substitution will not be destructive in all translated languages.
  return (helpSubstituteCharacters(self, newChars, oldChars));
}

const char* stringSubstituteCharacters(const char* self, const char* newChars, const char* oldChars) {
  // Substitute all occurences of of a member of `old-chars' with the 
  // corresponding member of `new-chars' in the string `self'.  Returns a new string.
  return ((helpSubstituteCharacters(strcpy(new (GC) char[strlen(self)+1], self), newChars, oldChars)));
}

const char* replaceSubstrings(const char* string, const char* neW, const char* old) {
  // Replace all occurrences of `old' in `string' with `new'.
  { int stringlength = strlen(string);
    int oldlength = strlen(old);
    int newlength = strlen(neW);
    int nofoccurrences = 0;
    int oldstart = 0;
    int cursor = 0;
    int resultcursor = 0;
    char* result = NULL;

    while ((oldstart = stringSearch(string, old, cursor)) != NULL_INTEGER) {
      nofoccurrences = nofoccurrences + 1;
      cursor = oldstart + oldlength;
    }
    if (nofoccurrences == 0) {
      return (string);
    }
    result = makeRawMutableString(stringlength + (nofoccurrences * (newlength - oldlength)));
    cursor = 0;
    while ((oldstart = stringSearch(string, old, cursor)) != NULL_INTEGER) {
      { int i = NULL_INTEGER;
        int iter000 = cursor;
        int upperBound000 = oldstart - 1;

        for  (; iter000 <= upperBound000; 
              iter000 = iter000 + 1) {
          i = iter000;
          result[resultcursor] = (string[i]);
          resultcursor = resultcursor + 1;
        }
      }
      { char chaR = NULL_CHARACTER;
        const char* vector000 = neW;
        int index000 = 0;
        int length000 = strlen(vector000);

        for  (; index000 < length000; 
              index000 = index000 + 1) {
          chaR = vector000[index000];
          result[resultcursor] = chaR;
          resultcursor = resultcursor + 1;
        }
      }
      cursor = oldstart + oldlength;
    }
    { int i = NULL_INTEGER;
      int iter001 = cursor;
      int upperBound001 = stringlength - 1;

      for  (; iter001 <= upperBound001; 
            iter001 = iter001 + 1) {
        i = iter001;
        result[resultcursor] = (string[i]);
        resultcursor = resultcursor + 1;
      }
    }
    return (result);
  }
}

const char* instantiateStringTemplate(const char* templatE, int varsAvalues, ...) {
  // For each occurrence of a <var> string from `vars&values' in `template' replace it
  // with its corresponding <value> string.  Replacement is done in sequence which
  // means (part of) a value might be replaced further with a later <var> and <value>.
  { const char* var = NULL;

    { va_list iter000;
      int iter000Count = varsAvalues;
      const char* item = NULL;

      va_start(iter000, varsAvalues);
            for  (; (iter000Count--) > 0; ) {
        item = va_arg(iter000, const char*);
        if (var != NULL) {
          templatE = replaceSubstrings(templatE, item, var);
          var = NULL;
        }
        else {
          var = item;
        }
      }
      va_end(iter000);
    }
    return (templatE);
  }
}

int insertString(const char* source, int start, int end, char* target, int targetIndex, Keyword* caseConversion) {
  // Inserts characters from `source' begining at `start' and
  // ending at `end' into `target' starting at `target-index'.  If `end' is `null',
  // then the entire length of the string is used. The copy of characters is affected
  // by the `case-conversion' keyword which should be one of
  //    :UPCASE :DOWNCASE :CAPITALIZE :PRESERVE.
  // 
  // The final value of target-index is returned.
  if (end == NULL_INTEGER) {
    end = strlen(source) - 1;
  }
  if (end < start) {
    return (targetIndex);
  }
  if (caseConversion == KWD_PRIMAL_UPCASE) {
    { int j = NULL_INTEGER;
      int iter000 = start;
      int upperBound000 = end;
      boolean unboundedP000 = upperBound000 == NULL_INTEGER;

      for  (; unboundedP000 ||
                (iter000 <= upperBound000); 
            iter000 = iter000 + 1) {
        j = iter000;
        target[targetIndex] = (oCHARACTER_UPCASE_TABLEo[((int)(unsigned char) (source[j]))]);
        targetIndex = targetIndex + 1;
      }
    }
  }
  else if (caseConversion == KWD_PRIMAL_DOWNCASE) {
    { int j = NULL_INTEGER;
      int iter001 = start;
      int upperBound001 = end;
      boolean unboundedP001 = upperBound001 == NULL_INTEGER;

      for  (; unboundedP001 ||
                (iter001 <= upperBound001); 
            iter001 = iter001 + 1) {
        j = iter001;
        target[targetIndex] = (oCHARACTER_DOWNCASE_TABLEo[((int)(unsigned char) (source[j]))]);
        targetIndex = targetIndex + 1;
      }
    }
  }
  else if (caseConversion == KWD_PRIMAL_CAPITALIZE) {
    target[targetIndex] = (oCHARACTER_UPCASE_TABLEo[((int)(unsigned char) (source[start]))]);
    targetIndex = targetIndex + 1;
    { int j = NULL_INTEGER;
      int iter002 = start + 1;
      int upperBound002 = end;
      boolean unboundedP002 = upperBound002 == NULL_INTEGER;

      for  (; unboundedP002 ||
                (iter002 <= upperBound002); 
            iter002 = iter002 + 1) {
        j = iter002;
        target[targetIndex] = (oCHARACTER_DOWNCASE_TABLEo[((int)(unsigned char) (source[j]))]);
        targetIndex = targetIndex + 1;
      }
    }
  }
  else if (caseConversion == KWD_PRIMAL_PRESERVE) {
    { int j = NULL_INTEGER;
      int iter003 = start;
      int upperBound003 = end;
      boolean unboundedP003 = upperBound003 == NULL_INTEGER;

      for  (; unboundedP003 ||
                (iter003 <= upperBound003); 
            iter003 = iter003 + 1) {
        j = iter003;
        target[targetIndex] = (source[j]);
        targetIndex = targetIndex + 1;
      }
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << caseConversion << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (targetIndex);
}

const char* stringTrim(const char* string) {
  // Remove any leading and trailing white space from `string'
  // and return a copy of the trimmed substring (which might be empty if we had
  // all white space).  If no white space was removed, `string' is returned
  // unmodified and uncopied.
  { int start = 0;
    int last = strlen(string) - 1;
    int end = last;

    while ((start <= end) &&
        (oCHARACTER_TYPE_TABLEo[(int)(unsigned char) (string[start])] == KWD_PRIMAL_WHITE_SPACE)) {
      start = start + 1;
    }
    while ((end > start) &&
        (oCHARACTER_TYPE_TABLEo[(int)(unsigned char) (string[end])] == KWD_PRIMAL_WHITE_SPACE)) {
      end = end - 1;
    }
    if ((start > 0) ||
        (end < last)) {
      return (stringSubsequence(string, start, end + 1));
    }
    else {
      return (string);
    }
  }
}

const char* intToString(int i) {
  // Convert `i' to its string representation and return the result.
  // This is a convenience function that expects regular integers as opposed to longs
  // which is useful in contexts where we do automatic unwrapping based on the target.
  return (integerToString(((long long int)(i))));
}

const char* characterToString(char c) {
  // Convert `c' into a one-element string and return the result.
  return (makeString(1, c));
}

const char* stellaIntegerToStringInBase(long long int integer, int base) {
  // STELLA version of `integer-to-string-in-base' which is faster than
  // the C++ version we have but slower than the native Java version.
  if (!((base >= 2) &&
      (base <= 36))) {
    std::cerr << "Safety violation: " << "integer-to-string-in-base: illegal base: " << "`" << base << "'";
  }
  if (integer == 0) {
    return ("0");
  }
  { int offset = ((integer < 0) ? 1 : 0);

    if (offset == 1) {
      integer = 0 - integer;
    }
    { int integerbits = integerLength(integer);
      int basebits = integerLength(((long long int)(base)));
      int bufferlength = offset + (integerbits / (basebits - 1)) + 1;
      char* buffer = makeRawMutableString(bufferlength);
      int index = bufferlength;
      const char* table = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
      long long int remainder = 0l;
      int digit = 0;
      int base1 = base - 1;

      if ((base & base1) == 0) {
        basebits = basebits - 1;
        while (integer > 0) {
          index = index - 1;
          digit = ((int)((integer & (((long long int)(base1))))));
          integer = (integer >> basebits);
          buffer[index] = (table[digit]);
        }
      }
      else {
        while (integer > 0) {
          index = index - 1;
          remainder = (integer / (((long long int)(base))));
          digit = ((int)(integer - (remainder * base)));
          integer = remainder;
          buffer[index] = (table[digit]);
        }
      }
      if (offset == 1) {
        index = index - 1;
        buffer[index] = '-';
      }
      if (index == 0) {
        return (buffer);
      }
      else {
        return (mutableStringSubsequence(buffer, index, bufferlength));
      }
    }
  }
}

int stringToInt(const char* string) {
  // Convert a `string' representation of an integer into an integer.
  // This is a convenience function that ensures a regular integer return value.  If
  // `string' represents a long integer, the behavior is undefined.  Use `parse-integer'
  // if the syntax of `string' needs to be checked for errors.
  return (((int)(stringToInteger(string))));
}

const char* formatWithPadding(const char* input, int length, char padchar, Keyword* align, boolean truncateP) {
  // Formats `input' to be (at least) `length' long, using `padchar' to
  // fill if necessary.  `align' must be one of :LEFT, :RIGHT, :CENTER and will control
  // how `input' will be justified in the resulting string.  If `truncate?' is true, then
  // then an overlength string will be truncated, using the opposite of `align' to pick
  // the truncation direction.
  { int len = strlen(input);

    if (len == length) {
      return (input);
    }
    else if (len > length) {
      if (truncateP) {
        if (align == KWD_PRIMAL_LEFT) {
          return (stringSubsequence(input, len - length, len));
        }
        else if (align == KWD_PRIMAL_RIGHT) {
          return (stringSubsequence(input, 0, len - length));
        }
        else if (align == KWD_PRIMAL_CENTER) {
          { int left = ((int)((len - length) / 2.0));

            return (stringSubsequence(input, left, left + length));
          }
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << align << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
        }
      }
      else {
        return (input);
      }
    }
    else {
      if (align == KWD_PRIMAL_LEFT) {
        return (stringConcatenate(input, makeString(length - len, padchar), 0));
      }
      else if (align == KWD_PRIMAL_RIGHT) {
        return (stringConcatenate(makeString(length - len, padchar), input, 0));
      }
      else if (align == KWD_PRIMAL_CENTER) {
        { int left = ((int)((length - len) / 2.0));

          return (stringConcatenate(makeString(left, padchar), input, 1, makeString((length - len) - left, padchar)));
        }
      }
      else {
        { OutputStringStream* stream001 = newOutputStringStream();

          *(stream001->nativeStream) << "`" << align << "'" << " is not a valid case option";
          throw *newStellaException(stream001->theStringReader());
        }
      }
    }
  }
}

const char* zeroPadInteger(int value, int size) {
  // Returns a string representing `value' of at least length
  // 'size', padded if necessary with 0 characters.
  return (((value < 0) ? stringConcatenate("-", formatWithPadding(integerToString(((long long int)(0 - value))), size - 1, '0', KWD_PRIMAL_RIGHT, false), 0) : formatWithPadding(integerToString(((long long int)(value))), size, '0', KWD_PRIMAL_RIGHT, false)));
}

const char* zeroPadString(const char* input, int size) {
  return (formatWithPadding(input, size, '0', KWD_PRIMAL_RIGHT, false));
}

char stringFirst(const char* self) {
  // Return the first character of `self'.
  return (self[0]);
}

char mutableStringFirst(char* self) {
  // Return the first character of `self' (settable via `setf').
  return (self[0]);
}

char mutableStringFirstSetter(char* self, char ch) {
  // Set the first character of `self' to `ch' and return `ch'.
  return (self[0] = ch);
}

char stringSecond(const char* self) {
  // Return the second character of `self'.
  return (self[1]);
}

char mutableStringSecond(char* self) {
  // Return the second character of `self' (settable via `setf').
  return (self[1]);
}

char mutableStringSecondSetter(char* self, char ch) {
  // Set the second character of `self' to `ch' and return `ch'.
  return (self[1] = ch);
}

char stringThird(const char* self) {
  // Return the third character of `self'.
  return (self[2]);
}

char mutableStringThird(char* self) {
  // Return the third character of `self' (settable via `setf').
  return (self[2]);
}

char mutableStringThirdSetter(char* self, char ch) {
  // Set the third character of `self' to `ch' and return `ch'.
  return (self[2] = ch);
}

char stringFourth(const char* self) {
  // Return the fourth character of `self'.
  return (self[3]);
}

char mutableStringFourth(char* self) {
  // Return the fourth character of `self' (settable via `setf').
  return (self[3]);
}

char mutableStringFourthSetter(char* self, char ch) {
  // Set the fourth character of `self' to `ch' and return `ch'.
  return (self[3] = ch);
}

char stringFifth(const char* self) {
  // Return the fifth character of `self'.
  return (self[4]);
}

char mutableStringFifth(char* self) {
  // Return the fifth character of `self' (settable via `setf').
  return (self[4]);
}

char mutableStringFifthSetter(char* self, char ch) {
  // Set the fifth character of `self' to `ch' and return `ch'.
  return (self[4] = ch);
}

char stringNth(const char* self, int position) {
  // Return the character in `self' at `position'.
  return (self[position]);
}

char mutableStringNth(char* self, int position) {
  // Return the character in `self' at `position'.
  return (self[position]);
}

char mutableStringNthSetter(char* self, char ch, int position) {
  // Set the character in `self' at `position' to `ch'.
  return (self[position] = ch);
}

int stringLength(const char* self) {
  // Return the length of the string `self'.
  return (strlen(self));
}

int mutableStringLength(char* self) {
  // Return the length of the string `self'.
  return (strlen(self));
}

int stringSearchIgnoreCase(const char* string, const char* substring, int start) {
  // Return start position of the left-most occurrence of
  // `substring' in `string', beginning from `start'.  Return NULL if it is not
  // a substring.  The comparison ignores differences in letter case.
  if (start == NULL_INTEGER) {
    start = 0;
  }
  return (stringSearch(stringDowncase(string), stringDowncase(substring), start));
}

boolean startsWithP(const char* string, const char* prefix, int start) {
  // Return TRUE if `string' starts with `prefix' starting from
  // `start' (which defaults to 0 if it is supplied as NULL).
  if (start == NULL_INTEGER) {
    start = 0;
  }
  { int prefixlength = strlen(prefix);

    if ((start + prefixlength) > strlen(string)) {
      return (false);
    }
    else {
      { boolean alwaysP000 = true;

        { int i = NULL_INTEGER;
          int iter000 = 0;
          int upperBound000 = prefixlength - 1;
          int j = NULL_INTEGER;
          int iter001 = start;

          for  (; iter000 <= upperBound000; 
                iter000 = iter000 + 1,
                iter001 = iter001 + 1) {
            i = iter000;
            j = iter001;
            if (!(prefix[i] == string[j])) {
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
}

boolean endsWithP(const char* string, const char* suffix, int end) {
  // Return TRUE if the substring of `string' ending at `end'
  // ends with `suffix'.  If `end' is NULL it defaults to the length of `string'.
  if (end == NULL_INTEGER) {
    end = strlen(string);
  }
  { int suffixlength = strlen(suffix);
    int start = end - suffixlength;

    if (start < 0) {
      return (false);
    }
    else {
      { boolean alwaysP000 = true;

        { int i = NULL_INTEGER;
          int iter000 = 0;
          int upperBound000 = suffixlength - 1;
          int j = NULL_INTEGER;
          int iter001 = start;

          for  (; iter000 <= upperBound000; 
                iter000 = iter000 + 1,
                iter001 = iter001 + 1) {
            i = iter000;
            j = iter001;
            if (!(suffix[i] == string[j])) {
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
}

int helpFindMatchingPrefixLength(const char* string1, int start1, int end1, const char* string2, int start2, int end2) {
  // Helping function for `find-matching-prefix' that requires `end1' and `end2'
  // to be properly set up.
  { int i1 = start1;
    int i2 = start2;

    while ((i1 < end1) &&
        ((i2 < end2) &&
         (string1[i1] == string2[i2]))) {
      i1 = i1 + 1;
      i2 = i2 + 1;
    }
    return (i1 - start1);
  }
}

int findMatchingPrefixLength(const char* string1, int start1, int end1, const char* string2, int start2, int end2) {
  // Finds the length of the matching prefix strings of `string1' and
  // `string2', starting at position `start1' and `start2' respectively.
  // The search will end when `end1' or `end2' is reached.  If either `end1'
  // or `end2' is null, then they will be set to the length of their respective
  // strings.
  if (end1 == NULL_INTEGER) {
    end1 = strlen(string1);
  }
  if (end2 == NULL_INTEGER) {
    end2 = strlen(string2);
  }
  return (helpFindMatchingPrefixLength(string1, start1, end1, string2, start2, end2));
}

int findMismatch(const char* string1, int start1, int end1, const char* string2, int start2, int end2, int& _Return1) {
  // Finds the first position in each of `string1' and `string2' where
  // they mismatch, starting at position `start1' and `start2' respectively.
  // The search will end when `end1' or `end2' is reached.  If either `end1'
  // or `end2' is null, then they will be set to the length of their respective
  // strings.  If there is no mismatch, then `null' values are returned.
  if (end1 == NULL_INTEGER) {
    end1 = strlen(string1);
  }
  if (end2 == NULL_INTEGER) {
    end2 = strlen(string2);
  }
  { int len = helpFindMatchingPrefixLength(string1, start1, end1, string2, start2, end2);

    start1 = start1 + len;
    start2 = start2 + len;
    if ((start1 == end1) &&
        (start2 == end2)) {
      _Return1 = NULL_INTEGER;
      return (NULL_INTEGER);
    }
    else {
      _Return1 = start2;
      return (start1);
    }
  }
}

int nonMatchingPositionHelper(const char* source, int start, int end, const char* match) {
  // Helper for `non-matching-position' that requires `end' to not be `null'.
  while ((start < end) &&
      stringMemberP(match, source[start])) {
    start = start + 1;
  }
  return (start);
}

int nonMatchingPosition(const char* source, int start, const char* match) {
  // Returns the index into `source', starting from `start', of the first
  // character that is not included in `match'.
  return (nonMatchingPositionHelper(source, start, strlen(source), match));
}

int helpAdvancePastWhitespace(const char* source, int start, int end) {
  // Helper for `advance-past-whitespace' that requires `end' to be properly set.
  while ((start < end) &&
      (oCHARACTER_TYPE_TABLEo[(int)(unsigned char) (source[start])] == KWD_PRIMAL_WHITE_SPACE)) {
    start = start + 1;
  }
  return (start);
}

int advancePastWhitespace(const char* source, int start) {
  // Returns the first index into `source', starting from `start', of
  // the first character that is not white space.
  return (helpAdvancePastWhitespace(source, start, strlen(source)));
}

boolean eqlExceptInWhitespaceP(const char* s1, const char* s2) {
  // Return `true' if the strings `s1' and `s2' are the same
  // except for the amounts of whitespace separating words.  Leading or
  // trailing whitespace is also not considered.
  if (s1 == NULL) {
    return (s2 == NULL);
  }
  else if (s2 == NULL) {
    return (false);
  }
  else if (stringEqlP(s1, s2)) {
    return (true);
  }
  { int len1 = strlen(s1);
    int len2 = strlen(s2);
    int i1 = 0;
    int i2 = 0;

    while ((i1 < len1) &&
        (i2 < len2)) {
      if (oCHARACTER_TYPE_TABLEo[(int)(unsigned char) (s1[i1])] == KWD_PRIMAL_WHITE_SPACE) {
        if (oCHARACTER_TYPE_TABLEo[(int)(unsigned char) (s2[i2])] == KWD_PRIMAL_WHITE_SPACE) {
          {
            while ((i1 < len1) &&
                (oCHARACTER_TYPE_TABLEo[(int)(unsigned char) (s1[i1])] == KWD_PRIMAL_WHITE_SPACE)) {
              i1 = i1 + 1;
            }
            while ((i2 < len2) &&
                (oCHARACTER_TYPE_TABLEo[(int)(unsigned char) (s2[i2])] == KWD_PRIMAL_WHITE_SPACE)) {
              i2 = i2 + 1;
            }
          }
        }
        else {
          return (false);
        }
      }
      else if (s1[i1] == s2[i2]) {
        i1 = i1 + 1;
        i2 = i2 + 1;
      }
      else {
        return (false);
      }
    }
    while ((i1 < len1) &&
        (oCHARACTER_TYPE_TABLEo[(int)(unsigned char) (s1[i1])] == KWD_PRIMAL_WHITE_SPACE)) {
      i1 = i1 + 1;
    }
    while ((i2 < len2) &&
        (oCHARACTER_TYPE_TABLEo[(int)(unsigned char) (s2[i2])] == KWD_PRIMAL_WHITE_SPACE)) {
      i2 = i2 + 1;
    }
    return ((i1 == len1) &&
        (i2 == len2));
  }
}

Cons* splitString(const char* input, char separator) {
  // Split `input' into separate strings based on the `separator' character.
  { int length = strlen(input);
    int start = 0;
    int end = 0;
    Cons* strings = NIL;

    for (;;) {
      end = stringPosition(input, separator, start);
      strings = cons(wrapString(stringSubsequence(input, start, end)), strings);
      if ((end != NULL_INTEGER) &&
          (end < (length - 1))) {
        start = end + 1;
      }
      else {
        break;
      }
    }
    return (strings->reverse());
  }
}

Object* unstringify(const char* string) {
  // Read a STELLA expression from `string' and return the result.
  // This is identical to `read-s-expression-from-string'.
  return (readSExpressionFromString(string));
}

# include "stella/cpp-lib/cpp-hashtable.hh"
void AbstractHashTable::freeHashTableValues() {
  // Call free on each value in the hash table `self'.
  { AbstractHashTable* self = this;

    if (oUSE_STELLA_HASH_TABLESpo) {
      return;
    }
    { cpp_hash_table* nativeTable = self->theHashTable;

      std::cout << "WARNING: freeHashTableValues not yet implemented" << std::endl;;
    }
  }
}

void AbstractHashTable::initializeHashTable() {
  // Insert a newly-created native hash table into `self'.
  { AbstractHashTable* self = this;

    if (oUSE_STELLA_HASH_TABLESpo) {
      self->theStellaHashTable = newStellaHashTable();
      return;
    }
    self->theHashTable = (cpp_hash_table*)(new Native_EQL_Hash_Table<Object*, Object*>);
  }
}

Object* HashTable::lookup(Object* key) {
  { HashTable* self = this;

    if (oUSE_STELLA_HASH_TABLESpo) {
      return (stellaHashTableLookup(self->theStellaHashTable, key));
    }
    { cpp_hash_table* nativeTable = self->theHashTable;

      return (((Native_EQL_Hash_Table<Object*, Object*>*)nativeTable)->get(key));
    }
  }
}

void HashTable::insertAt(Object* key, Object* value) {
  { HashTable* self = this;

    if (oUSE_STELLA_HASH_TABLESpo) {
      stellaHashTableInsertAt(self->theStellaHashTable, key, value);
      return;
    }
    { cpp_hash_table* nativeTable = self->theHashTable;

      (*((Native_EQL_Hash_Table<Object*, Object*>*)nativeTable))[key] = value;;
    }
  }
}

void HashTable::removeAt(Object* key) {
  { HashTable* self = this;

    if (oUSE_STELLA_HASH_TABLESpo) {
      stellaHashTableRemoveAt(self->theStellaHashTable, key);
      return;
    }
    { cpp_hash_table* nativeTable = self->theHashTable;

      ((Native_EQL_Hash_Table<Object*, Object*>*)nativeTable)->erase(key);;
    }
  }
}

void IntegerHashTable::initializeHashTable() {
  // Insert a newly-created native hash table into `self'.
  { IntegerHashTable* self = this;

    if (oUSE_STELLA_HASH_TABLESpo) {
      self->theStellaHashTable = newStellaHashTable();
      return;
    }
    self->theHashTable = ((cpp_hash_table*)(new Native_EQL_Hash_Table<int, Object*>));
  }
}

Object* IntegerHashTable::lookup(int key) {
  { IntegerHashTable* self = this;

    if (oUSE_STELLA_HASH_TABLESpo) {
      return (stellaHashTableLookup(self->theStellaHashTable, wrapInteger(key)));
    }
    { cpp_hash_table* nativeTable = self->theHashTable;

      return (((Native_EQL_Hash_Table<int, Object*>*)nativeTable)->get(key));
    }
  }
}

void IntegerHashTable::insertAt(int key, Object* value) {
  { IntegerHashTable* self = this;

    if (oUSE_STELLA_HASH_TABLESpo) {
      stellaHashTableInsertAt(self->theStellaHashTable, wrapInteger(key), value);
      return;
    }
    { cpp_hash_table* nativeTable = self->theHashTable;

      (*((Native_EQL_Hash_Table<int, Object*>*)nativeTable))[key] = value;;
    }
  }
}

void IntegerHashTable::removeAt(int key) {
  { IntegerHashTable* self = this;

    if (oUSE_STELLA_HASH_TABLESpo) {
      stellaHashTableRemoveAt(self->theStellaHashTable, wrapInteger(key));
      return;
    }
    { cpp_hash_table* nativeTable = self->theHashTable;

      ((Native_EQL_Hash_Table<int, Object*>*)nativeTable)->erase(key);;
    }
  }
}

void FloatHashTable::initializeHashTable() {
  // Insert a newly-created native hash table into `self'.
  { FloatHashTable* self = this;

    if (oUSE_STELLA_HASH_TABLESpo) {
      self->theStellaHashTable = newStellaHashTable();
      return;
    }
    self->theHashTable = (cpp_hash_table*)(new Native_EQL_Hash_Table<double, Object*>);
  }
}

Object* FloatHashTable::lookup(double key) {
  { FloatHashTable* self = this;

    if (oUSE_STELLA_HASH_TABLESpo) {
      return (stellaHashTableLookup(self->theStellaHashTable, wrapFloat(key)));
    }
    { cpp_hash_table* nativeTable = self->theHashTable;

      return (((Native_EQL_Hash_Table<double, Object*>*)nativeTable)->get(key));
    }
  }
}

void FloatHashTable::insertAt(double key, Object* value) {
  { FloatHashTable* self = this;

    if (oUSE_STELLA_HASH_TABLESpo) {
      stellaHashTableInsertAt(self->theStellaHashTable, wrapFloat(key), value);
      return;
    }
    { cpp_hash_table* nativeTable = self->theHashTable;

      (*((Native_EQL_Hash_Table<double, Object*>*)nativeTable))[key] = value;;
    }
  }
}

void FloatHashTable::removeAt(double key) {
  { FloatHashTable* self = this;

    if (oUSE_STELLA_HASH_TABLESpo) {
      stellaHashTableRemoveAt(self->theStellaHashTable, wrapFloat(key));
      return;
    }
    { cpp_hash_table* nativeTable = self->theHashTable;

      ((Native_EQL_Hash_Table<double, Object*>*)nativeTable)->erase(key);;
    }
  }
}

void StringHashTable::initializeHashTable() {
  // Insert a newly-created native hash table into `self'.
  { StringHashTable* self = this;

    if (oUSE_STELLA_HASH_TABLESpo) {
      self->theStellaHashTable = newStellaHashTable();
      return;
    }
    self->theHashTable = (cpp_hash_table*)(new Native_EQL_Hash_Table<const char*, Object*>);
  }
}

Object* StringHashTable::lookup(const char* key) {
  { StringHashTable* self = this;

    if (oUSE_STELLA_HASH_TABLESpo) {
      return (stellaStringHashTableLookup(self->theStellaHashTable, key));
    }
    { cpp_hash_table* nativeTable = self->theHashTable;

      return (((Native_EQL_Hash_Table<const char*, Object*>*)nativeTable)->get(key));
    }
  }
}

void StringHashTable::insertAt(const char* key, Object* value) {
  { StringHashTable* self = this;

    if (oUSE_STELLA_HASH_TABLESpo) {
      stellaHashTableInsertAt(self->theStellaHashTable, wrapString(key), value);
      return;
    }
    { cpp_hash_table* nativeTable = self->theHashTable;

      (*((Native_EQL_Hash_Table<const char*, Object*>*)nativeTable))[key] = value;;
    }
  }
}

void StringHashTable::removeAt(const char* key) {
  { StringHashTable* self = this;

    if (oUSE_STELLA_HASH_TABLESpo) {
      stellaHashTableRemoveAt(self->theStellaHashTable, wrapString(key));
      return;
    }
    { cpp_hash_table* nativeTable = self->theHashTable;

      ((Native_EQL_Hash_Table<const char*, Object*>*)nativeTable)->erase(key);;
    }
  }
}

void StringToIntegerHashTable::initializeHashTable() {
  // Insert a newly-created native hash table into `self'.
  { StringToIntegerHashTable* self = this;

    if (oUSE_STELLA_HASH_TABLESpo) {
      self->theStellaHashTable = newStellaHashTable();
      return;
    }
    self->theHashTable = (cpp_hash_table*)(new Native_EQL_Hash_Table<const char*, int>(NULL_INTEGER));
  }
}

int StringToIntegerHashTable::lookup(const char* key) {
  { StringToIntegerHashTable* self = this;

    if (oUSE_STELLA_HASH_TABLESpo) {
      return (unwrapInteger(((IntegerWrapper*)(stellaStringHashTableLookup(self->theStellaHashTable, key)))));
    }
    { cpp_hash_table* nativeTable = self->theHashTable;
      int result = NULL_INTEGER;

      result = ((Native_EQL_Hash_Table<const char*, int>*)nativeTable)->get(key);
      return (result);
    }
  }
}

void StringToIntegerHashTable::insertAt(const char* key, int value) {
  { StringToIntegerHashTable* self = this;

    if (oUSE_STELLA_HASH_TABLESpo) {
      stellaHashTableInsertAt(self->theStellaHashTable, wrapString(key), wrapInteger(value));
      return;
    }
    { cpp_hash_table* nativeTable = self->theHashTable;

      (*((Native_EQL_Hash_Table<const char*, int>*)nativeTable))[key] = value;;
    }
  }
}

void StringToIntegerHashTable::removeAt(const char* key) {
  { StringToIntegerHashTable* self = this;

    if (oUSE_STELLA_HASH_TABLESpo) {
      stellaHashTableRemoveAt(self->theStellaHashTable, wrapString(key));
      return;
    }
    { cpp_hash_table* nativeTable = self->theHashTable;

      ((Native_EQL_Hash_Table<const char*, int>*)nativeTable)->erase(key);;
    }
  }
}

// A table of 256 N-bit random numbers that can be used to
// hash sequences of bytes.  Each bit-column in the table has an approximately
// even number of 0's and 1's.
int* oHASH_BYTE_RANDOM_TABLEo = NULL;

// The most significant bit of a regular integer (FIXNUM
// in Common-Lisp).  In C++ and Java this corresponds to the sign bit, in
// Lisp this corresponds to the left-most bit of `CL:most-positive-fixnum'.
int oINTEGER_MSB_MASKo = 1 << (sizeof (int) / sizeof (char) * 8 - 1);

// Mask that covers all the unsigned bits of an integer.
int oINTEGER_UNSIGNED_BITS_MASKo = MOST_POSITIVE_INTEGER;

// The sign bit of a long integer.
long long int oLONG_INTEGER_MSB_MASKo = NULL_LONG_INTEGER;

// Mask that covers all the unsigned bits of a long integer.
long long int oLONG_INTEGER_UNSIGNED_BITS_MASKo = MOST_POSITIVE_LONG_INTEGER;

int hashmod(int code, int size) {
  // Map the hash code `code' onto a bucket index for a hash table
  // of `size' (i.e., onto the interval [0..size-1].  This is just like `rem' for
  // positive hash codes but also works for negative hash codes by mapping those
  // onto a positive number first.  Note, that the sign conversion mapping is not
  // equivalent to calling the `abs' function (it simply masks the sign bit for
  // speed) and therefore really only makes sense for hash codes.
  return ((((unsigned int) code) % size));
}

int rotateHashCode(int arg) {
  // Rotate `arg' to the right by 1 position.  This means shift `arg' to the right
  // by one and feed in `arg's bit zero from the left.  In Lisp the result will stay
  // in positive FIXNUM range.  In C++ and Java this might return a negative
  // value which might be equal to NULL-INTEGER.  Important: to make this inlinable,
  // it must be called with an atom (i.e., constant or variable) as its argument.
  // This function is primarily useful for hashing sequences of items where the hash
  // code should take the sequential order of elements into account (e.g., lists).
  return ((((arg & 1) == 0) ? ((unsigned int)arg >> 1) : (((arg >> 1)) | oINTEGER_MSB_MASKo)));
}

int objectHashCode(Object* self) {
  // Return a hash code for `self' (can be negative).  Two objects that are `eq?'
  // are guaranteed to generate the same hash code.  Two objects that are not `eq?'
  // do not necessarily generate different hash codes.  Similar to `hash-code' but
  // always hashes on the address of `self' even if it is a wrapper.
  return ((size_t)self);
}

int Object::hashCode() {
  // Return a hash code for `self' (can be negative).  Two objects that are `eql?'
  // are guaranteed to generate the same hash code.  Two objects that are not `eql?'
  // do not necessarily generate different hash codes.
  { Object* self = this;

    return ((size_t)self);
  }
}

int safeHashCode(Object* self) {
  // Return a hash code for `self'.  Just like `hash-code'
  // - which see, but also works for NULL.
  if (!((boolean)(self))) {
    return (63842277);
  }
  else {
    return (self->hashCode());
  }
}

int StandardObject::hashCode() {
  { StandardObject* self = this;

    return ((size_t)self);
  }
}

int Wrapper::hashCode() {
  { Wrapper* self = this;

    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "WRAPPER.hash-code: Don't know how to hash on " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

int StringWrapper::hashCode() {
  { StringWrapper* self = this;

    return (native_hash_string((self->wrapperValue)));
  }
}

int IntegerWrapper::hashCode() {
  { IntegerWrapper* self = this;

    return (self->wrapperValue);
  }
}

int LongIntegerWrapper::hashCode() {
  { LongIntegerWrapper* self = this;

    return (((int)(((((self->wrapperValue) ^ (((self->wrapperValue) >> 32)))) & (((long long int)(MOST_POSITIVE_INTEGER)))))));
  }
}

int FloatWrapper::hashCode() {
  { FloatWrapper* self = this;

    return ((size_t)(self->wrapperValue));
  }
}

int CharacterWrapper::hashCode() {
  { CharacterWrapper* self = this;

    return (((oHASH_BYTE_RANDOM_TABLEo[(int)(unsigned char) (self->wrapperValue)]) ^ 15119378));
  }
}

int BooleanWrapper::hashCode() {
  { BooleanWrapper* self = this;

    return ((self->wrapperValue ? 7333705 : 1891526));
  }
}

int stringHashCode(const char* self) {
  return (native_hash_string(self));
}

int integerHashCode(int self) {
  return (self);
}

int longIntegerHashCode(long long int self) {
  return (((int)((((self ^ ((self >> 32)))) & (((long long int)(MOST_POSITIVE_INTEGER)))))));
}

int floatHashCode(double self) {
  return ((size_t)self);
}

int characterHashCode(char self) {
  return (((oHASH_BYTE_RANDOM_TABLEo[(int)(unsigned char) self]) ^ 15119378));
}

int Object::equalHashCode() {
  // Return a hash code for `self' (can be negative).  Two objects that are `equal?'
  // are guaranteed to generate the same hash code (provided, that writers of
  // `object-equal?' methods also implemented the appropriate `equal-hash-code'
  // method).  Two objects that are not `equal?'do not necessarily generate different
  // hash codes.
  { Object* self = this;

    return (self->hashCode());
  }
}

int safeEqualHashCode(Object* self) {
  // Return a hash code for `self'.  Just like `equal-hash-code'
  // - which see, but also works for NULL.  `equal-hash-code' methods that expect to
  // handle NULL components should use this function for recursive calls.
  if (!((boolean)(self))) {
    return (16569644);
  }
  else {
    return (self->equalHashCode());
  }
}

int hashString(const char* string, int seedcode) {
  // Generate a hash-code for `string' and return it.
  // Two strings that are equal but not eq will generate the same code.
  // The hash-code is based on `seedCode' which usually will be 0.  However,
  // `seedCode' can also be used to supply the result of a previous hash
  // operation to achieve hashing on sequences of strings without actually
  // having to concatenate them.
  { int code = seedcode;
    int cursor = strlen(string);

    if (cursor == 0) {
      return (4303803);
    }
    else {
      cursor = cursor - 1;
    }
    for (;;) {
      code = (code ^ (oHASH_BYTE_RANDOM_TABLEo[(int)(unsigned char) (string[cursor])]));
      if (cursor == 0) {
        break;
      }
      else {
        cursor = cursor - 1;
      }
      code = (((code & 1) == 0) ? ((unsigned int)code >> 1) : (((code >> 1)) | oINTEGER_MSB_MASKo));
    }
    return (code);
  }
}

// List of prime numbers approximately growing by a factor of 2
// that are suitable to be used as hash table sizes.  This is in string
// format to enable processing by Lisps with different fixnum sizes.
Vector* oHASH_TABLE_SIZE_PRIME_STRINGSo = NULL;

// List of prime numbers approximately growing by a factor of 2
// that are suitable to be used as hash table sizes.
Vector* oHASH_TABLE_SIZE_PRIMESo = NULL;

int pickHashTableSizePrime(int minsize) {
  // Return a hash table prime of at least `minSize'.
  { IntegerWrapper* prime = NULL;
    Vector* vector000 = oHASH_TABLE_SIZE_PRIMESo;
    int index000 = 0;
    int length000 = vector000->length();

    for  (; index000 < length000; 
          index000 = index000 + 1) {
      prime = ((IntegerWrapper*)((vector000->theArray)[index000]));
      if (prime->wrapperValue >= minsize) {
        return (prime->wrapperValue);
      }
    }
  }
  throw *newStellaException("pick-hash-table-size-prime: minimum size is too large");
}

void Vector::initializeVector() {
  { Vector* self = this;

    { int size = self->arraySize;

      self->theArray = new (GC) Object*[size];
      { Object** array = self->theArray;

        { int i = NULL_INTEGER;
          int iter000 = 0;
          int upperBound000 = size - 1;

          for  (; iter000 <= upperBound000; 
                iter000 = iter000 + 1) {
            i = iter000;
            array[i] = NULL;
          }
        }
      }
    }
  }
}

void resizeVector(Vector* self, int size) {
  // Change the size of `self' to `size'.  If `size' is smaller
  // than the current size of `self' the vector will be truncated.  Otherwise, 
  // the internal array of `self' will be grown to `size' and unused elements
  // will be initialized to NULL.
  { int old_size = self->arraySize;
    int i = old_size;
    Object** old_array = self->theArray;
    Object** new_array = old_array;

    if (size == old_size) {
      return;
    }
    new_array = new (GC) Object*[size];
    if (size < old_size) {
      old_size = size;
      i = old_size;
    }
    while ((i = i - 1) >= 0) {
      new_array[i] = (old_array[i]);
    }
    { int i = NULL_INTEGER;
      int iter000 = old_size;
      int upperBound000 = size - 1;

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        i = iter000;
        new_array[i] = NULL;
      }
    }
    self->theArray = new_array;
    self->arraySize = size;
  }
}

Object* nativeVectorNth(Object** self, int position) {
  // Return the element in `self' at `position'.
  return (self[position]);
}

Object* nativeVectorNthSetter(Object** self, Object* value, int position) {
  // Set the element in `self' at `position' to `value'.
  return (self[position] = value);
}

void unmake(Object* self) {
  self = self;
}

# include <dirent.h>
boolean nativeProbeDirectoryP(const char* filename) {
  // Return true if file `fileName' exists and is a directory.
  // Note that this does not necessarily mean that the directory can also be read.
  // This does not handle any necessary pathname translations or error conditions.
  { boolean result = false;

    DIR *dirptr;
         dirptr = opendir(filename);
         if (dirptr != NULL) {
            result=true;
            closedir(dirptr);
         };
    return (result);
  }
}

boolean probeFileP(const char* filename) {
  // Return true if file `fileName' exists.  Note that this does
  // not necessarily mean that the file can also be read.
  // IMPORTANT Java idiosyncrasy: if file `foo/bar' exists and is not a directory,
  // Java will also say `foo/bar/' exists, which is different behavior than in Lisp
  // and C++.  For this reason, make sure to always use `probe-directory?' to test
  // whether a directory exists.
  return (nativeProbeFileP(translateLogicalPathname(filename)));
}

boolean probeDirectoryP(const char* filename) {
  // Return true if file `fileName' exists and is a directory.
  // Note that this does not necessarily mean that the directory can also be read.
  return (nativeProbeDirectoryP(translateLogicalPathname(filename)));
}

CalendarDate* fileWriteDate(const char* filename) {
  // Return the time at which file `fileName' was last modified or
  // NULL if that cannot be determined.
  { const char* truefile = translateLogicalPathname(filename);

    if (!(nativeProbeFileP(truefile))) {
      ensureFileExists(filename, "file-write-date");
    }
    return (nativeFileWriteDate(truefile));
  }
}

long long int fileLength(const char* filename) {
  // Return the length of file `fileName' in bytes or NULL if that
  // cannot be determined.
  { const char* truefile = translateLogicalPathname(filename);

    if (!(nativeProbeFileP(truefile))) {
      ensureFileExists(filename, "file-length");
    }
    return (nativeFileLength(truefile));
  }
}

void deleteFile(const char* filename) {
  // Delete the file `fileName'.
  { const char* truefile = translateLogicalPathname(filename);

    if (!(nativeProbeFileP(truefile))) {
      ensureFileExists(filename, "delete-file");
    }
    nativeDeleteFile(truefile);
  }
}

void renameFile(const char* fromfile, const char* tofile) {
  // Rename the file `fromFile' to `toFile'.
  { const char* truefrom = translateLogicalPathname(fromfile);
    const char* trueto = translateLogicalPathname(tofile);

    if (!(nativeProbeFileP(truefrom))) {
      ensureFileExists(fromfile, "rename-file");
    }
    if (nativeProbeFileP(trueto)) {
      ensureFileDoesNotExist(tofile, "rename-file");
    }
    nativeRenameFile(truefrom, trueto);
  }
}

void copyStreamToStream(InputStream* in, OutputStream* out) {
  // Copy `in' verbatimely to `out'.  Does the right thing for binary data.
  { char* buffer = new (PointerFreeGC) char[oTOKENIZER_INITIAL_BUFFER_SIZEo];
    int bytesread = 0;

    for (;;) {
      bytesread = nativeByteArrayReadSequence(buffer, in->nativeStream, 0, oTOKENIZER_INITIAL_BUFFER_SIZEo);
      if (bytesread > 0) {
        nativeByteArrayWriteSequence(buffer, out->nativeStream, 0, bytesread);
      }
      else {
        flushOutput(out);
        break;
      }
    }
  }
}

void copyFile(const char* fromfile, const char* tofile) {
  // Copy file `fromFile' to file `toFile', clobbering
  // any data already in `toFile'.
  ensureFileExists(fromfile, "copy-file");
  { InputFileStream* from = NULL;

    try {
      from = openInputFile(fromfile, 0);
      { OutputFileStream* to = NULL;

        try {
          to = openOutputFile(tofile, 0);
          copyStreamToStream(from, to);
        }
catch (...) {
          if (((boolean)(to))) {
            to->free();
          }
          throw;
        }
        if (((boolean)(to))) {
          to->free();
        }
      }
    }
catch (...) {
      if (((boolean)(from))) {
        from->free();
      }
      throw;
    }
    if (((boolean)(from))) {
      from->free();
    }
  }
}

const char* getTempDirectory() {
  // Return a suitable directory for temporary files.
  // Uses the value of `stella.tempDirectory' if defined; otherwise, it
  // will use a suitable OS-specific default.  The returned directory will
  // end in a separator for immediate concatenation with a physical filename.
  { Object* dir = getProperty(wrapString("stella.tempDirectory"), NIL);

    if (!((boolean)(dir))) {
      { Keyword* testValue000 = operatingSystem();

        if ((testValue000 == KWD_PRIMAL_UNIX) ||
            (testValue000 == KWD_PRIMAL_MAC)) {
          dir = wrapString("/tmp/");
        }
        else if (testValue000 == KWD_PRIMAL_WINDOWS) {
          dir = wrapString("C:\\WINDOWS\\TEMP\\");
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
        }
      }
    }
    else {
      dir = wrapString(fileNameAsDirectory(((StringWrapper*)(dir))->wrapperValue));
    }
    return (((StringWrapper*)(dir))->wrapperValue);
  }
}

const char* makeTemporaryFileName(const char* prefix, const char* suffix) {
  // Return a file name of the form `<prefix>NNNNNN<suffix>'
  // which is guaranteed to not refer to any existing file.  A null `prefix'
  // defaults to `tmpfile', a null `suffix' defaults to the empty string.
  // The number portion NNNNNN will correpond to a random number between 0
  // and 999999.  If no qualifying filename can be found after 100 attempts,
  // NULL will be returned.  Note that it is possible due to multi-threading
  // or processing that the generated filename becomes used by another thread
  // or OS process.  If necessary, this case can be handled by the caller.
  if (prefix == NULL) {
    prefix = "tmpfile";
  }
  if (suffix == NULL) {
    suffix = "";
  }
  { int i = NULL_INTEGER;
    int iter000 = 0;
    int upperBound000 = 100;

    for  (; iter000 <= upperBound000; 
          iter000 = iter000 + 1) {
      i = iter000;
      i = i;
      { const char* uniquifier = formatWithPadding(integerToString(((long long int)(stella::random(1000000)))), 6, '0', KWD_PRIMAL_RIGHT, false);
        const char* tempfilename = stringConcatenate(prefix, uniquifier, 1, suffix);

        if (!probeFileP(tempfilename)) {
          return (tempfilename);
        }
      }
    }
  }
  return (NULL);
}

const char* makeTemporaryFile(const char* prefix, const char* suffix) {
  // Variant of `make-temporary-file-name' that actually
  // allocates the file to prevent other processes from using that name.
  // This is still not fully thread safe - for that we would need a file lock -
  // but maybe a bit better in avoiding collisions.
  { int i = NULL_INTEGER;
    int iter000 = 0;
    int upperBound000 = 100;

    for  (; iter000 <= upperBound000; 
          iter000 = iter000 + 1) {
      i = iter000;
      i = i;
      try {
        { const char* tempfilename = makeTemporaryFileName(prefix, suffix);

          { OutputFileStream* temp = NULL;

            try {
              temp = openOutputFile(tempfilename, 2, KWD_PRIMAL_IF_EXISTS, KWD_PRIMAL_ERROR);
              closeStream(temp);
            }
catch (...) {
              if (((boolean)(temp))) {
                temp->free();
              }
              throw;
            }
            if (((boolean)(temp))) {
              temp->free();
            }
          }
          return (tempfilename);
        }
      }
      catch (std::exception ) {
      }
    }
  }
  return (NULL);
}

Cons* clListDirectoryFiles(const char* directory) {
  { Cons* files = NULL;
    const char* dirsep = directorySeparatorString();
    boolean checkduplicatesP = false;
    const char* normfile = NULL;
    Cons* normalizedfiles = NIL;

    if (!((boolean)(files))) {
      checkduplicatesP = true;
    }
    files = NIL;
    if (checkduplicatesP) {
      normalizedfiles = normalizedfiles->removeDuplicatesEqual();
    }
    { StringWrapper* file = NULL;
      Cons* iter000 = files;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        file = ((StringWrapper*)(iter000->value));
        normfile = file->wrapperValue;
        if (endsWithP(normfile, dirsep, NULL_INTEGER)) {
          normfile = stringSubsequence(normfile, 0, strlen(normfile) - strlen(dirsep));
        }
        normfile = fileNameWithoutDirectory(normfile);
        if (stringEqlP(normfile, ".") ||
            stringEqlP(normfile, "..")) {
          continue;
        }
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(wrapString(normfile), NIL);
            if (normalizedfiles == NIL) {
              normalizedfiles = collect000;
            }
            else {
              addConsToEndOfConsList(normalizedfiles, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(wrapString(normfile), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    return (normalizedfiles);
  }
}

# include <dirent.h>
Cons* cppListDirectoryFiles(const char* directory) {
  { Cons* files = NIL;

    DIR *dirptr;
       struct dirent *entry;
       dirptr = opendir(directory);
       if (dirptr != NULL) {
          while (entry = readdir(dirptr)) {
            const char* filename = entry->d_name;
            // skip . and ..:
            if (!strcmp(filename, ".") || !strcmp(filename, ".."))
               continue;
            // do this to copy out the string:
            filename = stringConcatenate(filename, "");
            files = cons(wrapString(filename), files);
          }
          closedir(dirptr);
         }
         else
            files = NULL;
    if (!((boolean)(files))) {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "list-directory-files: error reading " << "`" << directory << "'";
        throw *newStellaException(stream000->theStringReader());
      }
    }
    return (files);
  }
}

Cons* javaListDirectoryFiles(const char* directory) {
  { Cons* files = NIL;

    return (files);
  }
}

Cons* listDirectoryFiles(const char* directory) {
  // Return all the files and sub-directories in `directory' sorted by name.
  // Each returned file is a bare file name without a `directory' component.  If a file is
  // a directory, it will look just like a plain file.  This means consumers might have to
  // explicitly test whether a file is a directory depending on what they do. Excludes . and ..
  // directories.  Handles logical pathnames but resulting files will always use physical pathname
  // syntax.  This is mostly consistent across native languages, but some differences still exist -
  // e.g., Lisp will convert . or .. into absolute pathnames.
  directory = translateLogicalPathname(fileNameAsDirectory(directory));
  ensureFileExists(directory, "list-directory-files");
  { Cons* files = cppListDirectoryFiles(directory);

    return (files->sort(NULL));
  }
}

Cons* listDirectoryFilesEvaluatorWrapper(Cons* arguments) {
  return (listDirectoryFiles(((StringWrapper*)(arguments->value))->wrapperValue));
}

Cons* listDirectoryFilesRecursively(const char* directory) {
  // Just like `list-directory-files' (which see) but also recurses into
  // subdirectories.  Files at the top level of `directory' will be bare file names without
  // a `directory' component.  Files in subdirectories will be prefixed with the relative
  // subdirectory path starting right below `directory'.  The sort order is lexicographic
  // within directories which results in a depth-first presentation order of files.
  directory = translateLogicalPathname(fileNameAsDirectory(directory));
  ensureFileExists(directory, "list-directory-files");
  { Cons* files = NIL;

    { StringWrapper* file = NULL;
      Cons* iter000 = listDirectoryFiles(directory);

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        file = ((StringWrapper*)(iter000->value));
        if (probeDirectoryP(stringConcatenate(directory, file->wrapperValue, 0))) {
          file = wrapString(fileNameAsDirectory(file->wrapperValue));
          { StringWrapper* subfile = NULL;
            Cons* iter001 = listDirectoryFilesRecursively(stringConcatenate(directory, file->wrapperValue, 0));

            for (; !(iter001 == NIL); iter001 = iter001->rest) {
              subfile = ((StringWrapper*)(iter001->value));
              files = cons(wrapString(stringConcatenate(unwrapString(file), subfile->wrapperValue, 0)), files);
            }
          }
        }
        else {
          files = cons(file, files);
        }
      }
    }
    return (files->reverse());
  }
}

Cons* listDirectoryFilesRecursivelyEvaluatorWrapper(Cons* arguments) {
  return (listDirectoryFilesRecursively(((StringWrapper*)(arguments->value))->wrapperValue));
}

void cppCreateDirectory(const char* directory) {
  directory = translateLogicalPathname(fileNameAsDirectory(directory));
  if (!(probeDirectoryP(directory))) {
    if (!((!(((int)(mkdir(directory, 0777))))))) {
      throw *newInputOutputException(stringConcatenate("failed to create directory: ", directory, 0));
    }
  }
}

void createDirectories(const char* directory) {
  // If `directory' does not yet exist, create it and any of its parents
  // that do not yet exist.  If `directory' already does exist, this simply is a no-op.
  directory = translateLogicalPathname(fileNameAsDirectory(directory));
  if (!(probeDirectoryP(directory))) {
    try {
      { const char* parent = directoryParentDirectory(directory, 1);

        if (!(probeDirectoryP(parent))) {
          createDirectories(parent);
        }
        cppCreateDirectory(directory);
      }
    }
    catch (InputOutputException& _e) {
      InputOutputException* e = &_e;

      throw *e;
    }
    catch (std::exception& _e) {
      std::exception* e = &_e;

      throw *newInputOutputException(stringConcatenate("create-directories: ", exceptionMessage(e), 0));
    }
  }
}

void createDirectoriesEvaluatorWrapper(Cons* arguments) {
  createDirectories(((StringWrapper*)(arguments->value))->wrapperValue);
}

void ensureDirectoriesExist(const char* filename) {
  // Ensure all physical directories in the directory portion of `fileName' exist.
  { const char* directory = fileNameDirectory(translateLogicalPathname(filename));

    if (!(blankStringP(directory))) {
      createDirectories(directory);
    }
  }
}

void ensureDirectoriesExistEvaluatorWrapper(Cons* arguments) {
  ensureDirectoriesExist(((StringWrapper*)(arguments->value))->wrapperValue);
}

int integerLognot(int arg) {
  return ((~ arg));
}

long long int longIntegerLognot(long long int arg) {
  return ((~ arg));
}

int integerLogand(int arg1, int arg2) {
  return ((arg1 & arg2));
}

long long int longIntegerLogand(long long int arg1, long long int arg2) {
  return ((arg1 & arg2));
}

int integerLogor(int arg1, int arg2) {
  return ((arg1 | arg2));
}

long long int longIntegerLogor(long long int arg1, long long int arg2) {
  return ((arg1 | arg2));
}

int integerLogxor(int arg1, int arg2) {
  return ((arg1 ^ arg2));
}

long long int longIntegerLogxor(long long int arg1, long long int arg2) {
  return ((arg1 ^ arg2));
}

// The number of bits in a long integer.
int LONG_INTEGER_BIT_WIDTH = NULL_INTEGER;

int integerLength(long long int x) {
  // Return the 1-based position of the left-most bit in `x'.
  // If `x' is negative, we only count the value bits, not the sign.
  if (x < 0) {
    x = -1 - x;
  }
  if (x == 0) {
    return (0);
  }
  { int bot = 0;
    int top = LONG_INTEGER_BIT_WIDTH - 1;
    int split = 0;
    long long int rem = 0l;

    for (;;) {
      split = ((bot + top) >> 1);
      rem = (x >> split);
      if (rem == 1) {
        return (split + 1);
      }
      if (rem == 0) {
        top = split - 1;
      }
      else {
        bot = split + 1;
      }
    }
  }
}

int integerLength10(long long int x) {
  // Return the 1-based position of the left-most non-zero digit
  // in the base-10 representation of `x'.  If `x' is negative, we only consider
  // its absolute value, not the sign.  This effectively computes the minimum number
  // of base-10 digits to represent `x', with the exception of x=0.
  if (x < 0) {
    x = ((x < 0) ? (0 - x) : x);
  }
  { int len = 0;
    int comp = 1;

    for (;;) {
      if (x >= 1000000000l) {
        x = (x / 1000000000l);
        len = len + 9;
      }
      else if (x >= 10000) {
        x = (x / (10000l));
        len = len + 4;
      }
      else if (x >= 100) {
        x = (x / (100l));
        len = len + 2;
      }
      else {
        break;
      }
    }
    while (comp <= x) {
      comp = comp * 10;
      len = len + 1;
    }
    return (len);
  }
}

int integerShiftLeft(int arg, int count) {
  return ((arg << count));
}

long long int longIntegerShiftLeft(long long int arg, int count) {
  return ((arg << count));
}

int integerShiftRight(int arg, int count) {
  // Shift `arg' to the right by `count' positions and
  // 0-extend from the left if `arg' is positive or 1-extend if it is
  // negative.  This is an arithmetic shift that preserve the sign of `arg'
  // and is equivalent to dividing `arg' by 2** `count'.
  return ((arg >> count));
}

long long int longIntegerShiftRight(long long int arg, int count) {
  // Shift `arg' to the right by `count' positions and
  // 0-extend from the left if `arg' is positive or 1-extend if it is
  // negative.  This is an arithmetic shift that preserve the sign of `arg'
  // and is equivalent to dividing `arg' by 2** `count'.
  return ((arg >> count));
}

int integerUnsignedShiftRightBy1(int arg) {
  // Shift `arg' to the right by 1 position and 0-extend
  // from the left.  This does not preserve the sign of `arg' and shifts
  // the sign-bit just like a regular bit.  In Common-Lisp we can't do that
  // directly and need to do some extra masking.
  return (((unsigned int)arg >> 1));
}

long long int longIntegerUnsignedShiftRightBy1(long long int arg) {
  // Shift `arg' to the right by 1 position and 0-extend
  // from the left.  This does not preserve the sign of `arg' and shifts
  // the sign-bit just like a regular bit.  In Common-Lisp we can't do that
  // directly and need to do some extra masking.
  return (((unsigned long long int)arg >> 1));
}

const char* generateUuid(Keyword* uuidType) {
  // Generates a UUID of the specified type.  Legal types are
  // a subset of the IETF RFC 4122 (see http://www.ietf.org/rfc/rfc4122.txt )
  // UUID types.  Currently supported are:
  //     :TYPE-4  :RANDOM       A type-4 (random) UUID.  These are synonyms.
  if ((uuidType == KWD_PRIMAL_TYPE_4) ||
      (uuidType == KWD_PRIMAL_RANDOM)) {
    return (generateRandomUuid());
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "UUIDs of type " << "`" << uuidType << "'" << " are not supported.";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

const char* generateRandomUuid() {
  // Generates a random UUID (Type 4), according to the guidelines
  // of IETF RFC 4122 (see http://www.ietf.org/rfc/rfc4122.txt )
  // 
  // Take 16 random bytes (octets), put them all behind each other, for the description
  // the numbering starts with byte 1 (most significant, first) to byte 16 
  //    (least significant, last). Then put in the version and variant.
  // To put in the version, take the 7th byte and perform an and operation using 0x0f,
  //    followed by an or operation with 0x40. 
  // To put in the variant, take the 9th byte and perform an and operation using 0x3f,
  //    followed by an or operation with 0x80.
  // To make the string representation, take the hexadecimal presentation of bytes 1-4
  //    (without 0x in front of it) let them follow by a -, then take bytes 5 and 6, - 
  // bytes 7 and 8, - bytes 9 and 10, - then followed by bytes 11-16.
  return (stringConcatenate(zeroPadString(integerToHexString(((long long int)(stella::random(65536)))), 4), zeroPadString(integerToHexString(((long long int)(stella::random(65536)))), 4), 9, "-", zeroPadString(integerToHexString(((long long int)(stella::random(65536)))), 4), "-", integerToHexString(((long long int)(16384 + stella::random(4096)))), "-", integerToHexString(((long long int)(32768 + stella::random(16384)))), "-", zeroPadString(integerToHexString(((long long int)(stella::random(16777216)))), 6), zeroPadString(integerToHexString(((long long int)(stella::random(16777216)))), 6)));
}

Object* stellify(Object* self) {
  // Convert a Lisp object into a STELLA object.
  { Object* result = self;

    return (result);
  }
}

boolean stellaObjectP(Object* self) {
  // Return true if `self' is a member of the STELLA class `OBJECT'.
  { boolean resultP = true;

    return (resultP);
  }
}

boolean runningAsLispP() {
  // Return true if the executable code is a Common Lisp application.
  { boolean resultP = false;

    return (resultP);
  }
}

Keyword* runningInLanguage() {
  // Returns the keyword for the language the current implementation is running in.
  return (internKeyword("CPP"));
}

const char* runningSystemInformation() {
  // Returns an information string about the current running system environment.
  { const char* info = "";

    return (info);
  }
}

const char* getenv(const char* varname, Cons* deflt) {
  // Return the value of the OS environment variable `varname'.  If it is not defined
  // or if its value is the empty string and a `deflt' is provided, return the default value instead.
  { const char* undefined = NULL;
    const char* value = ::getenv(varname);

    if ((value == NULL) ||
        stringEqlP(value, "")) {
      { const char* def = NULL;
        Cons* iter000 = deflt;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          def = ((StringWrapper*)(iter000->value))->wrapperValue;
          return (def);
        }
      }
    }
    return (value);
  }
}

StringWrapper* getenvEvaluatorWrapper(Cons* arguments) {
  { const char* result = getenv(((StringWrapper*)(arguments->value))->wrapperValue, arguments->rest);

    if (result != NULL) {
      return (wrapString(result));
    }
    else {
      return (NULL);
    }
  }
}

void sleep(double seconds) {
  // The program will sleep for the indicated number of seconds.
  // Fractional values are allowed, but the results are implementation dependent:
  // Common Lisp uses the fractions natively, Java with a resolution of 0.001,
  // and C++ can only use integral values.
  sleep((unsigned int)seconds);
}

const char* exceptionMessage(std::exception* e) {
  // Accesses the error message of the exception `e'.
  return ((const char*)e->what());
}

void printExceptionContext(std::exception* e, OutputStream* stream) {
  // Prints system dependent information about the context of the specified
  // exception `e'.  For example, in Java it prints a stack trace.  In Lisp, it is vendor dependent.
  { std::ostream* s = stream->nativeStream;

    *(stream->nativeStream) << "No exception context available" << std::endl;
  }
}

const char* exceptionContext(std::exception* e) {
  // Print the exception context of `e' to a string and return the result.
  { OutputStringStream* out = newOutputStringStream();

    printExceptionContext(e, out);
    return (out->theStringReader());
  }
}

void* makeProcessLock() {
  return (NULL);
}

// Process lock object for bootstrap use.
void* oBOOTSTRAP_LOCKo = NULL;

void helpStartupPrimal1() {
  {
    KWD_PRIMAL_IF_NOT_EXISTS = ((Keyword*)(internRigidSymbolWrtModule("IF-NOT-EXISTS", NULL, 2)));
    KWD_PRIMAL_ABORT = ((Keyword*)(internRigidSymbolWrtModule("ABORT", NULL, 2)));
    SYM_PRIMAL_STELLA_FLOOR = ((Symbol*)(internRigidSymbolWrtModule("FLOOR", NULL, 0)));
    KWD_PRIMAL_CPP = ((Keyword*)(internRigidSymbolWrtModule("CPP", NULL, 2)));
    KWD_PRIMAL_FUNCTION = ((Keyword*)(internRigidSymbolWrtModule("FUNCTION", NULL, 2)));
    SYM_PRIMAL_STELLA_ROUND = ((Symbol*)(internRigidSymbolWrtModule("ROUND", NULL, 0)));
    SYM_PRIMAL_STELLA_FMOD = ((Symbol*)(internRigidSymbolWrtModule("FMOD", NULL, 0)));
    SYM_PRIMAL_STELLA_RANDOM = ((Symbol*)(internRigidSymbolWrtModule("RANDOM", NULL, 0)));
    SYM_PRIMAL_STELLA_SQRT = ((Symbol*)(internRigidSymbolWrtModule("SQRT", NULL, 0)));
    SYM_PRIMAL_STELLA_COS = ((Symbol*)(internRigidSymbolWrtModule("COS", NULL, 0)));
    SYM_PRIMAL_STELLA_SIN = ((Symbol*)(internRigidSymbolWrtModule("SIN", NULL, 0)));
    SYM_PRIMAL_STELLA_TAN = ((Symbol*)(internRigidSymbolWrtModule("TAN", NULL, 0)));
    SYM_PRIMAL_STELLA_ACOS = ((Symbol*)(internRigidSymbolWrtModule("ACOS", NULL, 0)));
    SYM_PRIMAL_STELLA_ASIN = ((Symbol*)(internRigidSymbolWrtModule("ASIN", NULL, 0)));
    SYM_PRIMAL_STELLA_ATAN = ((Symbol*)(internRigidSymbolWrtModule("ATAN", NULL, 0)));
    SYM_PRIMAL_STELLA_ATAN2 = ((Symbol*)(internRigidSymbolWrtModule("ATAN2", NULL, 0)));
    SYM_PRIMAL_STELLA_EXP = ((Symbol*)(internRigidSymbolWrtModule("EXP", NULL, 0)));
    SYM_PRIMAL_STELLA_LOG = ((Symbol*)(internRigidSymbolWrtModule("LOG", NULL, 0)));
    SYM_PRIMAL_STELLA_MIN = ((Symbol*)(internRigidSymbolWrtModule("MIN", NULL, 0)));
    SYM_PRIMAL_STELLA_MAX = ((Symbol*)(internRigidSymbolWrtModule("MAX", NULL, 0)));
    KWD_PRIMAL_WHITE_SPACE = ((Keyword*)(internRigidSymbolWrtModule("WHITE-SPACE", NULL, 2)));
    KWD_PRIMAL_ASCII_CASE_SENSITIVE = ((Keyword*)(internRigidSymbolWrtModule("ASCII-CASE-SENSITIVE", NULL, 2)));
    KWD_PRIMAL_ASCII_CASE_INSENSITIVE = ((Keyword*)(internRigidSymbolWrtModule("ASCII-CASE-INSENSITIVE", NULL, 2)));
    KWD_PRIMAL_ASCII_CASE_NORMALIZED = ((Keyword*)(internRigidSymbolWrtModule("ASCII-CASE-NORMALIZED", NULL, 2)));
    KWD_PRIMAL_UPCASE = ((Keyword*)(internRigidSymbolWrtModule("UPCASE", NULL, 2)));
    KWD_PRIMAL_DOWNCASE = ((Keyword*)(internRigidSymbolWrtModule("DOWNCASE", NULL, 2)));
    KWD_PRIMAL_CAPITALIZE = ((Keyword*)(internRigidSymbolWrtModule("CAPITALIZE", NULL, 2)));
    KWD_PRIMAL_PRESERVE = ((Keyword*)(internRigidSymbolWrtModule("PRESERVE", NULL, 2)));
    KWD_PRIMAL_LEFT = ((Keyword*)(internRigidSymbolWrtModule("LEFT", NULL, 2)));
    KWD_PRIMAL_RIGHT = ((Keyword*)(internRigidSymbolWrtModule("RIGHT", NULL, 2)));
    KWD_PRIMAL_CENTER = ((Keyword*)(internRigidSymbolWrtModule("CENTER", NULL, 2)));
    SYM_PRIMAL_STELLA_HASH_CODE = ((Symbol*)(internRigidSymbolWrtModule("HASH-CODE", NULL, 0)));
    KWD_PRIMAL_JAVA = ((Keyword*)(internRigidSymbolWrtModule("JAVA", NULL, 2)));
    KWD_PRIMAL_UNIX = ((Keyword*)(internRigidSymbolWrtModule("UNIX", NULL, 2)));
    KWD_PRIMAL_MAC = ((Keyword*)(internRigidSymbolWrtModule("MAC", NULL, 2)));
    KWD_PRIMAL_WINDOWS = ((Keyword*)(internRigidSymbolWrtModule("WINDOWS", NULL, 2)));
    KWD_PRIMAL_IF_EXISTS = ((Keyword*)(internRigidSymbolWrtModule("IF-EXISTS", NULL, 2)));
    KWD_PRIMAL_ERROR = ((Keyword*)(internRigidSymbolWrtModule("ERROR", NULL, 2)));
    KWD_PRIMAL_TYPE_4 = ((Keyword*)(internRigidSymbolWrtModule("TYPE-4", NULL, 2)));
    KWD_PRIMAL_RANDOM = ((Keyword*)(internRigidSymbolWrtModule("RANDOM", NULL, 2)));
    SYM_PRIMAL_STELLA_SLEEP = ((Symbol*)(internRigidSymbolWrtModule("SLEEP", NULL, 0)));
    SYM_PRIMAL_STELLA_STARTUP_PRIMAL = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-PRIMAL", NULL, 0)));
    SYM_PRIMAL_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
  }
}

void helpStartupPrimal2() {
  {
    defineFunctionObject("LISP-NULL-ARRAY-SYMBOL-STRING", "(DEFUN (LISP-NULL-ARRAY-SYMBOL-STRING STRING) ((RANK INTEGER)))", ((cpp_function_code)(&lispNullArraySymbolString)), NULL);
    defineFunctionObject("PRINT-NUMERIC-CONSTANTS", "(DEFUN PRINT-NUMERIC-CONSTANTS () :COMMAND? TRUE)", ((cpp_function_code)(&printNumericConstants)), NULL);
    defineMethodObject("(DEFMETHOD (NULL? BOOLEAN) ((X UNKNOWN)) :DOCUMENTATION \"Return true if `x' is undefined (handled specially by all translators).\" :PUBLIC? TRUE :NATIVE? TRUE)", NULL, NULL);
    defineMethodObject("(DEFMETHOD (NULL? BOOLEAN) ((X OBJECT)) :DOCUMENTATION \"Return true if `x' is undefined (handled specially by all translators).\" :PUBLIC? TRUE :NATIVE? TRUE)", NULL, NULL);
    defineMethodObject("(DEFMETHOD (NULL? BOOLEAN) ((X SECOND-CLASS-OBJECT)) :DOCUMENTATION \"Return true if `x' is undefined (handled specially by all translators).\" :PUBLIC? TRUE :NATIVE? TRUE)", NULL, NULL);
    defineMethodObject("(DEFMETHOD (NULL? BOOLEAN) ((X NATIVE-VECTOR)) :DOCUMENTATION \"Return true if `x' is undefined (handled specially by all translators).\" :PUBLIC? TRUE :NATIVE? TRUE)", NULL, NULL);
    defineMethodObject("(DEFMETHOD (NULL? BOOLEAN) ((X ARRAY)) :DOCUMENTATION \"Return true if `x' is undefined (handled specially by all translators).\" :PUBLIC? TRUE :NATIVE? TRUE)", NULL, NULL);
    defineMethodObject("(DEFMETHOD (NULL? BOOLEAN) ((X STRING)) :DOCUMENTATION \"Return true if `x' is undefined (handled specially by all translators).\" :PUBLIC? TRUE :NATIVE? TRUE)", NULL, NULL);
    defineMethodObject("(DEFMETHOD (NULL? BOOLEAN) ((X MUTABLE-STRING)) :DOCUMENTATION \"Return true if `x' is undefined (handled specially by all translators).\" :PUBLIC? TRUE :NATIVE? TRUE)", NULL, NULL);
    defineMethodObject("(DEFMETHOD (NULL? BOOLEAN) ((X CHARACTER)) :DOCUMENTATION \"Return true if `x' is undefined (handled specially by all translators).\" :PUBLIC? TRUE :NATIVE? TRUE)", NULL, NULL);
    defineMethodObject("(DEFMETHOD (NULL? BOOLEAN) ((X CODE)) :DOCUMENTATION \"Return true if `x' is undefined (handled specially by all translators).\" :PUBLIC? TRUE :NATIVE? TRUE)", NULL, NULL);
    defineMethodObject("(DEFMETHOD (NULL? BOOLEAN) ((X INTEGER)) :DOCUMENTATION \"Return true if `x' is undefined (handled specially by all translators).\" :PUBLIC? TRUE :NATIVE? TRUE)", NULL, NULL);
    defineMethodObject("(DEFMETHOD (NULL? BOOLEAN) ((X LONG-INTEGER)) :DOCUMENTATION \"Return true if `x' is undefined (handled specially by all translators).\" :PUBLIC? TRUE :NATIVE? TRUE)", NULL, NULL);
    defineMethodObject("(DEFMETHOD (NULL? BOOLEAN) ((X FLOAT)) :DOCUMENTATION \"Return true if `x' is undefined (handled specially by all translators).\" :PUBLIC? TRUE :NATIVE? TRUE)", NULL, NULL);
    defineMethodObject("(DEFMETHOD (DEFINED? BOOLEAN) ((X UNKNOWN)) :DOCUMENTATION \"Return true if `x' is defined (handled specially by all translators).\" :PUBLIC? TRUE :NATIVE? TRUE)", NULL, NULL);
    defineMethodObject("(DEFMETHOD (DEFINED? BOOLEAN) ((X OBJECT)) :DOCUMENTATION \"Return true if `x' is defined (handled specially by all translators).\" :PUBLIC? TRUE :NATIVE? TRUE)", NULL, NULL);
    defineMethodObject("(DEFMETHOD (DEFINED? BOOLEAN) ((X SECOND-CLASS-OBJECT)) :DOCUMENTATION \"Return true if `x' is defined (handled specially by all translators).\" :PUBLIC? TRUE :NATIVE? TRUE)", NULL, NULL);
    defineMethodObject("(DEFMETHOD (DEFINED? BOOLEAN) ((X NATIVE-VECTOR)) :DOCUMENTATION \"Return true if `x' is defined (handled specially by all translators).\" :PUBLIC? TRUE :NATIVE? TRUE)", NULL, NULL);
    defineMethodObject("(DEFMETHOD (DEFINED? BOOLEAN) ((X ARRAY)) :DOCUMENTATION \"Return true if `x' is defined (handled specially by all translators).\" :PUBLIC? TRUE :NATIVE? TRUE)", NULL, NULL);
    defineMethodObject("(DEFMETHOD (DEFINED? BOOLEAN) ((X STRING)) :DOCUMENTATION \"Return true if `x' is defined (handled specially by all translators).\" :PUBLIC? TRUE :NATIVE? TRUE)", NULL, NULL);
    defineMethodObject("(DEFMETHOD (DEFINED? BOOLEAN) ((X MUTABLE-STRING)) :DOCUMENTATION \"Return true if `x' is defined (handled specially by all translators).\" :PUBLIC? TRUE :NATIVE? TRUE)", NULL, NULL);
    defineMethodObject("(DEFMETHOD (DEFINED? BOOLEAN) ((X CHARACTER)) :DOCUMENTATION \"Return true if `x' is defined (handled specially by all translators).\" :PUBLIC? TRUE :NATIVE? TRUE)", NULL, NULL);
    defineMethodObject("(DEFMETHOD (DEFINED? BOOLEAN) ((X CODE)) :DOCUMENTATION \"Return true if `x' is defined (handled specially by all translators).\" :PUBLIC? TRUE :NATIVE? TRUE)", NULL, NULL);
    defineMethodObject("(DEFMETHOD (DEFINED? BOOLEAN) ((X INTEGER)) :DOCUMENTATION \"Return true if `x' is defined (handled specially by all translators).\" :PUBLIC? TRUE :NATIVE? TRUE)", NULL, NULL);
    defineMethodObject("(DEFMETHOD (DEFINED? BOOLEAN) ((X LONG-INTEGER)) :DOCUMENTATION \"Return true if `x' is defined (handled specially by all translators).\" :PUBLIC? TRUE :NATIVE? TRUE)", NULL, NULL);
    defineMethodObject("(DEFMETHOD (DEFINED? BOOLEAN) ((X FLOAT)) :DOCUMENTATION \"Return true if `x' is defined (handled specially by all translators).\" :PUBLIC? TRUE :NATIVE? TRUE)", NULL, NULL);
    defineFunctionObject("EQ?", "(DEFUN (EQ? BOOLEAN) ((X UNKNOWN) (Y UNKNOWN)) :DOCUMENTATION \"Return true if `x' and `y' are literally the same object (or\nsimple number).  Analogue to the Common Lisp EQL and C++ and Java's ==.\" :PUBLIC? TRUE :NATIVE? TRUE)", NULL, NULL);
    defineFunctionObject("=", "(DEFUN (= BOOLEAN) ((X NUMBER) (Y NUMBER)) :DOCUMENTATION \"Return true if `x' and `y' are numbers of exactly the same magnitude.\" :PUBLIC? TRUE :NATIVE? TRUE)", NULL, NULL);
    defineFunctionObject("EQL?", "(DEFUN (EQL? BOOLEAN) ((X OBJECT) (Y OBJECT)) :DOCUMENTATION \"Return true if `x' and `y' are `eq?' or equivalent literals\nsuch as strings that also might be wrapped in non-identical wrappers.  For\nthe case where `x' or `y' are plain literals such as strings or integers, the\nSTELLA translator substitutes the equality test appropriate for the particular\ntarget language and does not actually call this function.  For cases where\n`x' or `y' are known to be of type STANDARD-OBJECT, the STELLA translator\nsubstitutes the faster `eq?' test inline.\" :PUBLIC? TRUE)", ((cpp_function_code)(&eqlP)), NULL);
    defineFunctionObject("EQUAL?", "(DEFUN (EQUAL? BOOLEAN) ((X OBJECT) (Y OBJECT)) :DOCUMENTATION \"Return true if `x' and `y' are `eql?' or considered equal\nby a user-defined `object-equal?' method.  This implements a fully extensible\nequality test similar to Java's `equals' method.  Note that writers of custom\n`object-equal?' methods must also implement a corresponding `equal-hash-code'\nmethod.\" :PUBLIC? TRUE)", ((cpp_function_code)(&equalP)), NULL);
    defineMethodObject("(DEFMETHOD (OBJECT-EQUAL? BOOLEAN) ((X OBJECT) (Y OBJECT)) :DOCUMENTATION \"Return true if `x' and `y' are `eq?'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Object::objectEqualP))), NULL);
    defineMethodObject("(DEFMETHOD (OBJECT-EQUAL? BOOLEAN) ((X WRAPPER) (Y OBJECT)) :DOCUMENTATION \"Return true if `x' and `y' are literal wrappers whose\nliterals are considered `eql?'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Wrapper::objectEqualP))), NULL);
    defineFunctionObject(">", "(DEFUN (> BOOLEAN) ((X NUMBER) (Y NUMBER)) :DOCUMENTATION \"Return true if `x' is greater than `y'.\" :PUBLIC? TRUE :NATIVE? TRUE)", NULL, NULL);
    defineFunctionObject(">=", "(DEFUN (>= BOOLEAN) ((X NUMBER) (Y NUMBER)) :DOCUMENTATION \"Return true if `x' is greater than or equal to `y'.\" :PUBLIC? TRUE :NATIVE? TRUE)", NULL, NULL);
    defineFunctionObject("<", "(DEFUN (< BOOLEAN) ((X NUMBER) (Y NUMBER)) :DOCUMENTATION \"Return true if `x' is less than `y'.\" :PUBLIC? TRUE :NATIVE? TRUE)", NULL, NULL);
    defineFunctionObject("<=", "(DEFUN (<= BOOLEAN) ((X NUMBER) (Y NUMBER)) :DOCUMENTATION \"Return true if `x' is less than or equal to `y'.\" :PUBLIC? TRUE :NATIVE? TRUE)", NULL, NULL);
    defineFunctionObject("+", "(DEFUN (+ NUMBER) (|&REST| (ARGUMENTS NUMBER)) :DOCUMENTATION \"Return the sum of all `arguments'.\" :PUBLIC? TRUE :NATIVE? TRUE)", NULL, NULL);
    defineFunctionObject("-", "(DEFUN (- NUMBER) ((X NUMBER) |&REST| (ARGUMENTS NUMBER)) :DOCUMENTATION \"If only `x' was supplied return the result of 0 - `x'.\nOtherwise, return the result of (...((`x' - arg1) - arg2) - ... - argN).\" :PUBLIC? TRUE :NATIVE? TRUE)", NULL, NULL);
    defineFunctionObject("*", "(DEFUN (* NUMBER) (|&REST| (ARGUMENTS NUMBER)) :DOCUMENTATION \"Return the product of all `arguments'.\" :PUBLIC? TRUE :NATIVE? TRUE)", NULL, NULL);
    defineFunctionObject("/", "(DEFUN (/ NUMBER) ((X NUMBER) |&REST| (ARGUMENTS NUMBER)) :DOCUMENTATION \"If only `x' was supplied return the result of 1 / `x'.\nOtherwise, return the result of (...((`x' / arg1) / arg2 ) / ... / argN).\" :PUBLIC? TRUE :NATIVE? TRUE)", NULL, NULL);
    defineMethodObject("(DEFMETHOD (ZERO? BOOLEAN) ((X INTEGER)) :DOCUMENTATION \"Return true if `x' is 0.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:= X 0) :CPP \"(!x)\" :JAVA \"(x == 0)\")))", wrapFunctionCode(((cpp_function_code)(((boolean  (*) (int))(&integerZeroP))))), NULL);
    defineMethodObject("(DEFMETHOD (ZERO? BOOLEAN) ((X LONG-INTEGER)) :DOCUMENTATION \"Return true if `x' is 0.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:= X 0) :CPP \"(!x)\" :JAVA \"(x == 0)\")))", wrapFunctionCode(((cpp_function_code)(((boolean  (*) (long long int))(&longIntegerZeroP))))), NULL);
    defineMethodObject("(DEFMETHOD (PLUS? BOOLEAN) ((X INTEGER)) :DOCUMENTATION \"Return true if `x' is greater than 0.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:> X 0) :CPP \"(x > 0)\" :JAVA \"(x > 0)\")))", wrapFunctionCode(((cpp_function_code)(((boolean  (*) (int))(&integerPlusP))))), NULL);
    defineMethodObject("(DEFMETHOD (PLUS? BOOLEAN) ((X LONG-INTEGER)) :DOCUMENTATION \"Return true if `x' is greater than 0.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:> X 0) :CPP \"(x > 0)\" :JAVA \"(x > 0)\")))", wrapFunctionCode(((cpp_function_code)(((boolean  (*) (long long int))(&longIntegerPlusP))))), NULL);
    defineMethodObject("(DEFMETHOD (EVEN? BOOLEAN) ((X INTEGER)) :DOCUMENTATION \"Return true if `x' is an even number.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:NOT (CL:LOGBITP 0 X)) :CPP \"!(x % 2)\" :JAVA \"((x % 2) == 0)\")))", wrapFunctionCode(((cpp_function_code)(((boolean  (*) (int))(&integerEvenP))))), NULL);
    defineMethodObject("(DEFMETHOD (EVEN? BOOLEAN) ((X LONG-INTEGER)) :DOCUMENTATION \"Return true if `x' is an even number.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:NOT (CL:LOGBITP 0 X)) :CPP \"!(x % 2)\" :JAVA \"((x % 2) == 0)\")))", wrapFunctionCode(((cpp_function_code)(((boolean  (*) (long long int))(&longIntegerEvenP))))), NULL);
    defineMethodObject("(DEFMETHOD (ODD? BOOLEAN) ((X INTEGER)) :DOCUMENTATION \"Return true if `x' is an odd number.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:LOGBITP 0 X) :CPP \"(x % 2)\" :JAVA \"((x % 2) == 1)\")))", wrapFunctionCode(((cpp_function_code)(((boolean  (*) (int))(&integerOddP))))), NULL);
    defineMethodObject("(DEFMETHOD (ODD? BOOLEAN) ((X LONG-INTEGER)) :DOCUMENTATION \"Return true if `x' is an odd number.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:LOGBITP 0 X) :CPP \"(x % 2)\" :JAVA \"((x % 2) == 1)\")))", wrapFunctionCode(((cpp_function_code)(((boolean  (*) (long long int))(&longIntegerOddP))))), NULL);
    defineMethodObject("(DEFMETHOD (DIV INTEGER) ((X INTEGER) (Y INTEGER)) :DOCUMENTATION \"Return the integer quotient from dividing `x' by `y'.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:VALUES (CL:TRUNCATE X Y)) :CPP \"(x / y)\" :JAVA \"(x / y)\")))", wrapFunctionCode(((cpp_function_code)(((int  (*) (int, int))(&integerDiv))))), NULL);
    defineMethodObject("(DEFMETHOD (DIV LONG-INTEGER) ((X LONG-INTEGER) (Y LONG-INTEGER)) :DOCUMENTATION \"Return the integer quotient from dividing `x' by `y'.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:VALUES (CL:TRUNCATE X Y)) :CPP \"(x / y)\" :JAVA \"(x / y)\")))", wrapFunctionCode(((cpp_function_code)(((long long int  (*) (long long int, long long int))(&longIntegerDiv))))), NULL);
    defineMethodObject("(DEFMETHOD (REM INTEGER) ((X INTEGER) (Y INTEGER)) :DOCUMENTATION \"Return the remainder from dividing `x' by `y'.  The\nsign of the result is always the same as the sign of `x'.  This has slightly\ndifferent behavior than the `mod' function, and has less overhead in C++ and\nJava, which don't have direct support for a true modulus function.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:REM X Y) :CPP \"(x % y)\" :JAVA \"(x % y)\")))", wrapFunctionCode(((cpp_function_code)(((int  (*) (int, int))(&integerRem))))), NULL);
    defineMethodObject("(DEFMETHOD (REM LONG-INTEGER) ((X LONG-INTEGER) (Y LONG-INTEGER)) :DOCUMENTATION \"Return the remainder from dividing `x' by `y'.  The\nsign of the result is always the same as the sign of `x'.  This has slightly\ndifferent behavior than the `mod' function, and has less overhead in C++ and\nJava, which don't have direct support for a true modulus function.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:REM X Y) :CPP \"(x % y)\" :JAVA \"(x % y)\")))", wrapFunctionCode(((cpp_function_code)(((long long int  (*) (long long int, long long int))(&longIntegerRem))))), NULL);
    defineFunctionObject("FREM", "(DEFUN (FREM FLOAT) ((X FLOAT) (Y FLOAT)) :DOCUMENTATION \"Return the floating point remainder from dividing `x' by `y'.  The\nsign of the result is always the same as the sign of `x'.  This has slightly\ndifferent behavior than the `mod' function, and has less overhead in C++ and\nJava, which don't have direct support for a true modulus function.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:REM X Y) :CPP \"fmod(x, y)\" :JAVA \"(x % y)\")))", ((cpp_function_code)(&frem)), NULL);
    defineMethodObject("(DEFMETHOD (MOD INTEGER) ((X INTEGER) (MODULUS INTEGER)) :DOCUMENTATION \"True modulus.  Return the result of `x' mod `modulo'.\nNote: In C++ and Java, `mod' has more overhead than the similar\nfunction `rem'.  The  answers returned by `mod' and `rem' are only\ndifferent when the signs of `x' and `modulo' are different.\" :PUBLIC? TRUE)", wrapFunctionCode(((cpp_function_code)(((int  (*) (int, int))(&integerMod))))), NULL);
    defineMethodObject("(DEFMETHOD (MOD LONG-INTEGER) ((X LONG-INTEGER) (MODULUS LONG-INTEGER)) :DOCUMENTATION \"True modulus.  Return the result of `x' mod `modulo'.\nNote: In C++ and Java, `mod' has more overhead than the similar\nfunction `rem'.  The  answers returned by `mod' and `rem' are only\ndifferent when the signs of `x' and `modulo' are different.\" :PUBLIC? TRUE)", wrapFunctionCode(((cpp_function_code)(((long long int  (*) (long long int, long long int))(&longIntegerMod))))), NULL);
    defineFunctionObject("FMOD", "(DEFUN (FMOD FLOAT) ((X FLOAT) (MODULUS FLOAT)) :DOCUMENTATION \"True modulus for floats.  Return the result of `x' mod `modulo'.\nNote: In C++ and Java, `mod' has more overhead than the similar\nfunction `rem'.  The  answers returned by `mod' and `rem' are only\ndifferent when the signs of `x' and `modulo' are different.\" :PUBLIC? TRUE)", ((cpp_function_code)(&stella::fmod)), NULL);
    defineFunctionObject("GCD", "(DEFUN (GCD LONG-INTEGER) ((X LONG-INTEGER) (Y LONG-INTEGER)) :DOCUMENTATION \"Return the greatest common divisor of `x' and `y'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&gcd)), NULL);
    defineFunctionObject("CEILING", "(DEFUN (CEILING INTEGER) ((N NUMBER)) :DOCUMENTATION \"Return the smallest integer >= `n'.\" :NATIVE? TRUE :PUBLIC? TRUE)", NULL, NULL);
    defineFunctionObject("FLOOR", "(DEFUN (FLOOR INTEGER) ((N NUMBER)) :DOCUMENTATION \"Return the biggest integer <= `n'.\" :NATIVE? TRUE :PUBLIC? TRUE)", NULL, NULL);
    defineFunctionObject("ROUND", "(DEFUN (ROUND INTEGER) ((N NUMBER)) :DOCUMENTATION \"Round `n' to the closest integer and return the result.\" :NATIVE? TRUE :PUBLIC? TRUE)", NULL, NULL);
  }
}

void helpStartupPrimal3() {
  {
    defineFunctionObject("TRUNCATE", "(DEFUN (TRUNCATE INTEGER) ((N NUMBER)) :DOCUMENTATION \"Truncate `n' toward zero and return the result.\" :NATIVE? TRUE :PUBLIC? TRUE)", NULL, NULL);
    defineFunctionObject("REGULAR-INTEGER-VALUED?", "(DEFUN (REGULAR-INTEGER-VALUED? BOOLEAN) ((X LONG-INTEGER)) :DOCUMENTATION \"Return `true' if `x' can be represented by a regular integer.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (AND (>= X NULL-INTEGER) (<= X MOST-POSITIVE-INTEGER))))", ((cpp_function_code)(&regularIntegerValuedP)), NULL);
    defineFunctionObject("INTEGER-VALUED?", "(DEFUN (INTEGER-VALUED? BOOLEAN) ((X FLOAT)) :DOCUMENTATION \"Returns `true' if `x' is the floating point representation of an integer.\" :PUBLIC? TRUE)", ((cpp_function_code)(((boolean  (*) (double))(&integerValuedP)))), NULL);
    defineFunctionObject("FLOAT-TO-BASE60", "(DEFUN (FLOAT-TO-BASE60 (CONS OF NUMBER-WRAPPER)) ((X FLOAT) (ALL-INTEGERS? BOOLEAN)) :DOCUMENTATION \"Returns a cons of `x' in a base-60 form.  That means\nthe first value will be the integer part of `x', the next value\nthe iteger value of the fraction part of `x' times 60 and the\nthird value the fraction part of `x' time 3600.  If `all-integers?'\nis `true', then the last value will be rounded to an integer.\nThis can be used to convert from decimal degree values to Degree-Minute-Second\nor from decimal hours to Hour-Minute-Second format.\" :PUBLIC? TRUE)", ((cpp_function_code)(((Cons*  (*) (double, boolean))(&floatToBase60)))), NULL);
    defineFunctionObject("BASE60-TO-FLOAT", "(DEFUN (BASE60-TO-FLOAT FLOAT) ((L (CONS OF NUMBER-WRAPPER))) :DOCUMENTATION \"Converts (x y z) into a float.  The return value\nis x + y/60 + z/3600.\nThis can be used to convert from Degree-Minute-Second to decimal degrees\nor from Hour-Minute-Second format to decimal hours.\")", ((cpp_function_code)(&base60ToFloat)), NULL);
    defineFunctionObject("RANDOM", "(DEFUN (RANDOM INTEGER) ((N INTEGER)) :PUBLIC? TRUE :DOCUMENTATION \"Generate a random integer in the interval [0..n-1].\nThe random number generator is seeded based on the current time every\ntime STELLA starts up; however, your mileage may vary depending on\nthe native language implementation.\")", ((cpp_function_code)(&stella::random)), NULL);
    defineFunctionObject("SEED-RANDOM-NUMBER-GENERATOR", "(DEFUN SEED-RANDOM-NUMBER-GENERATOR () :DOCUMENTATION \"Seeds the random number generator based on the current time.\" :PUBLIC? TRUE)", ((cpp_function_code)(&seedRandomNumberGenerator)), NULL);
    defineFunctionObject("SEED-RANDOM-NUMBER-GENERATOR2", "(DEFUN SEED-RANDOM-NUMBER-GENERATOR2 () :DOCUMENTATION \"Seeds the random number generator based on the current time and /dev/urandom if it is available.\" :PUBLIC? TRUE)", ((cpp_function_code)(&seedRandomNumberGenerator2)), NULL);
    defineFunctionObject("SQRT", "(DEFUN (SQRT FLOAT) ((N FLOAT)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"Return the square root of `n'.\" (RETURN (VERBATIM :COMMON-LISP (CL:SQRT N) :CPP \"::sqrt(n)\" :JAVA \"Math.sqrt(n)\")))", ((cpp_function_code)(&stella::sqrt)), NULL);
    defineFunctionObject("COS", "(DEFUN (COS FLOAT) ((N FLOAT)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"Return the cosine of `n' radians.\" (RETURN (VERBATIM :COMMON-LISP (CL:COS N) :CPP \"::cos(n)\" :JAVA \"Math.cos(n)\")))", ((cpp_function_code)(&stella::cos)), NULL);
    defineFunctionObject("SIN", "(DEFUN (SIN FLOAT) ((N FLOAT)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"Return the sine of `n' radians.\" (RETURN (VERBATIM :COMMON-LISP (CL:SIN N) :CPP \"::sin(n)\" :JAVA \"Math.sin(n)\")))", ((cpp_function_code)(&stella::sin)), NULL);
    defineFunctionObject("TAN", "(DEFUN (TAN FLOAT) ((N FLOAT)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"Return the tangent of `n' radians.\" (RETURN (VERBATIM :COMMON-LISP (CL:TAN N) :CPP \"::tan(n)\" :JAVA \"Math.tan(n)\")))", ((cpp_function_code)(&stella::tan)), NULL);
    defineFunctionObject("ACOS", "(DEFUN (ACOS FLOAT) ((N FLOAT)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"Return the arccosine of `n' in radians.\" (RETURN (VERBATIM :COMMON-LISP (CL:ACOS N) :CPP \"::acos(n)\" :JAVA \"Math.acos(n)\")))", ((cpp_function_code)(&stella::acos)), NULL);
    defineFunctionObject("ASIN", "(DEFUN (ASIN FLOAT) ((N FLOAT)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"Return the arcsine of `n' in radians.\" (RETURN (VERBATIM :COMMON-LISP (CL:ASIN N) :CPP \"::asin(n)\" :JAVA \"Math.asin(n)\")))", ((cpp_function_code)(&stella::asin)), NULL);
    defineFunctionObject("ATAN", "(DEFUN (ATAN FLOAT) ((N FLOAT)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"Return the arc tangent of `n' in radians.\" (RETURN (VERBATIM :COMMON-LISP (CL:ATAN N) :CPP \"::atan(n)\" :JAVA \"Math.atan(n)\")))", ((cpp_function_code)(&stella::atan)), NULL);
    defineFunctionObject("ATAN2", "(DEFUN (ATAN2 FLOAT) ((X FLOAT) (Y FLOAT)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"Return the arc tangent of `x' / `y' in radians.\" (RETURN (VERBATIM :COMMON-LISP (CL:ATAN X Y) :CPP \"::atan2(x,y)\" :JAVA \"Math.atan2(x,y)\")))", ((cpp_function_code)(&stella::atan2)), NULL);
    defineFunctionObject("LOG", "(DEFUN (LOG FLOAT) ((N FLOAT)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"Return the natural logarithm (base e) of `n'.\" (RETURN (VERBATIM :COMMON-LISP (CL:LOG N) :CPP \"::log(n)\" :JAVA \"Math.log(n)\")))", ((cpp_function_code)(&stella::log)), NULL);
    defineFunctionObject("LOG2", "(DEFUN (LOG2 FLOAT) ((N FLOAT)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"Return the logarithm (base 2) of `n'.\" (RETURN (VERBATIM :COMMON-LISP \"(CL:LOG n 2.0d0)\" :OTHERWISE (* (LOG N) RECIPROCAL-NL2))))", ((cpp_function_code)(&log2)), NULL);
    defineFunctionObject("LOG10", "(DEFUN (LOG10 FLOAT) ((N FLOAT)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"Return the logarithm (base 10) of `n'.\" (RETURN (VERBATIM :COMMON-LISP \"(CL:LOG n 10.0d0)\" :OTHERWISE (* (LOG N) RECIPROCAL-NL10))))", ((cpp_function_code)(&log10)), NULL);
    defineFunctionObject("EXP", "(DEFUN (EXP FLOAT) ((N FLOAT)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"Return the e to the power `n'.\" (RETURN (VERBATIM :COMMON-LISP (CL:EXP N) :CPP \"::exp(n)\" :JAVA \"Math.exp(n)\")))", ((cpp_function_code)(&stella::exp)), NULL);
    defineFunctionObject("EXPT", "(DEFUN (EXPT FLOAT) ((X FLOAT) (Y FLOAT)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"Return `x' ^ `y'.\" (RETURN (VERBATIM :COMMON-LISP (CL:EXPT X Y) :CPP \"::pow(x,y)\" :JAVA \"Math.pow(x,y)\")))", ((cpp_function_code)(&expt)), NULL);
    defineMethodObject("(DEFMETHOD (MIN INTEGER) ((X INTEGER) (Y INTEGER)) :DOCUMENTATION \"Return the minimum of `x' and `y'.  If either is NULL, return the other.\" :PUBLIC? TRUE)", wrapFunctionCode(((cpp_function_code)(((int  (*) (int, int))(&stella::integerMin))))), NULL);
    defineMethodObject("(DEFMETHOD (MIN LONG-INTEGER) ((X LONG-INTEGER) (Y LONG-INTEGER)) :DOCUMENTATION \"Return the minimum of `x' and `y'.  If either is NULL, return the other.\" :PUBLIC? TRUE)", wrapFunctionCode(((cpp_function_code)(((long long int  (*) (long long int, long long int))(&stella::longIntegerMin))))), NULL);
    defineMethodObject("(DEFMETHOD (MIN FLOAT) ((X FLOAT) (Y FLOAT)) :DOCUMENTATION \"Return the minimum of `x' and `y'.  If either is NULL, return the other.\" :PUBLIC? TRUE)", wrapFunctionCode(((cpp_function_code)(((double  (*) (double, double))(&stella::floatMin))))), NULL);
    defineMethodObject("(DEFMETHOD (MIN NUMBER-WRAPPER) ((X NUMBER-WRAPPER) (Y NUMBER-WRAPPER)) :DOCUMENTATION \"Return the minimum of `x' and `y'.  If `y' is NULL, return `x'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NumberWrapper::min))), NULL);
    defineMethodObject("(DEFMETHOD (MAX INTEGER) ((X INTEGER) (Y INTEGER)) :DOCUMENTATION \"Return the maximum of `x' and `y'.  If either is NULL, return the other.\" :PUBLIC? TRUE)", wrapFunctionCode(((cpp_function_code)(((int  (*) (int, int))(&stella::integerMax))))), NULL);
    defineMethodObject("(DEFMETHOD (MAX LONG-INTEGER) ((X LONG-INTEGER) (Y LONG-INTEGER)) :DOCUMENTATION \"Return the maximum of `x' and `y'.  If either is NULL, return the other.\" :PUBLIC? TRUE)", wrapFunctionCode(((cpp_function_code)(((long long int  (*) (long long int, long long int))(&stella::longIntegerMax))))), NULL);
    defineMethodObject("(DEFMETHOD (MAX FLOAT) ((X FLOAT) (Y FLOAT)) :DOCUMENTATION \"Return the maximum of `x' and `y'.  If either is NULL, return the other.\" :PUBLIC? TRUE)", wrapFunctionCode(((cpp_function_code)(((double  (*) (double, double))(&stella::floatMax))))), NULL);
    defineMethodObject("(DEFMETHOD (MAX NUMBER-WRAPPER) ((X NUMBER-WRAPPER) (Y NUMBER-WRAPPER)) :DOCUMENTATION \"Return the maximum of `x' and `y'.  If `y' is NULL, return `x'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NumberWrapper::max))), NULL);
    defineMethodObject("(DEFMETHOD (ABS INTEGER) ((X INTEGER)) :DOCUMENTATION \"Return the absolute value of `x'.\" :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (CHOOSE (< X 0) (- 0 X) X)))", wrapFunctionCode(((cpp_function_code)(((int  (*) (int))(&integerAbs))))), NULL);
    defineMethodObject("(DEFMETHOD (ABS LONG-INTEGER) ((X LONG-INTEGER)) :DOCUMENTATION \"Return the absolute value of `x'.\" :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (CHOOSE (< X 0) (- 0 X) X)))", wrapFunctionCode(((cpp_function_code)(((long long int  (*) (long long int))(&longIntegerAbs))))), NULL);
    defineMethodObject("(DEFMETHOD (ABS FLOAT) ((X FLOAT)) :DOCUMENTATION \"Return the absolute value of `x'.\" :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (CHOOSE (< X 0.0) (- 0.0 X) X)))", wrapFunctionCode(((cpp_function_code)(((double  (*) (double))(&floatAbs))))), NULL);
    defineFunctionObject("CHARACTER-CODE", "(DEFUN (CHARACTER-CODE INTEGER) ((CH CHARACTER)) :DOCUMENTATION \"Return the 8-bit ASCII code of `ch' as an integer.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:CHAR-CODE CH) :CPP \"(int)(unsigned char) ch\" :JAVA \"(int) ch\")))", ((cpp_function_code)(((int  (*) (char))(&characterCode)))), NULL);
    defineFunctionObject("CODE-CHARACTER", "(DEFUN (CODE-CHARACTER CHARACTER) ((CODE INTEGER)) :DOCUMENTATION \"Return the character encoded by `code' (0 <= `code' <= 255).\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:CODE-CHAR CODE) :CPP \"(char) code\" :JAVA \"(char) code\")))", ((cpp_function_code)(((char  (*) (int))(&codeCharacter)))), NULL);
    defineFunctionObject("CHARACTER-DOWNCASE", "(DEFUN (CHARACTER-DOWNCASE CHARACTER) ((CH CHARACTER)) :DOCUMENTATION \"If `ch' is lowercase, return its uppercase version,\notherwise, return 'ch' unmodified.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (DOWNCASE-CHARACTER CH)))", ((cpp_function_code)(((char  (*) (char))(&characterDowncase)))), NULL);
    defineFunctionObject("CHARACTER-UPCASE", "(DEFUN (CHARACTER-UPCASE CHARACTER) ((CH CHARACTER)) :DOCUMENTATION \"If `ch' is uppercase, return its lowercase version,\notherwise, return 'ch' unmodified.  If only the first character of\na sequence of characters is to be capitalized, `character-capitalize'\nshould be used instead.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (UPCASE-CHARACTER CH)))", ((cpp_function_code)(((char  (*) (char))(&characterUpcase)))), NULL);
    defineFunctionObject("CHARACTER-CAPITALIZE", "(DEFUN (CHARACTER-CAPITALIZE CHARACTER) ((CH CHARACTER)) :DOCUMENTATION \"Return the capitalized character for `ch'.  This is generally the same\nas the uppercase character, except for obscure non-English characters in Java.  It should\nbe used if only the first character of a sequence of characters is to be capitalized.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (VERBATIM :JAVA \"Character.toTitleCase(ch)\" :OTHERWISE (CHARACTER-UPCASE CH))))", ((cpp_function_code)(((char  (*) (char))(&characterCapitalize)))), NULL);
    defineFunctionObject("STRING-EQL?", "(DEFUN (STRING-EQL? BOOLEAN) ((X STRING) (Y STRING)) :DOCUMENTATION \"Return true if `x' and `y' are equal strings or are both undefined.  This\ntest is substituted automatically by the STELLA translator if `eql?' is applied\nto strings.\" :PUBLIC? TRUE)", ((cpp_function_code)(((boolean  (*) (const char*, const char*))(&stringEqlP)))), NULL);
    defineFunctionObject("STRING-EQUAL?", "(DEFUN (STRING-EQUAL? BOOLEAN) ((X STRING) (Y STRING)) :DOCUMENTATION \"Return true if `x' and `y' are equal strings ignoring character case or\nare both undefined.\" :PUBLIC? TRUE)", ((cpp_function_code)(((boolean  (*) (const char*, const char*))(&stringEqualP)))), NULL);
    defineFunctionObject("STRING-COMPARE", "(DEFUN (STRING-COMPARE INTEGER) ((X STRING) (Y STRING) (CASE-SENSITIVE? BOOLEAN)) :PUBLIC? TRUE :DOCUMENTATION \"Compare `x' and `y' lexicographically, and return -1, 0, \nor 1, depending on whether `x' is less than, equal, or greater than `y'.\nIf `case-sensitive?' is true, then case does matter for the comparison\")", ((cpp_function_code)(((int  (*) (const char*, const char*, boolean))(&stringCompare)))), NULL);
    defineMethodObject("(DEFMETHOD (EMPTY? BOOLEAN) ((X STRING)) :DOCUMENTATION \"Return true if `x' is the empty string \\\"\\\"\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (STRING-EQL? X \"\")))", wrapFunctionCode(((cpp_function_code)(((boolean  (*) (const char*))(&stringEmptyP))))), NULL);
    defineMethodObject("(DEFMETHOD (NON-EMPTY? BOOLEAN) ((X STRING)) :DOCUMENTATION \"Return true if `x' is not the empty string \\\"\\\"\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (NOT (EMPTY? X))))", wrapFunctionCode(((cpp_function_code)(((boolean  (*) (const char*))(&stringNonEmptyP))))), NULL);
    defineMethodObject("(DEFMETHOD (EMPTY? BOOLEAN) ((X STRING-WRAPPER)) :DOCUMENTATION \"Return true if `x' is the wrapped empty string \\\"\\\"\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (STRING-EQL? (WRAPPER-VALUE X) \"\")))", wrapMethodCode(((cpp_method_code)(&StringWrapper::emptyP))), NULL);
    defineMethodObject("(DEFMETHOD (NON-EMPTY? BOOLEAN) ((X STRING-WRAPPER)) :DOCUMENTATION \"Return true if `x' is not the wrapped empty string \\\"\\\"\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (NOT (EMPTY? X))))", wrapMethodCode(((cpp_method_code)(&StringWrapper::nonEmptyP))), NULL);
    defineFunctionObject("BLANK-STRING?", "(DEFUN (BLANK-STRING? BOOLEAN) ((STRING STRING)) :DOCUMENTATION \"Return true if `string' is either NULL, empty, or only\ncontains white space characters.\" :PUBLIC? TRUE)", ((cpp_function_code)(&blankStringP)), NULL);
    defineFunctionObject("STRING<", "(DEFUN (STRING< BOOLEAN) ((X STRING) (Y STRING)) :PUBLIC? TRUE :DOCUMENTATION \"Return true if `x' is lexicographically < `y', considering case.\")", ((cpp_function_code)(&stringL)), NULL);
    defineFunctionObject("STRING<=", "(DEFUN (STRING<= BOOLEAN) ((X STRING) (Y STRING)) :PUBLIC? TRUE :DOCUMENTATION \"Return true if `x' is lexicographically <= `y', considering case.\")", ((cpp_function_code)(&stringLE)), NULL);
    defineFunctionObject("STRING>=", "(DEFUN (STRING>= BOOLEAN) ((X STRING) (Y STRING)) :PUBLIC? TRUE :DOCUMENTATION \"Return true if `x' is lexicographically >= `y', considering case.\")", ((cpp_function_code)(&stringGE)), NULL);
    defineFunctionObject("STRING>", "(DEFUN (STRING> BOOLEAN) ((X STRING) (Y STRING)) :PUBLIC? TRUE :DOCUMENTATION \"Return true if `x' is lexicographically > `y', considering case.\")", ((cpp_function_code)(&stringG)), NULL);
    defineFunctionObject("STRING-LESS?", "(DEFUN (STRING-LESS? BOOLEAN) ((X STRING) (Y STRING)) :PUBLIC? TRUE :DOCUMENTATION \"Return true if `x' is lexicographically < `y', ignoring case.\")", ((cpp_function_code)(((boolean  (*) (const char*, const char*))(&stringLessP)))), NULL);
    defineFunctionObject("STRING-LESS-EQUAL?", "(DEFUN (STRING-LESS-EQUAL? BOOLEAN) ((X STRING) (Y STRING)) :PUBLIC? TRUE :DOCUMENTATION \"Return true if `x' is lexicographically <= `y', ignoring case.\")", ((cpp_function_code)(((boolean  (*) (const char*, const char*))(&stringLessEqualP)))), NULL);
    defineFunctionObject("STRING-GREATER-EQUAL?", "(DEFUN (STRING-GREATER-EQUAL? BOOLEAN) ((X STRING) (Y STRING)) :PUBLIC? TRUE :DOCUMENTATION \"Return true if `x' is lexicographically >= `y', ignoring case.\")", ((cpp_function_code)(((boolean  (*) (const char*, const char*))(&stringGreaterEqualP)))), NULL);
    defineFunctionObject("STRING-GREATER?", "(DEFUN (STRING-GREATER? BOOLEAN) ((X STRING) (Y STRING)) :PUBLIC? TRUE :DOCUMENTATION \"Return true if `x' is lexicographically > `y', ignoring case.\")", ((cpp_function_code)(((boolean  (*) (const char*, const char*))(&stringGreaterP)))), NULL);
    defineFunctionObject("STRING-COMPARE-CASE-NORMALIZED", "(DEFUN (STRING-COMPARE-CASE-NORMALIZED INTEGER) ((X STRING) (Y STRING)) :DOCUMENTATION \"Compare `x' and `y' and return -1, 0, or 1, depending on whether\n`x' is less than, equal, or greater than `y' relative to the :ascii-case-normalized\ncollation.  In this collation `a < A < b' which gives strings that only differ in case a\ndefinite order while otherwise behaving identically to :ascii-case-insensitive.  This is\nsimilar to using a Java Collator for Locale.US with strength set to TERTIARY (which see).\" :PUBLIC? TRUE)", ((cpp_function_code)(((int  (*) (const char*, const char*))(&stringCompareCaseNormalized)))), NULL);
    defineFunctionObject("COMPARE-STRINGS", "(DEFUN (COMPARE-STRINGS INTEGER) ((X STRING) (Y STRING) (COLLATION KEYWORD)) :DOCUMENTATION \"Compare `x' and `y' and return -1, 0, or 1, depending on whether\n`x' is less than, equal, or greater than `y' relative to `collation'.  Currently\nsupported values for `collation' are :ascii-case-sensitive, :ascii-case-insensitive\n:ascii-case-normalized.  The first two correspond to `string-compare' called with\nthe appropriate third argument.  :ascii-case-normalized calls the function\n`string-compare-case-normalized' (which see).\" :PUBLIC? TRUE)", ((cpp_function_code)(&compareStrings)), NULL);
    defineFunctionObject("SAFE-COMPARE-STRINGS", "(DEFUN (SAFE-COMPARE-STRINGS INTEGER) ((X STRING) (Y STRING) (COLLATION KEYWORD)) :DOCUMENTATION \"Variant of `compare-strings' that also tolerates NULL values.\nNULL sorts after everything else in any collation.\" :PUBLIC? TRUE)", ((cpp_function_code)(&safeCompareStrings)), NULL);
    defineFunctionObject("MAKE-STRING", "(DEFUN (MAKE-STRING STRING) ((SIZE INTEGER) (INITCHAR CHARACTER)) :DOCUMENTATION \"Return a new string filled with `size' `initchar's.\" :PUBLIC? TRUE :NATIVE? TRUE)", ((cpp_function_code)(&makeString)), NULL);
    defineFunctionObject("MAKE-MUTABLE-STRING", "(DEFUN (MAKE-MUTABLE-STRING MUTABLE-STRING) ((SIZE INTEGER) (INITCHAR CHARACTER)) :DOCUMENTATION \"Return a new mutable string filled with `size' `initchar's.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:MAKE-STRING SIZE :INITIAL-ELEMENT INITCHAR) :CPP \"native_make_mutable_string(size, initchar)\" :JAVA \"#$(STELLAROOT).javalib.Native.makeMutableString(size, initchar)\")))", ((cpp_function_code)(&makeMutableString)), NULL);
    defineFunctionObject("MAKE-RAW-MUTABLE-STRING", "(DEFUN (MAKE-RAW-MUTABLE-STRING MUTABLE-STRING) ((SIZE INTEGER)) :DOCUMENTATION \"Return a new uninitialized mutable string of `size'.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (LET ((S MUTABLE-STRING NULL)) (VERBATIM :COMMON-LISP (SETQ S (CL:MAKE-STRING SIZE)) :CPP \"s = new (PointerFreeGC) char[size+1]; s[size]='\\\\0'\" :JAVA \"s = new StringBuffer(size); s.setLength(size)\") (RETURN S)))", ((cpp_function_code)(&makeRawMutableString)), NULL);
    defineFunctionObject("STRING-CONCATENATE", "(DEFUN (STRING-CONCATENATE STRING) ((STRING1 STRING) (STRING2 STRING)) :DOCUMENTATION \"Return a new string representing the concatenation of\n`string1' and `string2'.\" :NATIVE? TRUE)", ((cpp_function_code)(((const char*  (*) (const char*, const char*))(&stringConcatenate)))), NULL);
  }
}

void helpStartupPrimal4() {
  {
    defineMethodObject("(DEFMETHOD (CONCATENATE STRING) ((STRING1 STRING) (STRING2 STRING) |&REST| (OTHERSTRINGS STRING)) :PUBLIC? TRUE :DOCUMENTATION \"Return a new string representing the concatenation\nof `string1', `string2', and `otherStrings'.  The two mandatory parameters\nallow us to optimize the common binary case by not relying on the somewhat\nless efficient variable arguments mechanism.\")", wrapFunctionCode(((cpp_function_code)(((const char*  (*) (const char*, const char*, int, ...))(&stringConcatenate))))), NULL);
    defineFunctionObject("STRING-UPCASE", "(DEFUN (STRING-UPCASE STRING) ((STRING STRING)) :DOCUMENTATION \"Return an upper-case copy of `string'.\" :NATIVE? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(((const char*  (*) (const char*))(&stringUpcase)))), NULL);
    defineFunctionObject("STRING-DOWNCASE", "(DEFUN (STRING-DOWNCASE STRING) ((STRING STRING)) :DOCUMENTATION \"Return a lower-case copy of `string'.\" :NATIVE? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(((const char*  (*) (const char*))(&stringDowncase)))), NULL);
    defineFunctionObject("STRING-CAPITALIZE", "(DEFUN (STRING-CAPITALIZE STRING) ((STRING STRING)) :DOCUMENTATION \"Return a capitalized version of `string'.\" :NATIVE? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(((const char*  (*) (const char*))(&stringCapitalize)))), NULL);
    defineMethodObject("(DEFMETHOD (COPY STRING) ((STRING STRING)) :DOCUMENTATION \"Return a copy of `string'.\" :NATIVE? TRUE :C-CALLABLE? TRUE)", wrapFunctionCode(((cpp_function_code)(((const char*  (*) (const char*))(&stringCopy))))), NULL);
    defineMethodObject("(DEFMETHOD (COPY MUTABLE-STRING) ((STRING MUTABLE-STRING)) :DOCUMENTATION \"Return a copy of `string'.\" :NATIVE? TRUE :C-CALLABLE? TRUE)", wrapFunctionCode(((cpp_function_code)(((char*  (*) (char*))(&mutableStringCopy))))), NULL);
    defineMethodObject("(DEFMETHOD (SUBSTITUTE STRING) ((SELF STRING) (NEW-CHAR CHARACTER) (OLD-CHAR CHARACTER)) :DOCUMENTATION \"Substitute all occurences of `old-char' with `new-char'\nin the string `self'.\" :NATIVE? TRUE :PUBLIC? TRUE)", wrapFunctionCode(((cpp_function_code)(((const char*  (*) (const char*, char, char))(&stringSubstitute))))), NULL);
    defineMethodObject("(DEFMETHOD (SUBSTITUTE MUTABLE-STRING) ((SELF MUTABLE-STRING) (NEW-CHAR CHARACTER) (OLD-CHAR CHARACTER)) :DOCUMENTATION \"Substitute all occurences of `old-char' with `new-char'\nin the string `self'.\" :NATIVE? TRUE :PUBLIC? TRUE)", wrapFunctionCode(((cpp_function_code)(((char*  (*) (char*, char, char))(&mutableStringSubstitute))))), NULL);
    defineFunctionObject("HELP-SUBSTITUTE-CHARACTERS", "(DEFUN (HELP-SUBSTITUTE-CHARACTERS MUTABLE-STRING) ((SELF MUTABLE-STRING) (NEW-CHARS STRING) (OLD-CHARS STRING)) :PUBLIC? FALSE :GLOBALLY-INLINE? TRUE (LET ((POS INTEGER NULL)) (FOREACH I IN (INTERVAL 0 (1- (LENGTH SELF))) DO (SETQ POS (POSITION OLD-CHARS (NTH SELF I) 0)) (WHEN (DEFINED? POS) (SETF (NTH SELF I) (NTH NEW-CHARS POS)))) (RETURN SELF)))", ((cpp_function_code)(&helpSubstituteCharacters)), NULL);
    defineMethodObject("(DEFMETHOD (SUBSTITUTE-CHARACTERS MUTABLE-STRING) ((SELF MUTABLE-STRING) (NEW-CHARS STRING) (OLD-CHARS STRING)) :DOCUMENTATION \"Substitute all occurences of of a member of `old-chars' with the \ncorresponding member of `new-chars' in the string `self'.  IMPORTANT:  The return\nvalue should be used instead of relying on destructive substitution, since the\nsubstitution will not be destructive in all translated languages.\" :PUBLIC? TRUE)", wrapFunctionCode(((cpp_function_code)(((char*  (*) (char*, const char*, const char*))(&mutableStringSubstituteCharacters))))), NULL);
    defineMethodObject("(DEFMETHOD (SUBSTITUTE-CHARACTERS STRING) ((SELF STRING) (NEW-CHARS STRING) (OLD-CHARS STRING)) :DOCUMENTATION \"Substitute all occurences of of a member of `old-chars' with the \ncorresponding member of `new-chars' in the string `self'.  Returns a new string.\" :PUBLIC? TRUE)", wrapFunctionCode(((cpp_function_code)(((const char*  (*) (const char*, const char*, const char*))(&stringSubstituteCharacters))))), NULL);
    defineFunctionObject("REPLACE-SUBSTRINGS", "(DEFUN (REPLACE-SUBSTRINGS STRING) ((STRING STRING) (NEW STRING) (OLD STRING)) :DOCUMENTATION \"Replace all occurrences of `old' in `string' with `new'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&replaceSubstrings)), NULL);
    defineFunctionObject("INSTANTIATE-STRING-TEMPLATE", "(DEFUN (INSTANTIATE-STRING-TEMPLATE STRING) ((TEMPLATE STRING) |&REST| (|VARS&VALUES| STRING)) :DOCUMENTATION \"For each occurrence of a <var> string from `vars&values' in `template' replace it\nwith its corresponding <value> string.  Replacement is done in sequence which\nmeans (part of) a value might be replaced further with a later <var> and <value>.\" :PUBLIC? TRUE)", ((cpp_function_code)(&instantiateStringTemplate)), NULL);
    defineFunctionObject("INSERT-STRING", "(DEFUN (INSERT-STRING INTEGER) ((SOURCE STRING) (START INTEGER) (END INTEGER) (TARGET MUTABLE-STRING) (TARGET-INDEX INTEGER) (CASE-CONVERSION KEYWORD)) :DOCUMENTATION \"Inserts characters from `source' begining at `start' and\nending at `end' into `target' starting at `target-index'.  If `end' is `null',\nthen the entire length of the string is used. The copy of characters is affected\nby the `case-conversion' keyword which should be one of\n   :UPCASE :DOWNCASE :CAPITALIZE :PRESERVE.\n\nThe final value of target-index is returned.\")", ((cpp_function_code)(&insertString)), NULL);
    defineFunctionObject("STRING-TRIM", "(DEFUN (STRING-TRIM STRING) ((STRING STRING)) :DOCUMENTATION \"Remove any leading and trailing white space from `string'\nand return a copy of the trimmed substring (which might be empty if we had\nall white space).  If no white space was removed, `string' is returned\nunmodified and uncopied.\" :PUBLIC? TRUE)", ((cpp_function_code)(((const char*  (*) (const char*))(&stringTrim)))), NULL);
    defineFunctionObject("INTEGER-TO-STRING", "(DEFUN (INTEGER-TO-STRING STRING) ((I LONG-INTEGER)) :DOCUMENTATION \"Convert `i' to its string representation and return the result.\n This is more efficient than using a string stream.\" :NATIVE? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(((const char*  (*) (long long int))(&integerToString)))), NULL);
    defineFunctionObject("INT-TO-STRING", "(DEFUN (INT-TO-STRING STRING) ((I INTEGER)) :DOCUMENTATION \"Convert `i' to its string representation and return the result.\nThis is a convenience function that expects regular integers as opposed to longs\nwhich is useful in contexts where we do automatic unwrapping based on the target.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (INTEGER-TO-STRING I)))", ((cpp_function_code)(&intToString)), NULL);
    defineFunctionObject("INTEGER-TO-HEX-STRING", "(DEFUN (INTEGER-TO-HEX-STRING STRING) ((I LONG-INTEGER)) :DOCUMENTATION \"Convert `i' to a string representation in hexadecimal notation and return the result.\" :NATIVE? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(((const char*  (*) (long long int))(&integerToHexString)))), NULL);
    defineFunctionObject("INTEGER-TO-STRING-IN-BASE", "(DEFUN (INTEGER-TO-STRING-IN-BASE STRING) ((I LONG-INTEGER) (BASE INTEGER)) :DOCUMENTATION \"Convert `i' to a string representation in `base' and return the\nresult.  `base' must be positive and not more than 36.\n\nNote that in the C++ version, only 8, 10 and 16 will work as `base' arguments,\nsince that is all the underlying implementation supports.  Other argument\nvalues will be treated as `10'.\" :NATIVE? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(((const char*  (*) (long long int, int))(&integerToStringInBase)))), NULL);
    defineFunctionObject("FLOAT-TO-STRING", "(DEFUN (FLOAT-TO-STRING STRING) ((F FLOAT)) :DOCUMENTATION \"Convert `f' to its string representation and return the result.  This is more\nefficient than using a string stream.\" :NATIVE? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(((const char*  (*) (double))(&floatToString)))), NULL);
    defineFunctionObject("CHARACTER-TO-STRING", "(DEFUN (CHARACTER-TO-STRING STRING) ((C CHARACTER)) :DOCUMENTATION \"Convert `c' into a one-element string and return the result.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (MAKE-STRING 1 C)))", ((cpp_function_code)(((const char*  (*) (char))(&characterToString)))), NULL);
    defineFunctionObject("STELLA-INTEGER-TO-STRING-IN-BASE", "(DEFUN (STELLA-INTEGER-TO-STRING-IN-BASE STRING) ((INTEGER LONG-INTEGER) (BASE INTEGER)) :DOCUMENTATION \"STELLA version of `integer-to-string-in-base' which is faster than\nthe C++ version we have but slower than the native Java version.\" :PUBLIC? TRUE)", ((cpp_function_code)(&stellaIntegerToStringInBase)), NULL);
    defineFunctionObject("STRING-TO-INTEGER", "(DEFUN (STRING-TO-INTEGER LONG-INTEGER) ((STRING STRING)) :DOCUMENTATION \"Convert a `string' representation of an integer into an integer.\nUse `parse-long-integer' if the syntax of `string' needs to be checked for errors.\" :NATIVE? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(((long long int  (*) (const char*))(&stringToInteger)))), NULL);
    defineFunctionObject("STRING-TO-INT", "(DEFUN (STRING-TO-INT INTEGER) ((STRING STRING)) :DOCUMENTATION \"Convert a `string' representation of an integer into an integer.\nThis is a convenience function that ensures a regular integer return value.  If\n`string' represents a long integer, the behavior is undefined.  Use `parse-integer'\nif the syntax of `string' needs to be checked for errors.\" :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (STRING-TO-INTEGER STRING)))", ((cpp_function_code)(((int  (*) (const char*))(&stringToInt)))), NULL);
    defineFunctionObject("STRING-TO-FLOAT", "(DEFUN (STRING-TO-FLOAT FLOAT) ((STRING STRING)) :DOCUMENTATION \"Convert a `string' representation of a float into a float.\nUse `parse-float' if the syntax of `string' needs to be checked for errors.\" :NATIVE? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(((double  (*) (const char*))(&stringToFloat)))), NULL);
    defineFunctionObject("FORMAT-FLOAT", "(DEFUN (FORMAT-FLOAT STRING) ((F FLOAT) (NDECIMALS INTEGER)) :DOCUMENTATION \"Print `f' in fixed-point format with `nDecimals' behind the decimal point\nand return the result as a string.\" :NATIVE? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&formatFloat)), NULL);
    defineFunctionObject("FORMAT-WITH-PADDING", "(DEFUN (FORMAT-WITH-PADDING STRING) ((INPUT STRING) (LENGTH INTEGER) (PADCHAR CHARACTER) (ALIGN KEYWORD) (TRUNCATE? BOOLEAN)) :PUBLIC? TRUE :DOCUMENTATION \"Formats `input' to be (at least) `length' long, using `padchar' to\nfill if necessary.  `align' must be one of :LEFT, :RIGHT, :CENTER and will control\nhow `input' will be justified in the resulting string.  If `truncate?' is true, then\nthen an overlength string will be truncated, using the opposite of `align' to pick\nthe truncation direction.\")", ((cpp_function_code)(&formatWithPadding)), NULL);
    defineFunctionObject("ZERO-PAD-INTEGER", "(DEFUN (ZERO-PAD-INTEGER STRING) ((VALUE INTEGER) (SIZE INTEGER)) :PUBLIC? TRUE :DOCUMENTATION \"Returns a string representing `value' of at least length\n'size', padded if necessary with 0 characters.\")", ((cpp_function_code)(&zeroPadInteger)), NULL);
    defineFunctionObject("ZERO-PAD-STRING", "(DEFUN (ZERO-PAD-STRING STRING) ((INPUT STRING) (SIZE INTEGER)) :PUBLIC? FALSE)", ((cpp_function_code)(&zeroPadString)), NULL);
    defineMethodObject("(DEFMETHOD (MEMBER? BOOLEAN) ((SELF STRING) (CHAR CHARACTER)) :NATIVE? TRUE :PUBLIC? TRUE)", wrapFunctionCode(((cpp_function_code)(((boolean  (*) (const char*, char))(&stringMemberP))))), NULL);
    defineMethodObject("(DEFMETHOD (FIRST CHARACTER) ((SELF STRING)) :DOCUMENTATION \"Return the first character of `self'.\" :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (NTH SELF 0)))", wrapFunctionCode(((cpp_function_code)(((char  (*) (const char*))(&stringFirst))))), NULL);
    defineMethodObject("(DEFMETHOD (FIRST CHARACTER) ((SELF MUTABLE-STRING)) :DOCUMENTATION \"Return the first character of `self' (settable via `setf').\" :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (NTH SELF 0)))", wrapFunctionCode(((cpp_function_code)(((char  (*) (char*))(&mutableStringFirst))))), NULL);
    defineMethodObject("(DEFMETHOD (FIRST-SETTER CHARACTER) ((SELF MUTABLE-STRING) (CH CHARACTER)) :DOCUMENTATION \"Set the first character of `self' to `ch' and return `ch'.\" :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (SETF (NTH SELF 0) CH)))", wrapFunctionCode(((cpp_function_code)(((char  (*) (char*, char))(&mutableStringFirstSetter))))), NULL);
    defineMethodObject("(DEFMETHOD (SECOND CHARACTER) ((SELF STRING)) :DOCUMENTATION \"Return the second character of `self'.\" :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (NTH SELF 1)))", wrapFunctionCode(((cpp_function_code)(((char  (*) (const char*))(&stringSecond))))), NULL);
    defineMethodObject("(DEFMETHOD (SECOND CHARACTER) ((SELF MUTABLE-STRING)) :DOCUMENTATION \"Return the second character of `self' (settable via `setf').\" :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (NTH SELF 1)))", wrapFunctionCode(((cpp_function_code)(((char  (*) (char*))(&mutableStringSecond))))), NULL);
    defineMethodObject("(DEFMETHOD (SECOND-SETTER CHARACTER) ((SELF MUTABLE-STRING) (CH CHARACTER)) :DOCUMENTATION \"Set the second character of `self' to `ch' and return `ch'.\" :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (SETF (NTH SELF 1) CH)))", wrapFunctionCode(((cpp_function_code)(((char  (*) (char*, char))(&mutableStringSecondSetter))))), NULL);
    defineMethodObject("(DEFMETHOD (THIRD CHARACTER) ((SELF STRING)) :DOCUMENTATION \"Return the third character of `self'.\" :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (NTH SELF 2)))", wrapFunctionCode(((cpp_function_code)(((char  (*) (const char*))(&stringThird))))), NULL);
    defineMethodObject("(DEFMETHOD (THIRD CHARACTER) ((SELF MUTABLE-STRING)) :DOCUMENTATION \"Return the third character of `self' (settable via `setf').\" :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (NTH SELF 2)))", wrapFunctionCode(((cpp_function_code)(((char  (*) (char*))(&mutableStringThird))))), NULL);
    defineMethodObject("(DEFMETHOD (THIRD-SETTER CHARACTER) ((SELF MUTABLE-STRING) (CH CHARACTER)) :DOCUMENTATION \"Set the third character of `self' to `ch' and return `ch'.\" :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (SETF (NTH SELF 2) CH)))", wrapFunctionCode(((cpp_function_code)(((char  (*) (char*, char))(&mutableStringThirdSetter))))), NULL);
    defineMethodObject("(DEFMETHOD (FOURTH CHARACTER) ((SELF STRING)) :DOCUMENTATION \"Return the fourth character of `self'.\" :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (NTH SELF 3)))", wrapFunctionCode(((cpp_function_code)(((char  (*) (const char*))(&stringFourth))))), NULL);
    defineMethodObject("(DEFMETHOD (FOURTH CHARACTER) ((SELF MUTABLE-STRING)) :DOCUMENTATION \"Return the fourth character of `self' (settable via `setf').\" :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (NTH SELF 3)))", wrapFunctionCode(((cpp_function_code)(((char  (*) (char*))(&mutableStringFourth))))), NULL);
    defineMethodObject("(DEFMETHOD (FOURTH-SETTER CHARACTER) ((SELF MUTABLE-STRING) (CH CHARACTER)) :DOCUMENTATION \"Set the fourth character of `self' to `ch' and return `ch'.\" :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (SETF (NTH SELF 3) CH)))", wrapFunctionCode(((cpp_function_code)(((char  (*) (char*, char))(&mutableStringFourthSetter))))), NULL);
    defineMethodObject("(DEFMETHOD (FIFTH CHARACTER) ((SELF STRING)) :DOCUMENTATION \"Return the fifth character of `self'.\" :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (NTH SELF 4)))", wrapFunctionCode(((cpp_function_code)(((char  (*) (const char*))(&stringFifth))))), NULL);
    defineMethodObject("(DEFMETHOD (FIFTH CHARACTER) ((SELF MUTABLE-STRING)) :DOCUMENTATION \"Return the fifth character of `self' (settable via `setf').\" :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (NTH SELF 4)))", wrapFunctionCode(((cpp_function_code)(((char  (*) (char*))(&mutableStringFifth))))), NULL);
    defineMethodObject("(DEFMETHOD (FIFTH-SETTER CHARACTER) ((SELF MUTABLE-STRING) (CH CHARACTER)) :DOCUMENTATION \"Set the fifth character of `self' to `ch' and return `ch'.\" :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (SETF (NTH SELF 4) CH)))", wrapFunctionCode(((cpp_function_code)(((char  (*) (char*, char))(&mutableStringFifthSetter))))), NULL);
    defineMethodObject("(DEFMETHOD (NTH CHARACTER) ((SELF STRING) (POSITION INTEGER)) :DOCUMENTATION \"Return the character in `self' at `position'.\" :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF) (CL:THE CL:FIXNUM POSITION)) :CPP \"self[position]\" :JAVA \"self.charAt(position)\")))", wrapFunctionCode(((cpp_function_code)(((char  (*) (const char*, int))(&stringNth))))), NULL);
    defineMethodObject("(DEFMETHOD (NTH CHARACTER) ((SELF MUTABLE-STRING) (POSITION INTEGER)) :DOCUMENTATION \"Return the character in `self' at `position'.\" :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF) (CL:THE CL:FIXNUM POSITION)) :CPP \"self[position]\" :JAVA \"self.charAt(position)\")))", wrapFunctionCode(((cpp_function_code)(((char  (*) (char*, int))(&mutableStringNth))))), NULL);
    defineMethodObject("(DEFMETHOD (NTH-SETTER CHARACTER) ((SELF MUTABLE-STRING) (CH CHARACTER) (POSITION INTEGER)) :DOCUMENTATION \"Set the character in `self' at `position' to `ch'.\" :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (VERBATIM :COMMON-LISP (SETF (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF) (CL:THE CL:FIXNUM POSITION)) (CL:THE CL:CHARACTER CH)) :CPP \"self[position] = ch\" :JAVA \"#$(STELLAROOT).javalib.Native.mutableString_nthSetter(self, ch, position)\")))", wrapFunctionCode(((cpp_function_code)(((char  (*) (char*, char, int))(&mutableStringNthSetter))))), NULL);
    defineMethodObject("(DEFMETHOD (REST STRING) ((SELF STRING)) :NATIVE? TRUE :PUBLIC? TRUE)", wrapFunctionCode(((cpp_function_code)(((const char*  (*) (const char*))(&stringRest))))), NULL);
    defineMethodObject("(DEFMETHOD (LENGTH INTEGER) ((SELF STRING)) :DOCUMENTATION \"Return the length of the string `self'.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:LENGTH SELF) :CPP \"strlen(self)\" :JAVA \"self.length()\")))", wrapFunctionCode(((cpp_function_code)(((int  (*) (const char*))(&stringLength))))), NULL);
    defineMethodObject("(DEFMETHOD (LENGTH INTEGER) ((SELF MUTABLE-STRING)) :DOCUMENTATION \"Return the length of the string `self'.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:LENGTH SELF) :CPP \"strlen(self)\" :JAVA \"self.length()\")))", wrapFunctionCode(((cpp_function_code)(((int  (*) (char*))(&mutableStringLength))))), NULL);
    defineMethodObject("(DEFMETHOD (POSITION INTEGER) ((STRING STRING) (CHARACTER CHARACTER) (START INTEGER)) :DOCUMENTATION \"Return the position of `character' within `string' (counting\nfrom zero); or return NULL if `character' does not occur within `string'.\nIf `start' was supplied as non-NULL, only consider the substring starting\nat `start', however, the returned position will always be relative to the\nentire string.\" :NATIVE? TRUE :PUBLIC? TRUE)", wrapFunctionCode(((cpp_function_code)(((int  (*) (const char*, char, int))(&stringPosition))))), NULL);
    defineMethodObject("(DEFMETHOD (LAST-POSITION INTEGER) ((STRING STRING) (CHARACTER CHARACTER) (END INTEGER)) :DOCUMENTATION \"Return the last position of `character' within `string'\n(counting from zero); or return NULL if `character' does not occur \nwithin `string'.  If `end' was supplied as non-NULL, only consider\nthe substring ending at `end', however, the returned position will\nalways be relative to the entire string.\" :NATIVE? TRUE :PUBLIC? TRUE)", wrapFunctionCode(((cpp_function_code)(((int  (*) (const char*, char, int))(&stringLastPosition))))), NULL);
    defineFunctionObject("STRING-SEARCH", "(DEFUN (STRING-SEARCH INTEGER) ((STRING STRING) (SUBSTRING STRING) (START INTEGER)) :DOCUMENTATION \"Return start position of the left-most occurrence of\n`substring' in `string', beginning from `start'.  Return NULL if it is not\na substring.  The comparison is exact.\" :NATIVE? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(((int  (*) (const char*, const char*, int))(&stringSearch)))), NULL);
    defineFunctionObject("STRING-SEARCH-IGNORE-CASE", "(DEFUN (STRING-SEARCH-IGNORE-CASE INTEGER) ((STRING STRING) (SUBSTRING STRING) (START INTEGER)) :DOCUMENTATION \"Return start position of the left-most occurrence of\n`substring' in `string', beginning from `start'.  Return NULL if it is not\na substring.  The comparison ignores differences in letter case.\" :PUBLIC? TRUE)", ((cpp_function_code)(((int  (*) (const char*, const char*, int))(&stringSearchIgnoreCase)))), NULL);
    defineFunctionObject("STARTS-WITH?", "(DEFUN (STARTS-WITH? BOOLEAN) ((STRING STRING) (PREFIX STRING) (START INTEGER)) :DOCUMENTATION \"Return TRUE if `string' starts with `prefix' starting from\n`start' (which defaults to 0 if it is supplied as NULL).\" :PUBLIC? TRUE)", ((cpp_function_code)(&startsWithP)), NULL);
    defineFunctionObject("ENDS-WITH?", "(DEFUN (ENDS-WITH? BOOLEAN) ((STRING STRING) (SUFFIX STRING) (END INTEGER)) :DOCUMENTATION \"Return TRUE if the substring of `string' ending at `end'\nends with `suffix'.  If `end' is NULL it defaults to the length of `string'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&endsWithP)), NULL);
    defineFunctionObject("HELP-FIND-MATCHING-PREFIX-LENGTH", "(DEFUN (HELP-FIND-MATCHING-PREFIX-LENGTH INTEGER) ((STRING1 STRING) (START1 INTEGER) (END1 INTEGER) (STRING2 STRING) (START2 INTEGER) (END2 INTEGER)) :PUBLIC? FALSE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"Helping function for `find-matching-prefix' that requires `end1' and `end2'\nto be properly set up.\" (LET ((I1 START1) (I2 START2)) (WHILE (AND (< I1 END1) (< I2 END2) (EQL? (NTH STRING1 I1) (NTH STRING2 I2))) (++ I1) (++ I2)) (RETURN (- I1 START1))))", ((cpp_function_code)(&helpFindMatchingPrefixLength)), NULL);
    defineFunctionObject("FIND-MATCHING-PREFIX-LENGTH", "(DEFUN (FIND-MATCHING-PREFIX-LENGTH INTEGER) ((STRING1 STRING) (START1 INTEGER) (END1 INTEGER) (STRING2 STRING) (START2 INTEGER) (END2 INTEGER)) :PUBLIC? TRUE :DOCUMENTATION \"Finds the length of the matching prefix strings of `string1' and\n`string2', starting at position `start1' and `start2' respectively.\nThe search will end when `end1' or `end2' is reached.  If either `end1'\nor `end2' is null, then they will be set to the length of their respective\nstrings.\")", ((cpp_function_code)(&findMatchingPrefixLength)), NULL);
    defineFunctionObject("FIND-MISMATCH", "(DEFUN (FIND-MISMATCH INTEGER INTEGER) ((STRING1 STRING) (START1 INTEGER) (END1 INTEGER) (STRING2 STRING) (START2 INTEGER) (END2 INTEGER)) :PUBLIC? TRUE :DOCUMENTATION \"Finds the first position in each of `string1' and `string2' where\nthey mismatch, starting at position `start1' and `start2' respectively.\nThe search will end when `end1' or `end2' is reached.  If either `end1'\nor `end2' is null, then they will be set to the length of their respective\nstrings.  If there is no mismatch, then `null' values are returned.\")", ((cpp_function_code)(&findMismatch)), NULL);
  }
}

void helpStartupPrimal5() {
  {
    defineFunctionObject("NON-MATCHING-POSITION-HELPER", "(DEFUN (NON-MATCHING-POSITION-HELPER INTEGER) ((SOURCE STRING) (START INTEGER) (END INTEGER) (MATCH STRING)) :PUBLIC? FALSE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"Helper for `non-matching-position' that requires `end' to not be `null'.\" (WHILE (AND (< START END) (MEMBER? MATCH (NTH SOURCE START))) (++ START)) (RETURN START))", ((cpp_function_code)(&nonMatchingPositionHelper)), NULL);
    defineFunctionObject("NON-MATCHING-POSITION", "(DEFUN (NON-MATCHING-POSITION INTEGER) ((SOURCE STRING) (START INTEGER) (MATCH STRING)) :PUBLIC? TRUE :DOCUMENTATION \"Returns the index into `source', starting from `start', of the first\ncharacter that is not included in `match'.\")", ((cpp_function_code)(&nonMatchingPosition)), NULL);
    defineFunctionObject("HELP-ADVANCE-PAST-WHITESPACE", "(DEFUN (HELP-ADVANCE-PAST-WHITESPACE INTEGER) ((SOURCE STRING) (START INTEGER) (END INTEGER)) :PUBLIC? FALSE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"Helper for `advance-past-whitespace' that requires `end' to be properly set.\" (WHILE (AND (< START END) (WHITE-SPACE-CHARACTER? (NTH SOURCE START))) (++ START)) (RETURN START))", ((cpp_function_code)(&helpAdvancePastWhitespace)), NULL);
    defineFunctionObject("ADVANCE-PAST-WHITESPACE", "(DEFUN (ADVANCE-PAST-WHITESPACE INTEGER) ((SOURCE STRING) (START INTEGER)) :PUBLIC? TRUE :DOCUMENTATION \"Returns the first index into `source', starting from `start', of\nthe first character that is not white space.\")", ((cpp_function_code)(&advancePastWhitespace)), NULL);
    defineFunctionObject("EQL-EXCEPT-IN-WHITESPACE?", "(DEFUN (EQL-EXCEPT-IN-WHITESPACE? BOOLEAN) ((S1 STRING) (S2 STRING)) :PUBLIC? TRUE :DOCUMENTATION \"Return `true' if the strings `s1' and `s2' are the same\nexcept for the amounts of whitespace separating words.  Leading or\ntrailing whitespace is also not considered.\")", ((cpp_function_code)(&eqlExceptInWhitespaceP)), NULL);
    defineMethodObject("(DEFMETHOD (SUBSEQUENCE STRING) ((STRING STRING) (START INTEGER) (END INTEGER)) :DOCUMENTATION \"Return a substring of `string' beginning at position `start'\nand ending up to but not including position `end', counting from zero.  An\n`end' value of NULL stands for the rest of the string.\" :NATIVE? TRUE :PUBLIC? TRUE)", wrapFunctionCode(((cpp_function_code)(((const char*  (*) (const char*, int, int))(&stringSubsequence))))), NULL);
    defineMethodObject("(DEFMETHOD (SUBSEQUENCE STRING) ((STRING MUTABLE-STRING) (START INTEGER) (END INTEGER)) :DOCUMENTATION \"Return a substring of `string' beginning at position `start'\nand ending up to but not including position `end', counting from zero.  An\n`end' value of NULL stands for the rest of the string.\" :NATIVE? TRUE :PUBLIC? TRUE)", wrapFunctionCode(((cpp_function_code)(((const char*  (*) (char*, int, int))(&mutableStringSubsequence))))), NULL);
    defineFunctionObject("SPLIT-STRING", "(DEFUN (SPLIT-STRING (CONS OF STRING-WRAPPER)) ((INPUT STRING) (SEPARATOR CHARACTER)) :DOCUMENTATION \"Split `input' into separate strings based on the `separator' character.\" :PUBLIC? TRUE)", ((cpp_function_code)(&splitString)), NULL);
    defineFunctionObject("STRINGIFY", "(DEFUN (STRINGIFY STRING) ((EXPRESSION OBJECT)) :DOCUMENTATION \"Print `expression' onto a string and return the result.\nPrinting is done with `*printReadably?*' set to true and with `*printPretty?*'\nset to false.\" :NATIVE? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&stringify)), NULL);
    defineFunctionObject("UNSTRINGIFY", "(DEFUN (UNSTRINGIFY OBJECT) ((STRING STRING)) :DOCUMENTATION \"Read a STELLA expression from `string' and return the result.\nThis is identical to `read-s-expression-from-string'.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (READ-S-EXPRESSION-FROM-STRING STRING)))", ((cpp_function_code)(&unstringify)), NULL);
    defineMethodObject("(DEFMETHOD FREE-HASH-TABLE-VALUES ((SELF ABSTRACT-HASH-TABLE)) :DOCUMENTATION \"Call free on each value in the hash table `self'.\")", wrapMethodCode(((cpp_method_code)(&AbstractHashTable::freeHashTableValues))), NULL);
    defineMethodObject("(DEFMETHOD INITIALIZE-HASH-TABLE ((SELF ABSTRACT-HASH-TABLE)) :DOCUMENTATION \"Insert a newly-created native hash table into `self'.\")", wrapMethodCode(((cpp_method_code)(&AbstractHashTable::initializeHashTable))), NULL);
    defineMethodObject("(DEFMETHOD (LOOKUP (LIKE (ANY-VALUE SELF))) ((SELF HASH-TABLE) (KEY (LIKE (ANY-KEY SELF)))) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&HashTable::lookup))), NULL);
    defineMethodObject("(DEFMETHOD INSERT-AT ((SELF HASH-TABLE) (KEY (LIKE (ANY-KEY SELF))) (VALUE (LIKE (ANY-VALUE SELF)))) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&HashTable::insertAt))), NULL);
    defineMethodObject("(DEFMETHOD REMOVE-AT ((SELF HASH-TABLE) (KEY (LIKE (ANY-KEY SELF)))) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&HashTable::removeAt))), NULL);
    defineMethodObject("(DEFMETHOD INITIALIZE-HASH-TABLE ((SELF INTEGER-HASH-TABLE)) :DOCUMENTATION \"Insert a newly-created native hash table into `self'.\")", wrapMethodCode(((cpp_method_code)(&IntegerHashTable::initializeHashTable))), NULL);
    defineMethodObject("(DEFMETHOD (LOOKUP (LIKE (ANY-VALUE SELF))) ((SELF INTEGER-HASH-TABLE) (KEY INTEGER)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&IntegerHashTable::lookup))), NULL);
    defineMethodObject("(DEFMETHOD INSERT-AT ((SELF INTEGER-HASH-TABLE) (KEY INTEGER) (VALUE OBJECT)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&IntegerHashTable::insertAt))), NULL);
    defineMethodObject("(DEFMETHOD REMOVE-AT ((SELF INTEGER-HASH-TABLE) (KEY (LIKE (ANY-KEY SELF)))))", wrapMethodCode(((cpp_method_code)(&IntegerHashTable::removeAt))), NULL);
    defineMethodObject("(DEFMETHOD INITIALIZE-HASH-TABLE ((SELF FLOAT-HASH-TABLE)) :DOCUMENTATION \"Insert a newly-created native hash table into `self'.\")", wrapMethodCode(((cpp_method_code)(&FloatHashTable::initializeHashTable))), NULL);
    defineMethodObject("(DEFMETHOD (LOOKUP (LIKE (ANY-VALUE SELF))) ((SELF FLOAT-HASH-TABLE) (KEY FLOAT)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&FloatHashTable::lookup))), NULL);
    defineMethodObject("(DEFMETHOD INSERT-AT ((SELF FLOAT-HASH-TABLE) (KEY FLOAT) (VALUE OBJECT)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&FloatHashTable::insertAt))), NULL);
    defineMethodObject("(DEFMETHOD REMOVE-AT ((SELF FLOAT-HASH-TABLE) (KEY (LIKE (ANY-KEY SELF)))))", wrapMethodCode(((cpp_method_code)(&FloatHashTable::removeAt))), NULL);
    defineMethodObject("(DEFMETHOD INITIALIZE-HASH-TABLE ((SELF STRING-HASH-TABLE)) :DOCUMENTATION \"Insert a newly-created native hash table into `self'.\")", wrapMethodCode(((cpp_method_code)(&StringHashTable::initializeHashTable))), NULL);
    defineMethodObject("(DEFMETHOD (LOOKUP (LIKE (ANY-VALUE SELF))) ((SELF STRING-HASH-TABLE) (KEY STRING)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&StringHashTable::lookup))), NULL);
    defineMethodObject("(DEFMETHOD INSERT-AT ((SELF STRING-HASH-TABLE) (KEY STRING) (VALUE OBJECT)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&StringHashTable::insertAt))), NULL);
    defineMethodObject("(DEFMETHOD REMOVE-AT ((SELF STRING-HASH-TABLE) (KEY STRING)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&StringHashTable::removeAt))), NULL);
    defineMethodObject("(DEFMETHOD INITIALIZE-HASH-TABLE ((SELF STRING-TO-INTEGER-HASH-TABLE)) :DOCUMENTATION \"Insert a newly-created native hash table into `self'.\")", wrapMethodCode(((cpp_method_code)(&StringToIntegerHashTable::initializeHashTable))), NULL);
    defineMethodObject("(DEFMETHOD (LOOKUP INTEGER) ((SELF STRING-TO-INTEGER-HASH-TABLE) (KEY STRING)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&StringToIntegerHashTable::lookup))), NULL);
    defineMethodObject("(DEFMETHOD INSERT-AT ((SELF STRING-TO-INTEGER-HASH-TABLE) (KEY STRING) (VALUE INTEGER)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&StringToIntegerHashTable::insertAt))), NULL);
    defineMethodObject("(DEFMETHOD REMOVE-AT ((SELF STRING-TO-INTEGER-HASH-TABLE) (KEY STRING)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&StringToIntegerHashTable::removeAt))), NULL);
    defineFunctionObject("HASHMOD", "(DEFUN (HASHMOD INTEGER) ((CODE INTEGER) (SIZE INTEGER)) :DOCUMENTATION \"Map the hash code `code' onto a bucket index for a hash table\nof `size' (i.e., onto the interval [0..size-1].  This is just like `rem' for\npositive hash codes but also works for negative hash codes by mapping those\nonto a positive number first.  Note, that the sign conversion mapping is not\nequivalent to calling the `abs' function (it simply masks the sign bit for\nspeed) and therefore really only makes sense for hash codes.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:REM (CL:THE CL:FIXNUM (CL:LOGAND CODE *INTEGER-UNSIGNED-BITS-MASK*)) SIZE) :CPP \"(((unsigned int) code) % size)\" :JAVA \"((code & 0x7FFFFFFF) % size)\")))", ((cpp_function_code)(&hashmod)), NULL);
    defineFunctionObject("ROTATE-HASH-CODE", "(DEFUN (ROTATE-HASH-CODE INTEGER) ((ARG INTEGER)) :DOCUMENTATION \"Rotate `arg' to the right by 1 position.  This means shift `arg' to the right\nby one and feed in `arg's bit zero from the left.  In Lisp the result will stay\nin positive FIXNUM range.  In C++ and Java this might return a negative\nvalue which might be equal to NULL-INTEGER.  Important: to make this inlinable,\nit must be called with an atom (i.e., constant or variable) as its argument.\nThis function is primarily useful for hashing sequences of items where the hash\ncode should take the sequential order of elements into account (e.g., lists).\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (CHOOSE (= (LOGAND ARG 1) 0) (UNSIGNED-SHIFT-RIGHT-BY-1 ARG) (LOGOR (SHIFT-RIGHT ARG 1) *INTEGER-MSB-MASK*))))", ((cpp_function_code)(&rotateHashCode)), NULL);
    defineFunctionObject("OBJECT-HASH-CODE", "(DEFUN (OBJECT-HASH-CODE INTEGER) ((SELF OBJECT)) :DOCUMENTATION \"Return a hash code for `self' (can be negative).  Two objects that are `eq?'\nare guaranteed to generate the same hash code.  Two objects that are not `eq?'\ndo not necessarily generate different hash codes.  Similar to `hash-code' but\nalways hashes on the address of `self' even if it is a wrapper.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (VERBATIM :COMMON-LISP \"(STELLA::%%OBJECT-HASH-CODE SELF)\" :CPP \"(size_t)self\" :JAVA \"self.hashCode()\")))", ((cpp_function_code)(&objectHashCode)), NULL);
    defineMethodObject("(DEFMETHOD (HASH-CODE INTEGER) ((SELF OBJECT)) :DOCUMENTATION \"Return a hash code for `self' (can be negative).  Two objects that are `eql?'\nare guaranteed to generate the same hash code.  Two objects that are not `eql?'\ndo not necessarily generate different hash codes.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Object::hashCode))), NULL);
    defineFunctionObject("SAFE-HASH-CODE", "(DEFUN (SAFE-HASH-CODE INTEGER) ((SELF OBJECT)) :DOCUMENTATION \"Return a hash code for `self'.  Just like `hash-code'\n- which see, but also works for NULL.\" :PUBLIC? TRUE)", ((cpp_function_code)(&safeHashCode)), NULL);
    defineMethodObject("(DEFMETHOD (HASH-CODE INTEGER) ((SELF STANDARD-OBJECT)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (OBJECT-HASH-CODE SELF)))", wrapMethodCode(((cpp_method_code)(&StandardObject::hashCode))), NULL);
    defineMethodObject("(DEFMETHOD (HASH-CODE INTEGER) ((SELF WRAPPER)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Wrapper::hashCode))), NULL);
    defineMethodObject("(DEFMETHOD (HASH-CODE INTEGER) ((SELF STRING-WRAPPER)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (HASH-CODE (WRAPPER-VALUE SELF))))", wrapMethodCode(((cpp_method_code)(&StringWrapper::hashCode))), NULL);
    defineMethodObject("(DEFMETHOD (HASH-CODE INTEGER) ((SELF INTEGER-WRAPPER)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (HASH-CODE (WRAPPER-VALUE SELF))))", wrapMethodCode(((cpp_method_code)(&IntegerWrapper::hashCode))), NULL);
    defineMethodObject("(DEFMETHOD (HASH-CODE INTEGER) ((SELF LONG-INTEGER-WRAPPER)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (HASH-CODE (WRAPPER-VALUE SELF))))", wrapMethodCode(((cpp_method_code)(&LongIntegerWrapper::hashCode))), NULL);
    defineMethodObject("(DEFMETHOD (HASH-CODE INTEGER) ((SELF FLOAT-WRAPPER)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (HASH-CODE (WRAPPER-VALUE SELF))))", wrapMethodCode(((cpp_method_code)(&FloatWrapper::hashCode))), NULL);
    defineMethodObject("(DEFMETHOD (HASH-CODE INTEGER) ((SELF CHARACTER-WRAPPER)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (HASH-CODE (WRAPPER-VALUE SELF))))", wrapMethodCode(((cpp_method_code)(&CharacterWrapper::hashCode))), NULL);
    defineMethodObject("(DEFMETHOD (HASH-CODE INTEGER) ((SELF BOOLEAN-WRAPPER)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (CHOOSE (WRAPPER-VALUE SELF) 7333705 1891526)))", wrapMethodCode(((cpp_method_code)(&BooleanWrapper::hashCode))), NULL);
    defineMethodObject("(DEFMETHOD (HASH-CODE INTEGER) ((SELF STRING)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:SXHASH SELF) :JAVA \"self.hashCode()\" :CPP \"native_hash_string(self)\" :OTHERWISE (HASH-STRING SELF 0))))", wrapFunctionCode(((cpp_function_code)(((int  (*) (const char*))(&stringHashCode))))), NULL);
    defineMethodObject("(DEFMETHOD (HASH-CODE INTEGER) ((SELF INTEGER)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN SELF))", wrapFunctionCode(((cpp_function_code)(((int  (*) (int))(&integerHashCode))))), NULL);
    defineMethodObject("(DEFMETHOD (HASH-CODE INTEGER) ((SELF LONG-INTEGER)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (CAST (LOGAND (LOGXOR SELF (SHIFT-RIGHT SELF 32)) MOST-POSITIVE-INTEGER) INTEGER)))", wrapFunctionCode(((cpp_function_code)(((int  (*) (long long int))(&longIntegerHashCode))))), NULL);
    defineMethodObject("(DEFMETHOD (HASH-CODE INTEGER) ((SELF FLOAT)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:SXHASH SELF) :CPP \"(size_t)self\" :JAVA \"(int)(Double.doubleToLongBits(self)^(Double.doubleToLongBits(self)>>>32))\")))", wrapFunctionCode(((cpp_function_code)(((int  (*) (double))(&floatHashCode))))), NULL);
    defineMethodObject("(DEFMETHOD (HASH-CODE INTEGER) ((SELF CHARACTER)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (LOGXOR (AREF *HASH-BYTE-RANDOM-TABLE* (CHARACTER-CODE SELF)) 15119378)))", wrapFunctionCode(((cpp_function_code)(((int  (*) (char))(&characterHashCode))))), NULL);
    defineMethodObject("(DEFMETHOD (EQUAL-HASH-CODE INTEGER) ((SELF OBJECT)) :DOCUMENTATION \"Return a hash code for `self' (can be negative).  Two objects that are `equal?'\nare guaranteed to generate the same hash code (provided, that writers of\n`object-equal?' methods also implemented the appropriate `equal-hash-code'\nmethod).  Two objects that are not `equal?'do not necessarily generate different\nhash codes.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Object::equalHashCode))), NULL);
    defineFunctionObject("SAFE-EQUAL-HASH-CODE", "(DEFUN (SAFE-EQUAL-HASH-CODE INTEGER) ((SELF OBJECT)) :DOCUMENTATION \"Return a hash code for `self'.  Just like `equal-hash-code'\n- which see, but also works for NULL.  `equal-hash-code' methods that expect to\nhandle NULL components should use this function for recursive calls.\" :PUBLIC? TRUE)", ((cpp_function_code)(&safeEqualHashCode)), NULL);
    defineFunctionObject("HASH-STRING", "(DEFUN (HASH-STRING INTEGER) ((STRING STRING) (SEEDCODE INTEGER)) :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE :DOCUMENTATION \"Generate a hash-code for `string' and return it.\nTwo strings that are equal but not eq will generate the same code.\nThe hash-code is based on `seedCode' which usually will be 0.  However,\n`seedCode' can also be used to supply the result of a previous hash\noperation to achieve hashing on sequences of strings without actually\nhaving to concatenate them.\" (LET ((CODE SEEDCODE) (CURSOR (LENGTH STRING))) (IF (= CURSOR 0) (RETURN 4303803) (-- CURSOR)) (LOOP (SETQ CODE (LOGXOR CODE (AREF *HASH-BYTE-RANDOM-TABLE* (CHARACTER-CODE (NTH STRING CURSOR))))) (IF (= CURSOR 0) (BREAK) (-- CURSOR)) (SETQ CODE (ROTATE-HASH-CODE CODE))) (RETURN CODE)))", ((cpp_function_code)(&hashString)), NULL);
    defineFunctionObject("PICK-HASH-TABLE-SIZE-PRIME", "(DEFUN (PICK-HASH-TABLE-SIZE-PRIME INTEGER) ((MINSIZE INTEGER)) :DOCUMENTATION \"Return a hash table prime of at least `minSize'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&pickHashTableSizePrime)), NULL);
    defineMethodObject("(DEFMETHOD INITIALIZE-VECTOR ((SELF VECTOR)))", wrapMethodCode(((cpp_method_code)(&Vector::initializeVector))), NULL);
    defineFunctionObject("RESIZE-VECTOR", "(DEFUN RESIZE-VECTOR ((SELF VECTOR) (SIZE INTEGER)) :DOCUMENTATION \"Change the size of `self' to `size'.  If `size' is smaller\nthan the current size of `self' the vector will be truncated.  Otherwise, \nthe internal array of `self' will be grown to `size' and unused elements\nwill be initialized to NULL.\" :PUBLIC? TRUE)", ((cpp_function_code)(&resizeVector)), NULL);
    defineMethodObject("(DEFMETHOD (NTH (LIKE (ANY-VALUE SELF))) ((SELF NATIVE-VECTOR) (POSITION INTEGER)) :DOCUMENTATION \"Return the element in `self' at `position'.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:AREF SELF POSITION) :CPP \"self[position]\" :JAVA \"self[position]\")))", wrapFunctionCode(((cpp_function_code)(((Object*  (*) (Object**, int))(&nativeVectorNth))))), NULL);
    defineMethodObject("(DEFMETHOD (NTH-SETTER (LIKE (ANY-VALUE SELF))) ((SELF NATIVE-VECTOR) (VALUE (LIKE (ANY-VALUE SELF))) (POSITION INTEGER)) :DOCUMENTATION \"Set the element in `self' at `position' to `value'.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:SETF (CL:AREF SELF POSITION) VALUE) :CPP \"self[position] = value\" :JAVA \"self[position] = value\")))", wrapFunctionCode(((cpp_function_code)(((Object*  (*) (Object**, Object*, int))(&nativeVectorNthSetter))))), NULL);
    defineFunctionObject("UNMAKE", "(DEFUN UNMAKE ((SELF OBJECT)))", ((cpp_function_code)(&unmake)), NULL);
    defineFunctionObject("NATIVE-PROBE-FILE?", "(DEFUN (NATIVE-PROBE-FILE? BOOLEAN) ((FILENAME FILE-NAME)) :DOCUMENTATION \"Return true if file `fileName' exists.  Note that this does\nnot necessarily mean that the file can also be read.  This does not handle any\nnecessary pathname translations or error conditions.\" :NATIVE? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&nativeProbeFileP)), NULL);
    defineFunctionObject("NATIVE-PROBE-DIRECTORY?", "(DEFUN (NATIVE-PROBE-DIRECTORY? BOOLEAN) ((FILENAME FILE-NAME)) :DOCUMENTATION \"Return true if file `fileName' exists and is a directory.\nNote that this does not necessarily mean that the directory can also be read.\nThis does not handle any necessary pathname translations or error conditions.\" :PUBLIC? TRUE)", ((cpp_function_code)(&nativeProbeDirectoryP)), NULL);
  }
}

void helpStartupPrimal6() {
  {
    defineFunctionObject("PROBE-FILE?", "(DEFUN (PROBE-FILE? BOOLEAN) ((FILENAME FILE-NAME)) :DOCUMENTATION \"Return true if file `fileName' exists.  Note that this does\nnot necessarily mean that the file can also be read.\nIMPORTANT Java idiosyncrasy: if file `foo/bar' exists and is not a directory,\nJava will also say `foo/bar/' exists, which is different behavior than in Lisp\nand C++.  For this reason, make sure to always use `probe-directory?' to test\nwhether a directory exists.\" :PUBLIC? TRUE)", ((cpp_function_code)(&probeFileP)), NULL);
    defineFunctionObject("PROBE-DIRECTORY?", "(DEFUN (PROBE-DIRECTORY? BOOLEAN) ((FILENAME FILE-NAME)) :DOCUMENTATION \"Return true if file `fileName' exists and is a directory.\nNote that this does not necessarily mean that the directory can also be read.\" :PUBLIC? TRUE)", ((cpp_function_code)(&probeDirectoryP)), NULL);
    defineFunctionObject("NATIVE-FILE-WRITE-DATE", "(DEFUN (NATIVE-FILE-WRITE-DATE CALENDAR-DATE) ((FILENAME FILE-NAME)) :DOCUMENTATION \"Return the time at which file `fileName' was last modified or\nNULL if that cannot be determined.  This does not handle any necessary pathname\ntranslations or error conditions.\" :NATIVE? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&nativeFileWriteDate)), NULL);
    defineFunctionObject("FILE-WRITE-DATE", "(DEFUN (FILE-WRITE-DATE CALENDAR-DATE) ((FILENAME FILE-NAME)) :DOCUMENTATION \"Return the time at which file `fileName' was last modified or\nNULL if that cannot be determined.\" :PUBLIC? TRUE)", ((cpp_function_code)(&fileWriteDate)), NULL);
    defineFunctionObject("NATIVE-FILE-LENGTH", "(DEFUN (NATIVE-FILE-LENGTH LONG-INTEGER) ((FILENAME FILE-NAME)) :DOCUMENTATION \"Return the length of file `fileName' in bytes or NULL if that\ncannot be determined.  This does not handle any necessary pathname translations\nor error conditions.\" :NATIVE? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&nativeFileLength)), NULL);
    defineFunctionObject("FILE-LENGTH", "(DEFUN (FILE-LENGTH LONG-INTEGER) ((FILENAME FILE-NAME)) :DOCUMENTATION \"Return the length of file `fileName' in bytes or NULL if that\ncannot be determined.\" :PUBLIC? TRUE)", ((cpp_function_code)(&fileLength)), NULL);
    defineFunctionObject("NATIVE-DELETE-FILE", "(DEFUN NATIVE-DELETE-FILE ((FILENAME FILE-NAME)) :DOCUMENTATION \"Delete the file `fileName'.  This does not handle any necessary\npathname translations or error conditions.\" :NATIVE? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&nativeDeleteFile)), NULL);
    defineFunctionObject("DELETE-FILE", "(DEFUN DELETE-FILE ((FILENAME FILE-NAME)) :DOCUMENTATION \"Delete the file `fileName'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&deleteFile)), NULL);
    defineFunctionObject("NATIVE-RENAME-FILE", "(DEFUN NATIVE-RENAME-FILE ((FROMFILE FILE-NAME) (TOFILE FILE-NAME)) :DOCUMENTATION \"Rename the file `fromFile' to `toFile'.  This does not handle\nany necessary pathname translations or error conditions.\" :NATIVE? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&nativeRenameFile)), NULL);
    defineFunctionObject("RENAME-FILE", "(DEFUN RENAME-FILE ((FROMFILE FILE-NAME) (TOFILE FILE-NAME)) :DOCUMENTATION \"Rename the file `fromFile' to `toFile'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&renameFile)), NULL);
    defineFunctionObject("COPY-STREAM-TO-STREAM", "(DEFUN COPY-STREAM-TO-STREAM ((IN INPUT-STREAM) (OUT OUTPUT-STREAM)) :DOCUMENTATION \"Copy `in' verbatimely to `out'.  Does the right thing for binary data.\" :PUBLIC? TRUE)", ((cpp_function_code)(&copyStreamToStream)), NULL);
    defineFunctionObject("COPY-FILE", "(DEFUN COPY-FILE ((FROMFILE FILE-NAME) (TOFILE FILE-NAME)) :DOCUMENTATION \"Copy file `fromFile' to file `toFile', clobbering\nany data already in `toFile'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&copyFile)), NULL);
    defineFunctionObject("GET-TEMP-DIRECTORY", "(DEFUN (GET-TEMP-DIRECTORY STRING) () :DOCUMENTATION \"Return a suitable directory for temporary files.\nUses the value of `stella.tempDirectory' if defined; otherwise, it\nwill use a suitable OS-specific default.  The returned directory will\nend in a separator for immediate concatenation with a physical filename.\" :PUBLIC? TRUE)", ((cpp_function_code)(&getTempDirectory)), NULL);
    defineFunctionObject("MAKE-TEMPORARY-FILE-NAME", "(DEFUN (MAKE-TEMPORARY-FILE-NAME STRING) ((PREFIX STRING) (SUFFIX STRING)) :DOCUMENTATION \"Return a file name of the form `<prefix>NNNNNN<suffix>'\nwhich is guaranteed to not refer to any existing file.  A null `prefix'\ndefaults to `tmpfile', a null `suffix' defaults to the empty string.\nThe number portion NNNNNN will correpond to a random number between 0\nand 999999.  If no qualifying filename can be found after 100 attempts,\nNULL will be returned.  Note that it is possible due to multi-threading\nor processing that the generated filename becomes used by another thread\nor OS process.  If necessary, this case can be handled by the caller.\" :PUBLIC? TRUE)", ((cpp_function_code)(&makeTemporaryFileName)), NULL);
    defineFunctionObject("MAKE-TEMPORARY-FILE", "(DEFUN (MAKE-TEMPORARY-FILE STRING) ((PREFIX STRING) (SUFFIX STRING)) :DOCUMENTATION \"Variant of `make-temporary-file-name' that actually\nallocates the file to prevent other processes from using that name.\nThis is still not fully thread safe - for that we would need a file lock -\nbut maybe a bit better in avoiding collisions.\" :PUBLIC? TRUE)", ((cpp_function_code)(&makeTemporaryFile)), NULL);
    defineFunctionObject("CL-LIST-DIRECTORY-FILES", "(DEFUN (CL-LIST-DIRECTORY-FILES (CONS OF STRING-WRAPPER)) ((DIRECTORY STRING)))", ((cpp_function_code)(&clListDirectoryFiles)), NULL);
    defineFunctionObject("CPP-LIST-DIRECTORY-FILES", "(DEFUN (CPP-LIST-DIRECTORY-FILES (CONS OF STRING-WRAPPER)) ((DIRECTORY STRING)))", ((cpp_function_code)(&cppListDirectoryFiles)), NULL);
    defineFunctionObject("JAVA-LIST-DIRECTORY-FILES", "(DEFUN (JAVA-LIST-DIRECTORY-FILES (CONS OF STRING-WRAPPER)) ((DIRECTORY STRING)))", ((cpp_function_code)(&javaListDirectoryFiles)), NULL);
    defineFunctionObject("LIST-DIRECTORY-FILES", "(DEFUN (LIST-DIRECTORY-FILES (CONS OF STRING-WRAPPER)) ((DIRECTORY STRING)) :DOCUMENTATION \"Return all the files and sub-directories in `directory' sorted by name.\nEach returned file is a bare file name without a `directory' component.  If a file is\na directory, it will look just like a plain file.  This means consumers might have to\nexplicitly test whether a file is a directory depending on what they do. Excludes . and ..\ndirectories.  Handles logical pathnames but resulting files will always use physical pathname\nsyntax.  This is mostly consistent across native languages, but some differences still exist -\ne.g., Lisp will convert . or .. into absolute pathnames.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&listDirectoryFiles)), ((cpp_function_code)(&listDirectoryFilesEvaluatorWrapper)));
    defineFunctionObject("LIST-DIRECTORY-FILES-RECURSIVELY", "(DEFUN (LIST-DIRECTORY-FILES-RECURSIVELY (CONS OF STRING-WRAPPER)) ((DIRECTORY STRING)) :DOCUMENTATION \"Just like `list-directory-files' (which see) but also recurses into\nsubdirectories.  Files at the top level of `directory' will be bare file names without\na `directory' component.  Files in subdirectories will be prefixed with the relative\nsubdirectory path starting right below `directory'.  The sort order is lexicographic\nwithin directories which results in a depth-first presentation order of files.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&listDirectoryFilesRecursively)), ((cpp_function_code)(&listDirectoryFilesRecursivelyEvaluatorWrapper)));
    defineFunctionObject("CPP-CREATE-DIRECTORY", "(DEFUN CPP-CREATE-DIRECTORY ((DIRECTORY STRING)))", ((cpp_function_code)(&cppCreateDirectory)), NULL);
    defineFunctionObject("CREATE-DIRECTORIES", "(DEFUN CREATE-DIRECTORIES ((DIRECTORY STRING)) :DOCUMENTATION \"If `directory' does not yet exist, create it and any of its parents\nthat do not yet exist.  If `directory' already does exist, this simply is a no-op.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&createDirectories)), ((cpp_function_code)(&createDirectoriesEvaluatorWrapper)));
    defineFunctionObject("ENSURE-DIRECTORIES-EXIST", "(DEFUN ENSURE-DIRECTORIES-EXIST ((FILENAME FILE-NAME)) :DOCUMENTATION \"Ensure all physical directories in the directory portion of `fileName' exist.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&ensureDirectoriesExist)), ((cpp_function_code)(&ensureDirectoriesExistEvaluatorWrapper)));
    defineMethodObject("(DEFMETHOD (LOGNOT INTEGER) ((ARG INTEGER)) :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:LOGNOT ARG) :CPP \"(~ arg)\" :JAVA \"(~ arg)\")))", wrapFunctionCode(((cpp_function_code)(((int  (*) (int))(&integerLognot))))), NULL);
    defineMethodObject("(DEFMETHOD (LOGNOT LONG-INTEGER) ((ARG LONG-INTEGER)) :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:LOGNOT ARG) :CPP \"(~ arg)\" :JAVA \"(~ arg)\")))", wrapFunctionCode(((cpp_function_code)(((long long int  (*) (long long int))(&longIntegerLognot))))), NULL);
    defineMethodObject("(DEFMETHOD (LOGAND INTEGER) ((ARG1 INTEGER) (ARG2 INTEGER)) :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:LOGAND ARG1 ARG2) :CPP \"(arg1 & arg2)\" :JAVA \"(arg1 & arg2)\")))", wrapFunctionCode(((cpp_function_code)(((int  (*) (int, int))(&integerLogand))))), NULL);
    defineMethodObject("(DEFMETHOD (LOGAND LONG-INTEGER) ((ARG1 LONG-INTEGER) (ARG2 LONG-INTEGER)) :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:LOGAND ARG1 ARG2) :CPP \"(arg1 & arg2)\" :JAVA \"(arg1 & arg2)\")))", wrapFunctionCode(((cpp_function_code)(((long long int  (*) (long long int, long long int))(&longIntegerLogand))))), NULL);
    defineMethodObject("(DEFMETHOD (LOGOR INTEGER) ((ARG1 INTEGER) (ARG2 INTEGER)) :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:LOGIOR ARG1 ARG2) :CPP \"(arg1 | arg2)\" :JAVA \"(arg1 | arg2)\")))", wrapFunctionCode(((cpp_function_code)(((int  (*) (int, int))(&integerLogor))))), NULL);
    defineMethodObject("(DEFMETHOD (LOGOR LONG-INTEGER) ((ARG1 LONG-INTEGER) (ARG2 LONG-INTEGER)) :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:LOGIOR ARG1 ARG2) :CPP \"(arg1 | arg2)\" :JAVA \"(arg1 | arg2)\")))", wrapFunctionCode(((cpp_function_code)(((long long int  (*) (long long int, long long int))(&longIntegerLogor))))), NULL);
    defineMethodObject("(DEFMETHOD (LOGXOR INTEGER) ((ARG1 INTEGER) (ARG2 INTEGER)) :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:LOGXOR ARG1 ARG2) :CPP \"(arg1 ^ arg2)\" :JAVA \"(arg1 ^ arg2)\")))", wrapFunctionCode(((cpp_function_code)(((int  (*) (int, int))(&integerLogxor))))), NULL);
    defineMethodObject("(DEFMETHOD (LOGXOR LONG-INTEGER) ((ARG1 LONG-INTEGER) (ARG2 LONG-INTEGER)) :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:LOGXOR ARG1 ARG2) :CPP \"(arg1 ^ arg2)\" :JAVA \"(arg1 ^ arg2)\")))", wrapFunctionCode(((cpp_function_code)(((long long int  (*) (long long int, long long int))(&longIntegerLogxor))))), NULL);
    defineFunctionObject("INTEGER-LENGTH", "(DEFUN (INTEGER-LENGTH INTEGER) ((X LONG-INTEGER)) :DOCUMENTATION \"Return the 1-based position of the left-most bit in `x'.\nIf `x' is negative, we only count the value bits, not the sign.\" :PUBLIC? TRUE)", ((cpp_function_code)(((int  (*) (long long int))(&integerLength)))), NULL);
    defineFunctionObject("INTEGER-LENGTH10", "(DEFUN (INTEGER-LENGTH10 INTEGER) ((X LONG-INTEGER)) :DOCUMENTATION \"Return the 1-based position of the left-most non-zero digit\nin the base-10 representation of `x'.  If `x' is negative, we only consider\nits absolute value, not the sign.  This effectively computes the minimum number\nof base-10 digits to represent `x', with the exception of x=0.\" :PUBLIC? TRUE)", ((cpp_function_code)(((int  (*) (long long int))(&integerLength10)))), NULL);
    defineMethodObject("(DEFMETHOD (SHIFT-LEFT INTEGER) ((ARG INTEGER) (COUNT INTEGER)) :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:ASH ARG COUNT) :CPP \"(arg << count)\" :JAVA \"(arg << count)\")))", wrapFunctionCode(((cpp_function_code)(((int  (*) (int, int))(&integerShiftLeft))))), NULL);
    defineMethodObject("(DEFMETHOD (SHIFT-LEFT LONG-INTEGER) ((ARG LONG-INTEGER) (COUNT INTEGER)) :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:ASH ARG COUNT) :CPP \"(arg << count)\" :JAVA \"(arg << count)\")))", wrapFunctionCode(((cpp_function_code)(((long long int  (*) (long long int, int))(&longIntegerShiftLeft))))), NULL);
    defineMethodObject("(DEFMETHOD (SHIFT-RIGHT INTEGER) ((ARG INTEGER) (COUNT INTEGER)) :DOCUMENTATION \"Shift `arg' to the right by `count' positions and\n0-extend from the left if `arg' is positive or 1-extend if it is\nnegative.  This is an arithmetic shift that preserve the sign of `arg'\nand is equivalent to dividing `arg' by 2** `count'.\" :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:ASH ARG (CL:THE CL:FIXNUM (CL:- COUNT))) :CPP \"(arg >> count)\" :JAVA \"(arg >> count)\")))", wrapFunctionCode(((cpp_function_code)(((int  (*) (int, int))(&integerShiftRight))))), NULL);
    defineMethodObject("(DEFMETHOD (SHIFT-RIGHT LONG-INTEGER) ((ARG LONG-INTEGER) (COUNT INTEGER)) :DOCUMENTATION \"Shift `arg' to the right by `count' positions and\n0-extend from the left if `arg' is positive or 1-extend if it is\nnegative.  This is an arithmetic shift that preserve the sign of `arg'\nand is equivalent to dividing `arg' by 2** `count'.\" :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:ASH ARG (CL:THE CL:FIXNUM (CL:- COUNT))) :CPP \"(arg >> count)\" :JAVA \"(arg >> count)\")))", wrapFunctionCode(((cpp_function_code)(((long long int  (*) (long long int, int))(&longIntegerShiftRight))))), NULL);
    defineMethodObject("(DEFMETHOD (UNSIGNED-SHIFT-RIGHT-BY-1 INTEGER) ((ARG INTEGER)) :DOCUMENTATION \"Shift `arg' to the right by 1 position and 0-extend\nfrom the left.  This does not preserve the sign of `arg' and shifts\nthe sign-bit just like a regular bit.  In Common-Lisp we can't do that\ndirectly and need to do some extra masking.\" :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:LOGAND (CL:THE CL:FIXNUM (CL:ASH ARG -1)) *INTEGER-UNSIGNED-BITS-MASK*) :CPP \"((unsigned int)arg >> 1)\" :JAVA \"(arg >>> 1)\")))", wrapFunctionCode(((cpp_function_code)(((int  (*) (int))(&integerUnsignedShiftRightBy1))))), NULL);
    defineMethodObject("(DEFMETHOD (UNSIGNED-SHIFT-RIGHT-BY-1 LONG-INTEGER) ((ARG LONG-INTEGER)) :DOCUMENTATION \"Shift `arg' to the right by 1 position and 0-extend\nfrom the left.  This does not preserve the sign of `arg' and shifts\nthe sign-bit just like a regular bit.  In Common-Lisp we can't do that\ndirectly and need to do some extra masking.\" :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:LOGAND (CL:ASH ARG -1) *LONG-INTEGER-UNSIGNED-BITS-MASK*) :CPP \"((unsigned long long int)arg >> 1)\" :JAVA \"(arg >>> 1)\")))", wrapFunctionCode(((cpp_function_code)(((long long int  (*) (long long int))(&longIntegerUnsignedShiftRightBy1))))), NULL);
    defineFunctionObject("GENERATE-UUID", "(DEFUN (GENERATE-UUID STRING) ((UUID-TYPE KEYWORD)) :PUBLIC? TRUE :DOCUMENTATION \"Generates a UUID of the specified type.  Legal types are\na subset of the IETF RFC 4122 (see http://www.ietf.org/rfc/rfc4122.txt )\nUUID types.  Currently supported are:\n    :TYPE-4  :RANDOM       A type-4 (random) UUID.  These are synonyms.\")", ((cpp_function_code)(&generateUuid)), NULL);
    defineFunctionObject("GENERATE-RANDOM-UUID", "(DEFUN (GENERATE-RANDOM-UUID STRING) () :PUBLIC? TRUE :DOCUMENTATION \"Generates a random UUID (Type 4), according to the guidelines\nof IETF RFC 4122 (see http://www.ietf.org/rfc/rfc4122.txt )\n\nTake 16 random bytes (octets), put them all behind each other, for the description\nthe numbering starts with byte 1 (most significant, first) to byte 16 \n   (least significant, last). Then put in the version and variant.\nTo put in the version, take the 7th byte and perform an and operation using 0x0f,\n   followed by an or operation with 0x40. \nTo put in the variant, take the 9th byte and perform an and operation using 0x3f,\n   followed by an or operation with 0x80.\nTo make the string representation, take the hexadecimal presentation of bytes 1-4\n   (without 0x in front of it) let them follow by a -, then take bytes 5 and 6, - \nbytes 7 and 8, - bytes 9 and 10, - then followed by bytes 11-16.\")", ((cpp_function_code)(&generateRandomUuid)), NULL);
    defineFunctionObject("STELLIFY", "(DEFUN (STELLIFY OBJECT) ((SELF OBJECT)) :DOCUMENTATION \"Convert a Lisp object into a STELLA object.\" :PUBLIC? TRUE)", ((cpp_function_code)(&stellify)), NULL);
    defineFunctionObject("STELLA-OBJECT?", "(DEFUN (STELLA-OBJECT? BOOLEAN) ((SELF OBJECT)) :DOCUMENTATION \"Return true if `self' is a member of the STELLA class `OBJECT'.\")", ((cpp_function_code)(&stellaObjectP)), NULL);
    defineFunctionObject("RUNNING-AS-LISP?", "(DEFUN (RUNNING-AS-LISP? BOOLEAN) () :DOCUMENTATION \"Return true if the executable code is a Common Lisp application.\" :PUBLIC? TRUE)", ((cpp_function_code)(&runningAsLispP)), NULL);
    defineFunctionObject("RUNNING-IN-LANGUAGE", "(DEFUN (RUNNING-IN-LANGUAGE KEYWORD) () :DOCUMENTATION \"Returns the keyword for the language the current implementation is running in.\" :PUBLIC? TRUE)", ((cpp_function_code)(&runningInLanguage)), NULL);
    defineFunctionObject("RUNNING-SYSTEM-INFORMATION", "(DEFUN (RUNNING-SYSTEM-INFORMATION STRING) () :DOCUMENTATION \"Returns an information string about the current running system environment.\")", ((cpp_function_code)(&runningSystemInformation)), NULL);
    defineFunctionObject("GETENV", "(DEFUN (GETENV STRING) ((VARNAME STRING) |&REST| (DEFLT STRING)) :DOCUMENTATION \"Return the value of the OS environment variable `varname'.  If it is not defined\nor if its value is the empty string and a `deflt' is provided, return the default value instead.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&getenv)), ((cpp_function_code)(&getenvEvaluatorWrapper)));
    defineFunctionObject("GET-TICKTOCK", "(DEFUN (GET-TICKTOCK TICKTOCK) () :DOCUMENTATION \"Return the current CPU time.  If the current OS/Language\ncombination does not support measuring of CPU time, return real time instead.\nUse `ticktock-difference' to measure the time difference between values\nreturned by this function.  This is an attempt to provide some platform\nindependent support to measure (at least approximately) consumed CPU time.\" :PUBLIC? TRUE :NATIVE? TRUE)", ((cpp_function_code)(&getTicktock)), NULL);
    defineFunctionObject("TICKTOCK-DIFFERENCE", "(DEFUN (TICKTOCK-DIFFERENCE FLOAT) ((T1 TICKTOCK) (T2 TICKTOCK)) :DOCUMENTATION \"The difference in two TICKTOCK time values in seconds where\n`t1' is the earlier time.  The resolution is implementation dependent but will\nnormally be some fractional value of a second.\" :PUBLIC? TRUE :NATIVE? TRUE)", ((cpp_function_code)(((double  (*) (clock_t, clock_t))(&ticktockDifference)))), NULL);
    defineFunctionObject("TICKTOCK-RESOLUTION", "(DEFUN (TICKTOCK-RESOLUTION FLOAT) () :DOCUMENTATION \"The minimum theoretically detectable resolution of the\ndifference in two TICKTOCK time values in seconds.  This\nresolution is implementation dependent.  It may also not\nbe realizable in practice, since the timing grain size may\nbe larger than this resolution.\" :PUBLIC? TRUE :NATIVE? TRUE)", ((cpp_function_code)(((double  (*) ())(&ticktockResolution)))), NULL);
    defineFunctionObject("SLEEP", "(DEFUN SLEEP ((SECONDS FLOAT)) :DOCUMENTATION \"The program will sleep for the indicated number of seconds.\nFractional values are allowed, but the results are implementation dependent:\nCommon Lisp uses the fractions natively, Java with a resolution of 0.001,\nand C++ can only use integral values.\")", ((cpp_function_code)(&stella::sleep)), NULL);
    defineFunctionObject("EXCEPTION-MESSAGE", "(DEFUN (EXCEPTION-MESSAGE STRING) ((E NATIVE-EXCEPTION)) :DOCUMENTATION \"Accesses the error message of the exception `e'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&exceptionMessage)), NULL);
    defineFunctionObject("PRINT-EXCEPTION-CONTEXT", "(DEFUN PRINT-EXCEPTION-CONTEXT ((E NATIVE-EXCEPTION) (STREAM OUTPUT-STREAM)) :DOCUMENTATION \"Prints system dependent information about the context of the specified\nexception `e'.  For example, in Java it prints a stack trace.  In Lisp, it is vendor dependent.\" :PUBLIC? TRUE)", ((cpp_function_code)(&printExceptionContext)), NULL);
    defineFunctionObject("EXCEPTION-CONTEXT", "(DEFUN (EXCEPTION-CONTEXT STRING) ((E NATIVE-EXCEPTION)) :DOCUMENTATION \"Print the exception context of `e' to a string and return the result.\" :PUBLIC? TRUE)", ((cpp_function_code)(&exceptionContext)), NULL);
    defineFunctionObject("MAKE-PROCESS-LOCK", "(DEFUN (MAKE-PROCESS-LOCK PROCESS-LOCK-OBJECT) () :PUBLIC? TRUE)", ((cpp_function_code)(&makeProcessLock)), NULL);
    defineFunctionObject("STARTUP-PRIMAL", "(DEFUN STARTUP-PRIMAL () :PUBLIC? TRUE)", ((cpp_function_code)(&startupPrimal)), NULL);
    { MethodSlot* function = lookupFunction(SYM_PRIMAL_STELLA_STARTUP_PRIMAL);

      setDynamicSlotValue(function->dynamicSlots, SYM_PRIMAL_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupPrimal"), NULL_STRING_WRAPPER);
    }
  }
}

void startupPrimal() {
  if (currentStartupTimePhaseP(0)) {
    oHASH_BYTE_RANDOM_TABLEo = new (PointerFreeGC)int[256];
    { int i = NULL_INTEGER;
      int iter005 = 0;
      int upperBound006 = 255;

      for  (; iter005 <= upperBound006; 
            iter005 = iter005 + 1) {
        i = iter005;
        oHASH_BYTE_RANDOM_TABLEo[i] = 0;
      }
    }
    { int bit = NULL_INTEGER;
      int iter007 = 0;
      int upperBound008 = 31;

      for  (; iter007 <= upperBound008; 
            iter007 = iter007 + 1) {
        bit = iter007;
        { int i = NULL_INTEGER;
          int iter009 = 0;
          int upperBound010 = 255;

          for  (; iter009 <= upperBound010; 
                iter009 = iter009 + 1) {
            i = iter009;
            oHASH_BYTE_RANDOM_TABLEo[i] = ((oHASH_BYTE_RANDOM_TABLEo[i]) | (((stella::random(2)) << bit)));
          }
        }
      }
    }
    oHASH_TABLE_SIZE_PRIME_STRINGSo = stella::vector(27, wrapString("29"), wrapString("53"), wrapString("97"), wrapString("193"), wrapString("389"), wrapString("769"), wrapString("1543"), wrapString("3079"), wrapString("6151"), wrapString("12289"), wrapString("24593"), wrapString("49157"), wrapString("98317"), wrapString("196613"), wrapString("393241"), wrapString("786433"), wrapString("1572869"), wrapString("3145739"), wrapString("6291469"), wrapString("12582917"), wrapString("25165843"), wrapString("50331653"), wrapString("100663319"), wrapString("201326611"), wrapString("402653189"), wrapString("805306457"), wrapString("1610612741"));
    oHASH_TABLE_SIZE_PRIMESo = stella::newVector(oHASH_TABLE_SIZE_PRIME_STRINGSo->length());
    { StringWrapper* s = NULL;
      Vector* vector012 = oHASH_TABLE_SIZE_PRIME_STRINGSo;
      int index013 = 0;
      int length014 = vector012->length();
      int i = NULL_INTEGER;
      int iter015 = 0;

      for  (; index013 < length014; 
            index013 = index013 + 1,
            iter015 = iter015 + 1) {
        s = ((StringWrapper*)((vector012->theArray)[index013]));
        i = iter015;
        (oHASH_TABLE_SIZE_PRIMESo->theArray)[i] = (wrapInteger(((int)(stringToInteger(s->wrapperValue)))));
      }
    }
  }
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupPrimal1();
    }
    if (currentStartupTimePhaseP(4)) {
      MOST_NEGATIVE_INTEGER = NULL_INTEGER + 1;
      MOST_NEGATIVE_LONG_INTEGER = NULL_LONG_INTEGER + 1;
      LEAST_NEGATIVE_FLOAT = 0 - LEAST_POSITIVE_FLOAT;
      RECIPROCAL_NL2 = 1.0 / ::log(2.0);
      RECIPROCAL_NL10 = 1.0 / ::log(10.0);
      LONG_INTEGER_BIT_WIDTH = stella::round(::log((MOST_POSITIVE_LONG_INTEGER * 2.0)) / ::log((2.0)));
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupPrimal2();
      helpStartupPrimal3();
      helpStartupPrimal4();
      helpStartupPrimal5();
      helpStartupPrimal6();
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("/STELLA")))));
      defineGlobalVariableObject("(DEFCONSTANT PI FLOAT (VERBATIM :COMMON-LISP \"(cl:float CL:PI 0.0d0)\" :CPP \"3.141592653589793\" :JAVA \"java.lang.Math.PI\") :PUBLIC? TRUE :DOCUMENTATION \"A float approximation of the mathematical constant pi.\")", &PI);
      defineStellaGlobalVariableFromStringifiedSource("(defconstant NULL UNKNOWN NULL\n       :public? TRUE\n       :documentation\n       \"Generic undefined value for any STELLA data type.  The STELLA\ntranslator substitutes specific NULL-values appropriate for a particular data\ntype.  For example, NULL-INTEGER represents the undefined INTEGER value.\")");
      defineGlobalVariableObject("(DEFCONSTANT NULL-INTEGER INTEGER (VERBATIM :COMMON-LISP CL:MOST-NEGATIVE-FIXNUM :CPP \"std::numeric_limits<int>::min()\" :JAVA \"Integer.MIN_VALUE\") :PUBLIC? TRUE)", &NULL_INTEGER);
      defineGlobalVariableObject("(DEFCONSTANT NULL-SHORT-INTEGER SHORT-INTEGER (VERBATIM :COMMON-LISP CL:MOST-NEGATIVE-FIXNUM :CPP \"std::numeric_limits<short int>::min()\" :JAVA \"Short.MIN_VALUE\") :PUBLIC? TRUE)", &NULL_SHORT_INTEGER);
      defineGlobalVariableObject("(DEFCONSTANT NULL-LONG-INTEGER LONG-INTEGER (VERBATIM :COMMON-LISP \"(CL:- (CL:expt 2 63))\" :CPP \"std::numeric_limits<long long int>::min()\" :JAVA \"Long.MIN_VALUE\") :PUBLIC? TRUE)", &NULL_LONG_INTEGER);
      defineGlobalVariableObject("(DEFCONSTANT NULL-UNSIGNED-SHORT-INTEGER UNSIGNED-SHORT-INTEGER (VERBATIM :COMMON-LISP CL:MOST-NEGATIVE-FIXNUM :CPP \"std::numeric_limits<unsigned short int>::min()\" :JAVA \"Short.MIN_VALUE\") :PUBLIC? TRUE)", &NULL_UNSIGNED_SHORT_INTEGER);
      defineGlobalVariableObject("(DEFCONSTANT NULL-UNSIGNED-LONG-INTEGER UNSIGNED-LONG-INTEGER (VERBATIM :COMMON-LISP \"(CL:1- (CL:expt 2 64))\" :CPP \"std::numeric_limits<unsigned long long int>::min()\" :JAVA \"Long.MIN_VALUE\") :PUBLIC? TRUE)", &NULL_UNSIGNED_LONG_INTEGER);
      defineGlobalVariableObject("(DEFCONSTANT NULL-FLOAT FLOAT (VERBATIM :COMMON-LISP CL:MOST-NEGATIVE-DOUBLE-FLOAT :CPP \"std::numeric_limits<double>::infinity() != 0 ?\n                    -std::numeric_limits<double>::infinity() :\n                    // work around a problem in g++ 3.2.2 where infinity()==0:\n                    NULL_INTEGER / (double)ceiling(-0.42)\" :JAVA \"Double.NEGATIVE_INFINITY; /* IEEE Infinity */\") :PUBLIC? TRUE)", &NULL_FLOAT);
      defineGlobalVariableObject("(DEFCONSTANT NULL-SINGLE-FLOAT SINGLE-FLOAT (VERBATIM :COMMON-LISP CL:MOST-NEGATIVE-SINGLE-FLOAT :CPP \"-std::numeric_limits<float>::infinity()\" :JAVA \"Float.NEGATIVE_INFINITY; /* IEEE Infinity */\") :PUBLIC? TRUE)", &NULL_SINGLE_FLOAT);
      defineGlobalVariableObject("(DEFCONSTANT NULL-DOUBLE-FLOAT DOUBLE-FLOAT (VERBATIM :COMMON-LISP CL:MOST-NEGATIVE-DOUBLE-FLOAT :CPP \"-std::numeric_limits<double>::infinity()\" :JAVA \"Double.NEGATIVE_INFINITY; /* IEEE Infinity */\") :PUBLIC? TRUE)", &NULL_DOUBLE_FLOAT);
      defineGlobalVariableObject("(DEFCONSTANT NULL-CHARACTER CHARACTER (VERBATIM :COMMON-LISP (CL:CODE-CHAR 0) :CPP \"'\\\\0'\" :JAVA \"Character.MIN_VALUE\") :PUBLIC? TRUE)", &NULL_CHARACTER);
      defineGlobalVariableObject("(DEFCONSTANT NULL-BYTE BYTE (VERBATIM :COMMON-LISP \"255\" :CPP \"255\" :JAVA \"-128\") :PUBLIC? TRUE)", &NULL_BYTE);
      defineGlobalVariableObject("(DEFCONSTANT NULL-OCTET OCTET (VERBATIM :COMMON-LISP \"255\" :CPP \"255\" :JAVA \"-128\") :PUBLIC? TRUE)", &NULL_OCTET);
      defineGlobalVariableObject("(DEFCONSTANT MOST-POSITIVE-INTEGER INTEGER (VERBATIM :COMMON-LISP CL:MOST-POSITIVE-FIXNUM :CPP \"std::numeric_limits<int>::max()\" :JAVA \"Integer.MAX_VALUE\") :PUBLIC? TRUE)", &MOST_POSITIVE_INTEGER);
      defineGlobalVariableObject("(DEFCONSTANT MOST-NEGATIVE-INTEGER INTEGER (1+ NULL-INTEGER) :PUBLIC? TRUE)", &MOST_NEGATIVE_INTEGER);
      defineGlobalVariableObject("(DEFCONSTANT MOST-POSITIVE-LONG-INTEGER LONG-INTEGER (VERBATIM :COMMON-LISP \"(CL:1- (CL:expt 2 63))\" :CPP \"std::numeric_limits<long long int>::max()\" :JAVA \"Long.MAX_VALUE\") :PUBLIC? TRUE)", &MOST_POSITIVE_LONG_INTEGER);
      defineGlobalVariableObject("(DEFCONSTANT MOST-NEGATIVE-LONG-INTEGER LONG-INTEGER (1+ NULL-LONG-INTEGER) :PUBLIC? TRUE)", &MOST_NEGATIVE_LONG_INTEGER);
      defineGlobalVariableObject("(DEFCONSTANT MOST-POSITIVE-FLOAT FLOAT (VERBATIM :COMMON-LISP CL:MOST-POSITIVE-DOUBLE-FLOAT :CPP \"std::numeric_limits<double>::max()\" :JAVA \"Double.MAX_VALUE\") :PUBLIC? TRUE)", &MOST_POSITIVE_FLOAT);
      defineGlobalVariableObject("(DEFCONSTANT MOST-NEGATIVE-FLOAT FLOAT (VERBATIM :COMMON-LISP \"(cl:multiple-value-bind (signif expon)\n                (cl:integer-decode-float cl:most-positive-double-float)\n              (cl:- (cl:scale-float (CL:- signif 1.0) expon)))\" :OTHERWISE (- MOST-POSITIVE-FLOAT)) :PUBLIC? TRUE)", &MOST_NEGATIVE_FLOAT);
      defineGlobalVariableObject("(DEFCONSTANT LEAST-POSITIVE-FLOAT FLOAT (VERBATIM :COMMON-LISP CL:LEAST-POSITIVE-DOUBLE-FLOAT :CPP \"std::numeric_limits<double>::min()\" :JAVA \"Double.MIN_VALUE\") :PUBLIC? TRUE)", &LEAST_POSITIVE_FLOAT);
      defineGlobalVariableObject("(DEFCONSTANT LEAST-NEGATIVE-FLOAT FLOAT (- LEAST-POSITIVE-FLOAT) :PUBLIC? TRUE)", &LEAST_NEGATIVE_FLOAT);
      seedRandomNumberGenerator2();
      defineGlobalVariableObject("(DEFCONSTANT RECIPROCAL-NL2 FLOAT (/ 1.0 (LOG 2.0)) :DOCUMENTATION \"1 / (log 2) Reciprocal of the Log base e of 2.\nUsed for log 2 conversions.\")", &RECIPROCAL_NL2);
      defineGlobalVariableObject("(DEFCONSTANT RECIPROCAL-NL10 FLOAT (/ 1.0 (LOG 10.0)) :DOCUMENTATION \"1 / (log 10) Reciprocal of the Log base e of 10.\nUsed for log 10 conversions.\")", &RECIPROCAL_NL10);
      registerNativeName(SYM_PRIMAL_STELLA_FLOOR, KWD_PRIMAL_CPP, KWD_PRIMAL_FUNCTION);
      registerNativeName(SYM_PRIMAL_STELLA_ROUND, KWD_PRIMAL_CPP, KWD_PRIMAL_FUNCTION);
      registerNativeName(SYM_PRIMAL_STELLA_FMOD, KWD_PRIMAL_CPP, KWD_PRIMAL_FUNCTION);
      registerNativeName(SYM_PRIMAL_STELLA_RANDOM, KWD_PRIMAL_CPP, KWD_PRIMAL_FUNCTION);
      registerNativeName(SYM_PRIMAL_STELLA_SQRT, KWD_PRIMAL_CPP, KWD_PRIMAL_FUNCTION);
      registerNativeName(SYM_PRIMAL_STELLA_COS, KWD_PRIMAL_CPP, KWD_PRIMAL_FUNCTION);
      registerNativeName(SYM_PRIMAL_STELLA_SIN, KWD_PRIMAL_CPP, KWD_PRIMAL_FUNCTION);
      registerNativeName(SYM_PRIMAL_STELLA_TAN, KWD_PRIMAL_CPP, KWD_PRIMAL_FUNCTION);
      registerNativeName(SYM_PRIMAL_STELLA_ACOS, KWD_PRIMAL_CPP, KWD_PRIMAL_FUNCTION);
      registerNativeName(SYM_PRIMAL_STELLA_ASIN, KWD_PRIMAL_CPP, KWD_PRIMAL_FUNCTION);
      registerNativeName(SYM_PRIMAL_STELLA_ATAN, KWD_PRIMAL_CPP, KWD_PRIMAL_FUNCTION);
      registerNativeName(SYM_PRIMAL_STELLA_ATAN2, KWD_PRIMAL_CPP, KWD_PRIMAL_FUNCTION);
      registerNativeName(SYM_PRIMAL_STELLA_EXP, KWD_PRIMAL_CPP, KWD_PRIMAL_FUNCTION);
      registerNativeName(SYM_PRIMAL_STELLA_LOG, KWD_PRIMAL_CPP, KWD_PRIMAL_FUNCTION);
      registerNativeName(SYM_PRIMAL_STELLA_MIN, KWD_PRIMAL_CPP, KWD_PRIMAL_FUNCTION);
      registerNativeName(SYM_PRIMAL_STELLA_MAX, KWD_PRIMAL_CPP, KWD_PRIMAL_FUNCTION);
      defineGlobalVariableObject("(DEFSPECIAL *TRANSIENTOBJECTS?* BOOLEAN FALSE :PUBLIC? TRUE)", &oTRANSIENTOBJECTSpo);
      registerNativeName(SYM_PRIMAL_STELLA_HASH_CODE, KWD_PRIMAL_JAVA, KWD_PRIMAL_FUNCTION);
      defineGlobalVariableObject("(DEFGLOBAL *HASH-BYTE-RANDOM-TABLE* (ARRAY (256) OF INTEGER) NULL :DOCUMENTATION \"A table of 256 N-bit random numbers that can be used to\nhash sequences of bytes.  Each bit-column in the table has an approximately\neven number of 0's and 1's.\")", &oHASH_BYTE_RANDOM_TABLEo);
      defineGlobalVariableObject("(DEFCONSTANT *INTEGER-MSB-MASK* INTEGER (VERBATIM :COMMON-LISP \"#.(cl:abs (cl:ash cl:most-negative-fixnum -1))\" :CPP \"1 << (sizeof (int) / sizeof (char) * 8 - 1)\" :JAVA \"0x80000000\") :DOCUMENTATION \"The most significant bit of a regular integer (FIXNUM\nin Common-Lisp).  In C++ and Java this corresponds to the sign bit, in\nLisp this corresponds to the left-most bit of `CL:most-positive-fixnum'.\" :PUBLIC? TRUE)", &oINTEGER_MSB_MASKo);
      defineGlobalVariableObject("(DEFCONSTANT *INTEGER-UNSIGNED-BITS-MASK* INTEGER (VERBATIM :OTHERWISE MOST-POSITIVE-INTEGER) :DOCUMENTATION \"Mask that covers all the unsigned bits of an integer.\" :PUBLIC? TRUE)", &oINTEGER_UNSIGNED_BITS_MASKo);
      defineGlobalVariableObject("(DEFCONSTANT *LONG-INTEGER-MSB-MASK* LONG-INTEGER (VERBATIM :OTHERWISE NULL-LONG-INTEGER) :DOCUMENTATION \"The sign bit of a long integer.\" :PUBLIC? TRUE)", &oLONG_INTEGER_MSB_MASKo);
      defineGlobalVariableObject("(DEFCONSTANT *LONG-INTEGER-UNSIGNED-BITS-MASK* LONG-INTEGER (VERBATIM :OTHERWISE MOST-POSITIVE-LONG-INTEGER) :DOCUMENTATION \"Mask that covers all the unsigned bits of a long integer.\" :PUBLIC? TRUE)", &oLONG_INTEGER_UNSIGNED_BITS_MASKo);
      defineGlobalVariableObject("(DEFGLOBAL *HASH-TABLE-SIZE-PRIME-STRINGS* (VECTOR OF STRING-WRAPPER) NULL :DOCUMENTATION \"List of prime numbers approximately growing by a factor of 2\nthat are suitable to be used as hash table sizes.  This is in string\nformat to enable processing by Lisps with different fixnum sizes.\" :PUBLIC? TRUE)", &oHASH_TABLE_SIZE_PRIME_STRINGSo);
      defineGlobalVariableObject("(DEFGLOBAL *HASH-TABLE-SIZE-PRIMES* (VECTOR OF INTEGER-WRAPPER) NULL :DOCUMENTATION \"List of prime numbers approximately growing by a factor of 2\nthat are suitable to be used as hash table sizes.\" :PUBLIC? TRUE)", &oHASH_TABLE_SIZE_PRIMESo);
      defineGlobalVariableObject("(DEFCONSTANT LONG-INTEGER-BIT-WIDTH INTEGER (ROUND (/ (LOG (* MOST-POSITIVE-LONG-INTEGER 2.0)) (LOG 2))) :DOCUMENTATION \"The number of bits in a long integer.\")", &LONG_INTEGER_BIT_WIDTH);
      registerNativeName(SYM_PRIMAL_STELLA_SLEEP, KWD_PRIMAL_CPP, KWD_PRIMAL_FUNCTION);
      defineGlobalVariableObject("(DEFGLOBAL *BOOTSTRAP-LOCK* PROCESS-LOCK-OBJECT (VERBATIM :COMMON-LISP \"(%make-process-lock)\" :JAVA \"new java.lang.Object()\" :CPP \"NULL\") :PUBLIC? TRUE :DOCUMENTATION \"Process lock object for bootstrap use.\")", &oBOOTSTRAP_LOCKo);
    }
  }
}

Keyword* KWD_PRIMAL_IF_NOT_EXISTS = NULL;

Keyword* KWD_PRIMAL_ABORT = NULL;

Symbol* SYM_PRIMAL_STELLA_FLOOR = NULL;

Keyword* KWD_PRIMAL_CPP = NULL;

Keyword* KWD_PRIMAL_FUNCTION = NULL;

Symbol* SYM_PRIMAL_STELLA_ROUND = NULL;

Symbol* SYM_PRIMAL_STELLA_FMOD = NULL;

Symbol* SYM_PRIMAL_STELLA_RANDOM = NULL;

Symbol* SYM_PRIMAL_STELLA_SQRT = NULL;

Symbol* SYM_PRIMAL_STELLA_COS = NULL;

Symbol* SYM_PRIMAL_STELLA_SIN = NULL;

Symbol* SYM_PRIMAL_STELLA_TAN = NULL;

Symbol* SYM_PRIMAL_STELLA_ACOS = NULL;

Symbol* SYM_PRIMAL_STELLA_ASIN = NULL;

Symbol* SYM_PRIMAL_STELLA_ATAN = NULL;

Symbol* SYM_PRIMAL_STELLA_ATAN2 = NULL;

Symbol* SYM_PRIMAL_STELLA_EXP = NULL;

Symbol* SYM_PRIMAL_STELLA_LOG = NULL;

Symbol* SYM_PRIMAL_STELLA_MIN = NULL;

Symbol* SYM_PRIMAL_STELLA_MAX = NULL;

Keyword* KWD_PRIMAL_WHITE_SPACE = NULL;

Keyword* KWD_PRIMAL_ASCII_CASE_SENSITIVE = NULL;

Keyword* KWD_PRIMAL_ASCII_CASE_INSENSITIVE = NULL;

Keyword* KWD_PRIMAL_ASCII_CASE_NORMALIZED = NULL;

Keyword* KWD_PRIMAL_UPCASE = NULL;

Keyword* KWD_PRIMAL_DOWNCASE = NULL;

Keyword* KWD_PRIMAL_CAPITALIZE = NULL;

Keyword* KWD_PRIMAL_PRESERVE = NULL;

Keyword* KWD_PRIMAL_LEFT = NULL;

Keyword* KWD_PRIMAL_RIGHT = NULL;

Keyword* KWD_PRIMAL_CENTER = NULL;

Symbol* SYM_PRIMAL_STELLA_HASH_CODE = NULL;

Keyword* KWD_PRIMAL_JAVA = NULL;

Keyword* KWD_PRIMAL_UNIX = NULL;

Keyword* KWD_PRIMAL_MAC = NULL;

Keyword* KWD_PRIMAL_WINDOWS = NULL;

Keyword* KWD_PRIMAL_IF_EXISTS = NULL;

Keyword* KWD_PRIMAL_ERROR = NULL;

Keyword* KWD_PRIMAL_TYPE_4 = NULL;

Keyword* KWD_PRIMAL_RANDOM = NULL;

Symbol* SYM_PRIMAL_STELLA_SLEEP = NULL;

Symbol* SYM_PRIMAL_STELLA_STARTUP_PRIMAL = NULL;

Symbol* SYM_PRIMAL_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
