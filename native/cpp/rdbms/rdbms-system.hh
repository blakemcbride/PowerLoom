// rdbms-system.hh

#ifndef _STELLA_RDBMS_SYSTEM_HH
#define _STELLA_RDBMS_SYSTEM_HH

// Required systems:
#include "stella/stella-system.hh"

#include "logic/logic-system.hh"

#include "utilities/utilities-system.hh"

#include "sdbc/sdbc-system.hh"

// System-wide forward declarations:

namespace rdbms {
  using namespace stella;
  using namespace logic;

class ConnectionWrapper;
class RelationTableInfo;
class RelationColumnInfo;

} // end of namespace rdbms

// System components:
#include "rdbms/ontology.hh"
#include "rdbms/rdbms.hh"
#include "rdbms/fetch-interface.hh"
#include "rdbms/startup-system.hh"

#endif
