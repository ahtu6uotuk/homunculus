#include "string_converters.h"

#include <cstdio>
#include <float.h>

#include "common/err_t.h"
#include "common/string/string_utils.h"

// double
err_t string_to_data (const string &src, double &dst)
{
  if (src.empty ())
    return string_printf ("Could not convert empty string to int");

  char *endptr = nullptr;
  double res = strtod (src.c_str (), &endptr);

  if (*endptr)
    return err_t (string_printf ("Could not convert \"%s\" to double", src.c_str ()));

  dst = res;
  return ERR_OK;
}
err_t string_from_data (string &dst, const double &src)
{
  dst = string_printf ("%a", src);
  return ERR_OK;
}

// int
err_t string_to_data (const string &src, int &dst)
{
  if (src.empty ())
    return string_printf ("Could not convert empty string to int");

  char *endptr = nullptr;
  int res = static_cast<int> (strtol (src.c_str (), &endptr, 10));

  if (*endptr)
    return err_t (string_printf ("Could not convert \"%s\" to int", src.c_str ()));

  dst = res;
  return ERR_OK;
}
err_t string_from_data (string &dst, const int &src)
{
  dst = string_printf ("%d", src);
  return ERR_OK;
}

// int
err_t string_to_data (const string &src, bool &dst)
{
  if (src == "true")
    {
      dst = true;
      return ERR_OK;
    }
  if (src == "false")
    {
      dst = false;
      return ERR_OK;
    }

  return string_printf ("Could not convert string \"%s\" to bool", src.c_str ());
}
err_t string_from_data (string &dst, const bool &src)
{
  dst = (src ? "true" : "false");
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

// default case
err_t string_to_data (const string &, ...)
{
  assert_check (false, "This should not even be instantiated");
  return err_t ("This should not even be instantiated");
}
err_t string_from_data (string &, ...)
{
  assert_check (false, "This should not even be instantiated");
  return err_t ("This should not even be instantiated");
}
