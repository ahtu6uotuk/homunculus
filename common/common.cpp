#include "common.h"

#include <math.h>

void do_nothing_no_inline () {}

void assert_check (bool check, string message)
{
  if (!check)
    {
      fprintf (stderr, "WARNING: %s\n", message.c_str ());
      throw exception ();
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
