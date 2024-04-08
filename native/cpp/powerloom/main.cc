// main entry point for powerloom system

#include "powerloom/powerloom-system.hh"

using namespace stella_utilities;
using namespace stella_plx;
using namespace pli;
using namespace logic;
using namespace stella;
using namespace stella_powerloom_code;

int main(int count, const char** arguments) {
  std::cout << "Initializing STELLA..." << std::endl;
  startupStellaSystem();
  std::cout << "Initializing PowerLoom..." << std::endl;
  startupLogicSystem();
  startupPowerloomExtensionsSystem();
  startupPowerloomSystem();
  stella::stringChangeModule("PL-USER");
  processCommandLineArguments(count, arguments, KWD_POWERLOOM_WARN);
  if ((!eqlP(stella::getProperty(wrapString("powerloom.runInteractively"), NIL), FALSE_WRAPPER)) &&
      (!eqlP(stella::getProperty(wrapString("stella.showInfoOnly"), NIL), TRUE_WRAPPER))) {
    logic::powerloom();
  }
  runHooks(oSTELLA_EXIT_HOOKSo, NULL);
  return (1);
}

