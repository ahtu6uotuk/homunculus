#include "common.h"

#include <math.h>
#include <signal.h>

void assert_check (bool check, std::string message)
{
  if (!check)
    {
      fprintf (stderr, "WARNING: %s\n", message.c_str ());
#ifndef _WIN32
      ::raise (SIGTRAP);
#else
      __asm__("int $3");
      throw std::exception ();
#endif
    }
}

int fuzzycmp (double a, double b, double eps)
{
  if (fabs (a - b) <= eps)
    return 0;
  if (a > b)
    return 1;
  return -1;
}

std::string get_gamedata_path_prefix () { return "gamedata/"; }
std::string get_saved_game_path_prefix () { return "gamedata/saved_game/"; }
