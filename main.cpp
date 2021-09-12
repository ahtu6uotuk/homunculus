#include <fenv.h>
#include <cstring>

#include "common/common.h"
#include "common/err_t.h"
#include "common/logger/logger.h"
#include "control_flow/control_flow.h"


int main (int argc, char *argv[])
{
#ifndef WIN32
  feenableexcept (FE_DIVBYZERO | FE_OVERFLOW | FE_UNDERFLOW | FE_INVALID);
#endif

  if (!logger_t::instance ().is_ok ())
    {
      std::cout << "Error: can't init logger. Execution aborted" << std::endl;
      return 1;
    }

  control_flow flow (argc, argv);
  assert_error (flow.run (), "Error occured in while running: ");
  return 0;
}
