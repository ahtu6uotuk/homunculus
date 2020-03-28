#pragma once
#include <vector>

#include "common/common.h"
#include "common/string/string_utils.h"
#include "common/err_t.h"
class err_t;

err_t string_to_data (const std::string &src, double &dst);
err_t string_from_data (std::string &dst, const double &src);

err_t string_to_data (const std::string &src, float &dst);
err_t string_from_data (std::string &dst, const float &src);

err_t string_to_data (const std::string &src, int &dst);
err_t string_from_data (std::string &dst, const int &src);

err_t string_to_data (const std::string &src, std::string &dst);
err_t string_from_data (std::string &dst, const std::string &src);

err_t string_to_data (const std::string &src, bool &dst);
err_t string_from_data (std::string &dst, const bool &src);

template<typename Data, std::enable_if_t<std::is_enum_v<Data>, int> = 0>
err_t string_to_data (const std::string &src, Data &dst)
{
  for (int i = 0; i < (int) Data::COUNT; i++)
    if (enum_to_string ((Data) i) == src)
      {
        dst = (Data) i;
        return ERR_OK;
      }
  return string_printf ("Could not convert \"%s\" to enum of type %s", src.c_str (), typeid (Data).name ());
}

template<typename Data, std::enable_if_t<std::is_enum_v<Data>, int> = 0>
err_t string_from_data (std::string &dst, const Data &src)
{
  dst = enum_to_string (src);
  return ERR_OK;
}

err_t string_to_data (const std::string &, ...);
err_t string_from_data (std::string &, ...);
