#pragma once

#include "common/common.h"
#include "common/file_utils.h"
#include "common/err_t.h"
#include "logic/saveload/saveload.h"
#include "common/template_tricks/string_literal.h"

template <typename DataT, const char *asset_name>
class asset_ptr
{
public:
  DataT *operator-> () { return m_data.operator-> (); }
  DataT *get () { return m_data.get (); }
  DataT &operator * () { return m_data.operator* (); }

  asset_ptr () { init (); }
  asset_ptr (const asset_ptr<DataT, asset_name> &) { init (); }

private:
  void init ()
  {
    m_data = make_unique<DataT> ();
    string file_contents;
    assert_error (from_asset_file (file_contents, asset_name));
    assert_error (load (*m_data, file_contents));
  }
  unique_ptr<DataT> m_data;
};
