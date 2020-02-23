#pragma once
#include "common/common.h"

class err_t
{
public:
  err_t (const string &description) : m_description (description) {}
  bool ok () const { return m_description.empty (); }
  const string &descr () { return m_description; }
  const char *descr_c_str () { return m_description.c_str (); }
  operator bool () const { return !ok (); }

private:
  string m_description;
};
const err_t ERR_OK = err_t ("");

void assert_error (err_t err, const string &additional_info = "");
#define RETURN_IF_FAIL(A) {err_t __err = A; if (!__err.ok ()) return __err;}
