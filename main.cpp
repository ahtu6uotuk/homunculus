#include <fenv.h>

#include "application.h"

int main (int argc, char *argv[])
{
#ifndef WIN32
  feenableexcept (FE_DIVBYZERO | FE_OVERFLOW | FE_UNDERFLOW | FE_INVALID);
#endif

  application_t app (argc, argv);

  return app.exec ();
}
