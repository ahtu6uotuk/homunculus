#include <float.h>
#include <cstdio>
#include "string_converters.h"
#include "common/err_t.h"
#include "common/string_utils.h"

// double
err_t string_to_data (const string &src, double &dst)
{
  char *endptr = nullptr;
  double res = strtod (src.c_str (), &endptr);

  if (*endptr)
    return err_t (string_printf ("Could not convert %s to double", src.c_str ()));

  dst = res;
  return ERR_OK;
}
err_t string_from_data (string &dst, const double &src)
{
  dst = string_printf ("%a", src);
  return ERR_OK;
}

// long
err_t string_to_data (const string &src, int &dst)
{
  char *endptr = nullptr;
  int res = static_cast<int> (strtol (src.c_str (), &endptr, 10));

  if (*endptr)
    return err_t (string_printf ("Could not convert %s to double", src.c_str ()));

  dst = res;
  return ERR_OK;
}
err_t string_from_data (string &dst, const int &src)
{
  dst = string_printf ("%d", src);
  return ERR_OK;
}

// string
err_t string_to_data (const string &src, string &dst)
{
  dst = src;
  return ERR_OK;
}
err_t string_from_data (string &dst, const string &src)
{
  dst = src;
  return ERR_OK;
}
