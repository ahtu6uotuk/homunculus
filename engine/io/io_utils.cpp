#include "io_utils.h"
#include <fstream>
#include <iterator>

err_t read_file_data (const string &filename, string &data)
{
  ifstream fdata (filename, ios_base::in);

  if (!fdata.is_open ())
    return string ("can't open ").append (filename);

  fdata.seekg (0, ios::end);
  const auto file_size = fdata.tellg ();
  fdata.seekg (0, ios::beg);
  data.resize (file_size);
  data.assign (istreambuf_iterator<char> (fdata), istreambuf_iterator<char> ());

  if (fdata.bad ())
    return string ("can't read ").append (filename);

  return ERR_OK;
}
