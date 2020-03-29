#pragma once

#include "common/common.h"
#include "common/file_utils.h"
#include "common/err_t.h"
#include "common/template_tricks/string_literal.h"
#include "resource/resource_manager.h"

template <typename DataT, const char *asset_name>
class asset_ptr
{
public:
  DataT *get () { return m_cached_ptr; }
  DataT *operator-> () { return m_cached_ptr; }
  DataT &operator * () { return *m_cached_ptr; }

  ~asset_ptr () { die (); }
  asset_ptr () { init (); }
  asset_ptr (const asset_ptr<DataT, asset_name> &) { init (); }

private:
  DataT *m_cached_ptr = nullptr;

  void init ()
  {
    resource_manager &mgr = resource_manager::instance ();
    m_cached_ptr = mgr.get_resource<DataT> (asset_name);
  }
  void die ()
  {
    resource_manager &mgr = resource_manager::instance ();
    mgr.pop_resource<DataT> (asset_name);
  }
};
