#include <fenv.h>
#include <cstring>

#include "common/common.h"
#include "common/err_t.h"
#include "control_flow/control_flow.h"
#include "logic/tests/logic_tests.h"

int main (int argc, char *argv[])
{
  do_nothing (argc, argv);
#ifndef WIN32
  feenableexcept (FE_DIVBYZERO | FE_OVERFLOW | FE_INVALID);
#endif

  if (argc == 2)
    {
      if (!strcmp (argv[1], "--tests"))
        {
          run_logic_tests ();
          return 0;
        }
      if (!strcmp (argv[1], "--sim-start"))
        {
          run_logic_tests ();
          run_simulation (false);
          return 0;
        }
      if (!strcmp (argv[1], "--sim-cont"))
        {
          run_logic_tests ();
          run_simulation (true);
          return 0;
        }
      return 0;
    }

  control_flow flow (argc, argv);
  assert_error (flow.run (), "Error occured in while running: ");
  return 0;
}
