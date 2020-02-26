#pragma once
#ifndef IO_UTILS_H
#define IO_UTILS_H
#include "common/err_t.h"

err_t read_file_data (const string &filename, unique_ptr<char[]> &data);

#endif // IO_UTILS_H
