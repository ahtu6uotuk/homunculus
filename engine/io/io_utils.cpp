#include "io_utils.h"
#include <fstream>
#include <iterator>

err_t read_file_data (const std::string &filename, std::string &data)
{
  std::ifstream fdata (filename, std::ios_base::in);

  if (!fdata.is_open ())
    return std::string ("can't open ").append (filename);

  fdata.seekg (0, std::ios::end);
  const auto file_size = fdata.tellg ();
  fdata.seekg (0, std::ios::beg);
  data.resize (file_size);
  data.assign (std::istreambuf_iterator<char> (fdata), std::istreambuf_iterator<char> ());

  if (fdata.bad ())
    return std::string ("can't read ").append (filename);

  return ERR_OK;
}
