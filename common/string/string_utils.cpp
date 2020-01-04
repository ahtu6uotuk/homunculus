#include "string_utils.h"

#include <fstream>
#include <sstream>
#include <cstdarg>

#include "common/common.h"
#include "common/err_t.h"

err_t to_asset_file (const string &src_string, const string &asset_name)
{
  return to_file (src_string, get_assets_path_prefix () + asset_name + ".xml");
}

err_t from_asset_file (string &dst_string, const string &asset_name)
{
  return from_file (dst_string, get_assets_path_prefix () + asset_name + ".xml");
}

err_t to_file (const string &src_string, const string &dst_filename)
{
  fstream file_stream;

  file_stream.open (dst_filename, ios::out);
  if (!file_stream.is_open ())
    return string_printf ("Couldn't open file for writing %s", dst_filename.c_str ());

  file_stream << src_string;
  file_stream.flush ();
  file_stream.close ();

  return ERR_OK;
}

err_t from_file (string &dst_string, const string &src_filename)
{
  fstream file_stream;

  file_stream.open (src_filename, ios_base::in);
  if (!file_stream.is_open ())
    return string_printf ("Couldn't open file for reading %s", src_filename.c_str ());

  stringstream buffer;
  buffer << file_stream.rdbuf();

  dst_string = buffer.str ();
  file_stream.close ();

  return ERR_OK;
}

__attribute__((format(printf, 1, 2)))
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
