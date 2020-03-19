#include "err_t.h"

#include "common/common.h"

void assert_error (err_t err, const std::string &additional_info)
{
  assert_check (err.ok (), err.descr () + additional_info);
}
