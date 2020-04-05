#include <fenv.h>
#include <cstring>

#include "common/common.h"
#include "common/err_t.h"
#include "common/logger/logger.h"
#include "control_flow/control_flow.h"

#include "world/classes/enemy.h"
#include "world/classes/friend.h"

int main (int argc, char *argv[])
{
#ifndef WIN32
  feenableexcept (FE_DIVBYZERO | FE_OVERFLOW | FE_INVALID);
#endif

  enemy_t *kek = 0;
  (void) kek;
  friend_t *lel = 0;
  (void) lel;

  if (!logger_t::instance ().is_ok ())
    {
      std::cout << "Error: can't init logger. Execution aborted" << std::endl;
      return 1;
    }

  control_flow flow (argc, argv);
  assert_error (flow.run (), "Error occured in while running: ");
  return 0;
}
