// utilities-system.hh

#ifndef _STELLA_UTILITIES_SYSTEM_HH
#define _STELLA_UTILITIES_SYSTEM_HH

// Required systems:
#include "stella/stella-system.hh"

// System-wide forward declarations:

namespace stella_utilities {
  using namespace stella;

class Ratio;
class Measure;
class IncompatibleUnitsException;
class DimNumber;

} // end of namespace stella_utilities

// System components:
#include "utilities/manuals.hh"
#include "utilities/units.hh"
#include "utilities/unit-defs.hh"
#include "utilities/startup-system.hh"

#endif
