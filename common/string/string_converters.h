#pragma once
#include <vector>

#include "common/common.h"
#include "common/err_t.h"
class err_t;

err_t string_to_data (const string &src, double &dst);
err_t string_from_data (string &dst, const double &src);

err_t string_to_data (const string &src, int &dst);
err_t string_from_data (string &dst, const int &src);

err_t string_to_data (const string &src, string &dst);
err_t string_from_data (string &dst, const string &src);

template<typename Data>
err_t string_to_data (const string &src, Data &dst)
{
  do_nothing (src, dst);
  assert_check (false, "This should not even be instantiated");
  return err_t ("This should not even be instantiated");
}

template<typename Data>
err_t string_from_data (string &src, const Data &dst)
{
  do_nothing (src, dst);
  assert_check (false, "This should not even be instantiated");
  return err_t ("This should not even be instantiated");
}
