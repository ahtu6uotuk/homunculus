#pragma once

#include "resource/saveload/saveload_detail_typedefs.h"

namespace saveload
{

struct default_val_holder_base
{
  virtual ~default_val_holder_base () {}
  default_val_holder_base (xml_doc_t &root);

  virtual std::unique_ptr<node_t> make_node () = 0;

  xml_doc_t &m_root;
};


template<typename DataT>
struct default_val_holder : default_val_holder_base
{
  ~default_val_holder () {}

  default_val_holder (xml_doc_t &root, create_node_func_t<DataT> cr_func)
    : default_val_holder_base (root), m_cr_func (cr_func)
  {
  }

  std::unique_ptr<node_t> make_node () override
  {
    m_data_ownership = std::make_unique<DataT> ();
    return m_cr_func (m_root, *m_data_ownership);
  }

private:
  create_node_func_t<DataT> m_cr_func;
  std::unique_ptr<DataT> m_data_ownership;
};


struct defaultable_val
{
  defaultable_val (std::unique_ptr<node_t> val, default_val_holder_base *get_default);
  bool operator == (const defaultable_val &other) const;

  node_t *operator -> () { return m_val.get (); }
  node_t &operator * () { return *m_val; }
  const node_t *operator -> () const { return m_val.get (); }
  const node_t &operator * () const { return *m_val; }

private:
  std::unique_ptr<node_t> m_val;
  std::unique_ptr<default_val_holder_base> m_get_default;
};

}
