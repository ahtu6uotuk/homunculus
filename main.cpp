#include <fenv.h>
#include <cstring>

#include "common/common.h"
#include "common/err_t.h"
#include "control_flow/control_flow.h"

int main (int argc, char *argv[])
{
  do_nothing (argc, argv);
#ifndef WIN32
  feenableexcept (FE_DIVBYZERO | FE_OVERFLOW | FE_INVALID);
#endif

  control_flow flow (argc, argv);
  assert_error (flow.run (), "Error occured in while running: ");
  return 0;
}
