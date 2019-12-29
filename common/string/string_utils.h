#pragma once
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>

#include "common/common.h"

template<typename... Args>
string string_printf (const char *format, Args... args)
{
  size_t size = snprintf (nullptr, 0, format, args...) + 1;
  std::unique_ptr<char[]> buf (new char[size]);
  snprintf (buf.get (), size, format, args...);
  return std::string (buf.get (), buf.get () + size - 1);
}

inline string string_replace (
    const std::string &src,
    const std::string &to_replace,
    const std::string &replacement)
{
  string x = src;
  size_t pos = 0;

  while ((pos = x.find (to_replace, pos)) != std::string::npos)
    {
      x.replace (pos, to_replace.size (), replacement);
      pos += replacement.size ();
    }
  return x;
}

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
