// powerloom-extensions-system.hh

#ifndef _STELLA_POWERLOOM_EXTENSIONS_SYSTEM_HH
#define _STELLA_POWERLOOM_EXTENSIONS_SYSTEM_HH

// Required systems:
#include "stella/stella-system.hh"

#include "logic/logic-system.hh"

#include "utilities/utilities-system.hh"

// System-wide forward declarations:

namespace units {
  using namespace stella_utilities;
  using namespace stella;
  using namespace logic;

class DimNumberLogicWrapper;

} // end of namespace units

namespace timepoint {
  using namespace stella_utilities;
  using namespace stella;
  using namespace logic;

class DateTimeLogicWrapper;

} // end of namespace timepoint

// System components:
#include "logic/extensions/extensions.hh"
#include "logic/extensions/unit-support.hh"
#include "logic/extensions/unit-kb.hh"
#include "logic/extensions/timepoint-support.hh"
#include "logic/extensions/timepoint-kb.hh"
#include "logic/extensions/startup-system.hh"

#endif
