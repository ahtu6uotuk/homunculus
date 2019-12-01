#include <fenv.h>
#include "engine/engine.h"


int main (int argc, char *argv[])
{
  feenableexcept (FE_DIVBYZERO | FE_OVERFLOW | FE_INVALID);
  engine_t engine (argc, argv);
  return engine.exec ();
}
