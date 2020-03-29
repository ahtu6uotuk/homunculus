#include "resource_manager.h"

resource_manager &resource_manager::instance ()
{
  static resource_manager inst;
  return inst;
}

void resource_manager::pop_resource (const std::string &asset_name)
{
  auto it = m_loaded_resources.find (asset_name);
  assert_check (it != m_loaded_resources.end (), "Reference count went wrong");

  if (--it->second.m_refcount == 0)
    m_loaded_resources.erase (asset_name);
}
