#ifndef LOGGER_UTILS_H
#define LOGGER_UTILS_H
#pragma once
#include <string>

class logger_t;

namespace logger_utils
{
  template<typename T>
  void print_var_info (logger_t &logger, const char *var_name, const T &var_value);
}

#endif // LOGGER_UTILS_H
