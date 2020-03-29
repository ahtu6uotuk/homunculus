#pragma once
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "common/common.h"
class err_t;

#ifndef _WIN32
__attribute__((format(printf, 1, 2)))
#else
__attribute__((format(__MINGW_PRINTF_FORMAT, 1, 2)))
#endif
std::string string_printf (const char *format, ...);

inline std::string string_replace (
    const std::string &src,
    const std::string &to_replace,
    const std::string &replacement)
{
  std::string x = src;
  size_t pos = 0;

  while ((pos = x.find (to_replace, pos)) != std::string::npos)
    {
      x.replace (pos, to_replace.size (), replacement);
      pos += replacement.size ();
    }
  return x;
}

std::string string_join (const std::vector<std::string> &parts, const std::string &separator);
std::vector<std::string> string_split (const std::string &s, const std::string &delim);

inline std::string &ltrim (std::string &s, const char *t = " \t\n\r\f\v")
{
  s.erase (0, s.find_first_not_of (t));
  return s;
}

inline std::string &rtrim (std::string &s, const char *t = " \t\n\r\f\v")
{
  s.erase (s.find_last_not_of (t) + 1);
  return s;
}

inline std::string &trim (std::string &s, const char *t = " \t\n\r\f\v")
{
  return ltrim (rtrim (s, t), t);
}

inline std::string ltrim_copy (std::string s, const char *t = " \t\n\r\f\v")
{
  return ltrim (s, t);
}

inline std::string rtrim_copy (std::string s, const char *t = " \t\n\r\f\v")
{
  return rtrim (s, t);
}

inline std::string trim_copy (std::string s, const char *t = " \t\n\r\f\v")
{
  return trim (s, t);
}
