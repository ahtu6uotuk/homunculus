#include <cstring>
#include "logic_tests.h"

int main (int argc, char **argv)
{
  if (argc == 2)
    {
      if (!strcmp (argv[1], "--tests"))
        {
          run_logic_tests ();
          return 0;
        }
      if (!strcmp (argv[1], "--sim-start"))
        {
//          run_logic_tests ();
          run_simulation (false);
          return 0;
        }
      if (!strcmp (argv[1], "--sim-cont"))
        {
//          run_logic_tests ();
          run_simulation (true);
          return 0;
        }
      return 0;
    }
  run_simulation (false);
  return 0;
}
