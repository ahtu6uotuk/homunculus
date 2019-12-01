#include "engine/engine.h"


int main (int argc, char *argv[])
{
  engine_t engine (argc, argv);
  return engine.exec ();
}
