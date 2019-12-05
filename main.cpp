#include <fenv.h>
#include "engine/engine.h"
#include "common/common.h"
#include "common/err_t.h"
#include "logic/saveload_tree_test.h"

int main (int argc, char *argv[])
{
  do_nothing (argc, argv);
  feenableexcept (FE_DIVBYZERO | FE_OVERFLOW | FE_INVALID);

  saveload_tree_test ();

  engine_t engine (argc, argv);
  return engine.exec ();
}
