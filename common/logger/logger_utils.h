#pragma once
#include <string>

class logger_t;

namespace logger_utils
{
  template<typename T>
  void print_var_info (const char *var_name, const T &var_value);
}
