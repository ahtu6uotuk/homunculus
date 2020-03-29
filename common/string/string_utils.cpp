#include "string_utils.h"

#include <fstream>
#include <sstream>
#include <cstdarg>

#include "common/common.h"
#include "common/err_t.h"

#ifndef _WIN32
__attribute__((format(printf, 1, 2)))
#else
__attribute__((format(__MINGW_PRINTF_FORMAT, 1, 2)))
#endif
std::string string_printf (const char *format, ...)
{
  va_list va;
  va_start (va, format);

#ifndef _WIN32
  va_list va_for_couting;
  va_copy (va_for_couting, va);
  int length = vsnprintf (nullptr, 0, format, va_for_couting);
  va_end (va_for_couting);
#else
  int length = vsnprintf (0, 0, format, va);
#endif

  std::string result;
  if (length > 0)
    {
      result.assign (length, '\0');
      vsprintf (&result[0], format, va);
    }

  va_end (va);

  return result;
}

std::string string_join (const std::vector<std::string> &parts, const std::string &separator)
{
  std::stringstream ss;
  for (size_t i = 0; i < parts.size (); i++)
    {
      if (i != 0)
        ss << separator;
      ss << parts[i];
    }
  return ss.str ();
}

std::vector<std::string> string_split (const std::string &s, const std::string &delim)
{
  std::vector<std::string> result;

  auto start = 0U;
  auto end = s.find (delim);

  while (end != std::string::npos)
    {
      result.push_back (s.substr (start, end - start));
      start = end + delim.length ();
      end = s.find (delim, start);
    }

  result.push_back (s.substr (start, end));
  return result;
}
