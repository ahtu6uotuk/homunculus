#pragma once
#include "common/common.h"

class err_t
{
public:
  err_t (const string &description) : m_description (description) {}
  bool ok () { return m_description.empty (); }
  const string &descr () { return m_description; }
  const char *descr_c_str () { return m_description.c_str (); }
private:
  string m_description;
};
const err_t ERR_OK = err_t ("");

void assert_test (err_t err, const string &additional_info = "");
