// main entry point for sdbc system

#include "sdbc/sdbc-system.hh"

using namespace stella;
using namespace sdbc;

int main() {
  startupSdbcSystem();
  std::cout << "Start..." << std::endl;
  testRetrieveAll();
  testResultSet();
  testTransactions();
  testPreparedStatement();
  std::cout << "done!" << std::endl;
  return (1);
}

