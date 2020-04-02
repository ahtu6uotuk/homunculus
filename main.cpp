#include <fenv.h>
#include <cstring>

#include "common/common.h"
#include "common/err_t.h"
#include "common/logger/logger.h"
#include "control_flow/control_flow.h"

int main (int argc, char *argv[])
{
#ifndef WIN32
  feenableexcept (FE_DIVBYZERO | FE_OVERFLOW | FE_INVALID);
#endif

  if (!logger_t::instance ().is_ok ())
    {
      std::cout << "Error: can't init logger. Execution aborted" << std::endl;
      return 1;
    }

  control_flow flow (argc, argv);
  err_t err = flow.run ();
  if (err)
    logger_t::instance ().print (log_section_t::ENGINE, log_priority_t::LOG_ERROR, "execution aborted");

  return 0;
}
