#include "string_utils.h"

#include<fstream>
#include<sstream>

#include "common/common.h"
#include "common/err_t.h"

err_t to_file (const string &src_string, const string &dst_filename)
{
  fstream file_stream;

  file_stream.open (dst_filename, ios_base::out);
  if (!file_stream.is_open ())
    return string_printf ("Couldn't open file %s", dst_filename);

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
    return string_printf ("Couldn't open file %s", src_filename);

  stringstream buffer;
  buffer << file_stream.rdbuf();

  dst_string = buffer.str ();
  file_stream.close ();

  return ERR_OK;
}
