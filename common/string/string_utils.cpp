#include "string_utils.h"

#include <fstream>
#include <sstream>
#include <cstdarg>
#include <cstring>

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

std::vector<std::string> string_split (const std::string &string_to_split, char delimiter)
{
  std::vector<std::string> result;

  const char *begin_substr = string_to_split.c_str ();
  const char *end_substr = nullptr;

  do
    {
      end_substr = strchr (begin_substr, delimiter);
      if (end_substr != nullptr)
        {
          result.push_back (std::string (begin_substr, end_substr));
          begin_substr = end_substr + 1;
        }
      else
        result.push_back (std::string (begin_substr));
    }
  while (end_substr != nullptr);

  return result;
}
