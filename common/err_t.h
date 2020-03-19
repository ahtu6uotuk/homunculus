#pragma once
#include <string>

class err_t
{
public:
  err_t (const std::string &description) : m_description (description) {}
  bool ok () const { return m_description.empty (); }
  const std::string &descr () { return m_description; }
  const char *descr_c_str () { return m_description.c_str (); }
  operator bool () const { return !ok (); }

private:
  std::string m_description;
};
const err_t ERR_OK = err_t ("");

void assert_error (err_t err, const std::string &additional_info = "");
#define RETURN_IF_FAIL(A) {err_t __err = A; if (!__err.ok ()) return __err;}
