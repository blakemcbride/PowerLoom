// sdbc-system.hh

#ifndef _STELLA_SDBC_SYSTEM_HH
#define _STELLA_SDBC_SYSTEM_HH

// Required systems:
#include "stella/stella-system.hh"

// System-wide forward declarations:

namespace sdbc {
  using namespace stella;

class Connection;
class PreparedStatement;
class NativePreparedStatement;
class DatabaseException;
class ResultSetIterator;
class TableInfo;
class ColumnInfo;

} // end of namespace sdbc

// System components:
#include "sdbc/sdbc.hh"
#include "sdbc/startup-system.hh"

#endif
