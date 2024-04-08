// -*- Mode: C++ -*-

/*--------------------------- BEGIN LICENSE BLOCK ---------------------------+
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
| Portions created by the Initial Developer are Copyright (C) 1996-2020      |
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
+---------------------------- END LICENSE BLOCK ----------------------------*/

// Native C++ support for STELLA


// System libraries that need to be visible to all translated STELLA files:
#include <string.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <limits>
#include <exception>
#include <stdexcept>
//#include <filesystem>
#include <sys/stat.h>


// Garbage collector declarations
#include "stella/cpp-lib/gc.hh"

// Make sure these constants are defined.
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#ifdef __MINGW32__
// Make MinGW happy by providing these declarations, since `random()'
// is not POSIX (but BSD); -liberty will supply it but there doesn't
// seem to be an include file we can use:
extern "C" {
long int random();
void srandom(unsigned int);
}
#endif

namespace stella {

// Forward declarations
class Object;
class Vector;
class Stream;

// Primitive types
typedef bool boolean;
typedef bool fat_boolean;
typedef bool one_bit_boolean;
typedef void* cpp_function_code;
typedef Object* (Object::*cpp_method_code) ();
typedef void cpp_hash_table;


// Vector support:

// not currently used:
template<class Vector_Type, class Element_Type>
inline void initialize_stella_vector
     (Vector_Type self, int size, Element_Type null_value) {
  // Initialize `self' to a vector of `size' elements.
  Element_Type* array = new (GC) Element_Type[size];
  self->the_array = array;
  self->array_size = size;
  for (int i = 0; i < size; i++)
    array[i] = (Element_Type)null_value;
}

// not currently used:
template<class Vector_Type, class Element_Type>
void resize_stella_vector
     (Vector_Type self, int newsize, Element_Type null_value) {
  // Resize `self' to a vector of `newsize' elements.
  // This version can also handle downsizing.
  int oldsize = self->array_size;
  if (newsize == oldsize)
    return;
  Element_Type* oldarray = self->the_array;
  Element_Type* newarray = new (GC) Element_Type[newsize];
  self->the_array = newarray;
  self->array_size = newsize;
  // Copy the old content:
  if (newsize < oldsize)
    oldsize == newsize;
  for (int i = 0; i < oldsize; i++)
    newarray[i] = oldarray[i];
  // Initialize the new portion:
  for (int i = oldsize; i < newsize; i++)
    newarray[i] == null_value;
}


// Native hash table support:
// #see <cpp-hashtable.h>

// Function signatures:
boolean definedP (void* p); 
boolean definedP (int i);
boolean definedP (double f);
boolean nullP (void* p);
boolean nullP (int i);
boolean nullP (double f);

int ceiling(int n);
int ceiling(double n);
int floor(int n);
int floor(double n);
int round(int n);
int round(double n);
int truncate(int n);
int truncate(double n);

char* native_make_mutable_string(int size, char initialElement);
const char* makeString(int size, char initialElement);
const char* stringConcatenate(const char* string1, const char* string2);
const char* stringUpcase(const char* string);
const char* stringDowncase(const char* string);
const char* stringCapitalize(const char* string);
char* mutableStringCopy(const char* string);
const char* stringCopy(const char* string);
const char* stringRemove(const char* string, char character);
const char* stringSubstitute(const char* self, char newchar, char oldchar);
char* mutableStringSubstitute(char* self, char newchar, char oldchar);
boolean stringMemberP(const char* self, char character);
const char* stringRest(const char* self);
int stringPosition(const char* string, char character, int start);
int stringLastPosition(const char* string, char character, int end);
int stringSearch(const char* string, const char* substring, int start);
const char* stringSubsequence(const char* string, int start, int end);
char* mutableStringSubsequence(const char* string, int start, int end);
const char* ostringstream_to_c_string(std::ostringstream* stream);
const char* stringify(Object* expression);
const char* integerToString(long long int i);
const char* integerToHexString(long long int i);
const char* integerToStringInBase(long long int i, int base);
const char* floatToString(double f);
const char* formatFloat(double f, int n);
long long int stringToInteger(const char* string);
double stringToFloat(const char* string);
unsigned int native_hash_string (const char* x);

const char* native_read_line(std::istream* stream);
char native_read_character(std::istream* stream, boolean& return4);

boolean nativeProbeFileP(const char* filename);
CalendarDate* nativeFileWriteDate(const char* filename);
long long int nativeFileLength(const char* filename);
void nativeDeleteFile(const char* filename);
void nativeRenameFile(const char* fromfile, const char* tofile);

clock_t getTicktock();
double ticktockDifference(clock_t t1, clock_t t2);
double ticktockResolution();

boolean gcInitialize();
void startupCppPrimal();


// Special variables support (for unbinding via destructors):
// This is the new version that only allocates special structs
// for unbinding and keeps the types of specials virginal, just
// as if they were regular globals.  This makes things easier
// to use and also supports unexec better.

template <class Value_Type> struct stella_special
{
  Value_Type old_value;  // stores value of `variable' before rebinding
  Value_Type *variable;  // stores reference to the `variable' we are rebinding

  stella_special(Value_Type new_value, Value_Type *var) {
    // Used by BIND_STELLA_SPECIAL to save the old value and a reference to the variable.
    variable = var;
    old_value = *var;
    *var = new_value;
  }

  ~stella_special() {
    // Run upon exit from a special binding block which resets the value to the stored old one.
    *variable = old_value;
  }
};

// Create a declaration for SPECIAL with TYPE:
#define DECLARE_STELLA_SPECIAL(SPECIAL,TYPE) \
   TYPE SPECIAL

// Define the variable SPECIAL with TYPE and initialize it with VALUE:
#define DEFINE_STELLA_SPECIAL(SPECIAL,TYPE,VALUE) \
   TYPE SPECIAL = VALUE

// Bind the SPECIAL with TYPE to the local value VALUE:
#define BIND_STELLA_SPECIAL(SPECIAL,TYPE,VALUE) \
   stella_special<TYPE> _uNbInDrEcOrD_of_##SPECIAL=\
      stella_special<TYPE>(VALUE,& SPECIAL)

} // end of namespace stella
