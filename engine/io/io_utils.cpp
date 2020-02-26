#include "io_utils.h"
#include <fstream>

err_t read_file_data (const string &filename, unique_ptr<char[]> &data)
{
  ifstream fdata (filename, ios_base::in);

  if (!fdata.is_open ())
    return string ("can't open ").append (filename);

  fdata.seekg (0, ios::end);
  const auto file_size = fdata.tellg ();
  fdata.seekg (0, ios::beg);
  data = make_unique<char[]> (fdata.tellg ());
  fdata.read (data.get (), file_size);

  if (fdata.bad ())
    return string ("can't read ").append (filename);

  return ERR_OK;
}
