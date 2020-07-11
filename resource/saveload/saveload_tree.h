#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include <type_traits>
#include <algorithm>

#include "common/common.h"
#include "common/err_t.h"
#include "common/string/string_converters.h"
#include "common/string/string_utils.h"
#include "common/template_tricks/comparator.h"
#include "common/template_tricks/has_member.h"
#include "external/rapidxml/rapidxml.hpp"
#include "resource/saveload/saveload_default_helpers.h"
#include "resource/saveload/saveload_detail_typedefs.h"
#include "resource/saveload/saveload_fwd.h"

namespace saveload
{
class node_t
{
public:
  virtual err_t load ();
  virtual err_t save ();

  virtual ~node_t ();

protected:
  default_val_holder_base *m_default_holder = nullptr;
  xml_node_t *m_node = nullptr;
  std::string m_name;
  xml_doc_t &m_root;
  std::vector<defaultable_val> m_children;

  template<typename DataT, typename ElemT>
  friend class detail::container_node_t;
  friend struct defaultable_val;
  friend struct default_val_holder_base;

  virtual err_t save_private (bool ignore_defaults = true);
  void set_node_name (const std::string &name);
  void set_node_value (const std::string &value);
  virtual bool operator == (const node_t &other) const;
  node_t (xml_doc_t &root_node, const std::string &name);

  template<typename DataT>
  void add_node_and_default (create_node_func_t<DataT> cr_func, DataT &data)
  {
    std::unique_ptr<node_t> filled_node = cr_func (m_root, data);
    default_val_holder<DataT> *default_holder = new default_val_holder<DataT> (m_root, cr_func);
    m_children.emplace_back (std::move (filled_node), default_holder);
  }

public:
  /// for saveload::rules only

  node_t &last_child ();

  template<typename DataT, typename ElemT>
  void add_container (DataT &data, const std::string &name)
  {
    create_node_func_t<DataT> cr_func = [name] (xml_doc_t &root, DataT &idata) {
      return std::unique_ptr<node_t> (new detail::container_node_t<DataT, ElemT> (idata, root, name));
    };
    add_node_and_default (cr_func, data);
  }

  template<typename DataT>
  void add_primitive (DataT &data, const std::string &name)
  {
    create_node_func_t<DataT> cr_func = [name] (xml_doc_t &root, DataT &idata) {
      return std::unique_ptr<node_t> (new detail::primitive_node_t<DataT> (idata, root, name));
    };
    add_node_and_default (cr_func, data);
  }

  template<typename DataT>
  void add_complex_structure (DataT &data, const std::string &name)
  {
    create_node_func_t<DataT> cr_func = [name] (xml_doc_t &root, DataT &idata) {
      std::unique_ptr<node_t> new_node (new node_t (root, name));
      idata.build_saveload_tree (*new_node);
      return new_node;
    };
    add_node_and_default (cr_func, data);
  }

  template<typename DataT>
  void add_external_complex_structure (DataT &data, const std::string &name, fill_node_func_t<DataT> fill_func)
  {
    create_node_func_t<DataT> cr_func = [name, fill_func] (xml_doc_t &root, DataT &idata) {
      std::unique_ptr<node_t> new_node (new node_t (root, name));
      fill_func (*new_node, idata);
      return new_node;
    };
    add_node_and_default (cr_func, data);
  }
};

namespace detail
{

std::string xml_node_to_string (const rapidxml::xml_node<> &node);

GENERATE_HAS_MEMBER (build_saveload_tree)

class root_node_t : public node_t
{
public:
  virtual ~root_node_t ();
  root_node_t ();
  err_t save () override { return save_private (false /*ignore_defaults*/); }

  void set_node (xml_node_t *node);
  xml_doc_t m_root_ownership;
};

template<typename Primitive>
class primitive_node_t : public node_t
{
public:
  virtual ~primitive_node_t () {}
  primitive_node_t (Primitive &data, xml_doc_t &root, const std::string &name)
    : node_t (root, name), m_data (data)
  {
  }
  virtual err_t load () override
  {
    std::string src = m_node->value ();
    err_t err = string_to_data (src, m_data);
    if (!err.ok ())
      return err;

    return ERR_OK;
  }
  virtual err_t save_private (bool) override
  {
    std::string dst;
    err_t err = string_from_data (dst, m_data);
    if (!err.ok ())
      return err;
    set_node_value (dst);

    return ERR_OK;
  }
  virtual bool operator == (const node_t &other) const override
  {
    using this_type = primitive_node_t<Primitive>;
    const this_type *typed_other = dynamic_cast<const this_type *> (&other);
    if (!typed_other)
      return false;
    return typed_compare (m_data, typed_other->m_data);
  }

private:
  Primitive &m_data;
};

template<typename DataT, typename ElemT>
class container_node_t : public node_t
{
public:
  virtual ~container_node_t () {}
  container_node_t (DataT &data, xml_doc_t &root, const std::string &name)
    : node_t (root, name), m_data (data)
  {
  }

  err_t save () override { return save_private (false /*ignore_defaults*/); }
  err_t load () override
  {
    assert_check (m_node, "Node not set when trying to load");

    for (xml_node_t *current_node = m_node->first_node (); current_node; current_node = current_node->next_sibling ())
      {
        std::unique_ptr<ElemT> load_target = std::make_unique<ElemT> ();
        saveload::add (*this, *load_target, m_name); // this is going to make a null reference. but so what?
        m_children.back ()->m_node = current_node;

        err_t err = m_children.back ()->load ();
        if (!err.ok ())
          return err;

        saveload::detail::add_elem (m_data, std::move (load_target));
      }

    return ERR_OK;
  }

private:
  DataT &m_data;
};
}
}
