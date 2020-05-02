#include "saveload_default_helpers.h"

#include "resource/saveload/saveload_tree.h"

saveload::defaultable_val::defaultable_val (std::unique_ptr<node_t> val, default_val_holder_base *get_default)
  : m_val (std::move (val)), m_get_default (get_default)
{
  m_val->m_default_holder = m_get_default.get ();
}

saveload::default_val_holder_base::default_val_holder_base (xml_doc_t &root) : m_root (root) {}

bool saveload::defaultable_val::operator== (const defaultable_val &other) const
{
  return *m_val == *other.m_val;
}
