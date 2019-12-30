#include <fenv.h>

#include "common/common.h"
#include "common/err_t.h"
#include "engine/engine.h"
#include "logic/tests/logic_tests.h"

int main (int argc, char *argv[])
{
  do_nothing (argc, argv);
  feenableexcept (FE_DIVBYZERO | FE_OVERFLOW | FE_INVALID);

  complex_structure_saveload_test ();
  object_heap_test ();
  asset_test ();

  engine_t engine (argc, argv);
  return engine.exec ();
}
