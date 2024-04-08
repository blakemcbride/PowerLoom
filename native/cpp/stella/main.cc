// main entry point for stella system

#include "stella/stella-system.hh"

using namespace stella;

int main(int count, const char** arguments) {
  { boolean testingP = count == 1;

    startup(testingP);
    startupStellaSystem();
    std::cout << "Welcome to " << stellaVersionString() << std::endl;
    interpretCommandLineArguments(count, arguments);
    if (testingP) {
      std::cout << "Bye!" << std::endl;
    }
  }
  return (1);
}

