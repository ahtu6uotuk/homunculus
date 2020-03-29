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
#include "resource/saveload/saveload_fwd.h"

namespace saveload
{
class node_t
{
public:
  virtual err_t load ();
  virtual err_t save ();

  using xml_node_t = rapidxml::xml_node<>;
  using xml_doc_t = rapidxml::xml_document<>;
  virtual ~node_t ();

protected:
  xml_node_t *m_node;
  std::string m_name;
  xml_doc_t &m_root;
  std::vector<std::unique_ptr<node_t>> m_children;

  template<typename DataT, typename ElemT>
  friend class detail::container_node_t;

  node_t (xml_doc_t &root_node, const std::string &name);
  virtual err_t save_private (bool ignore_defaults = true);
  virtual bool is_default_self () const;
  void set_node_name (const std::string &name);
  void set_node_value (const std::string &value);
  bool is_default () const;

public:
  /// for saveload::rules only

  void spawn_empty_child (const std::string &name);
  node_t &last_child ();

  template<typename DataT, typename ElemT>
  void add_container (DataT &data, const std::string &name, const std::string &elem_name)
  {
    m_children.emplace_back (new detail::container_node_t<DataT, ElemT> (data, m_root, name, elem_name));
  }

  template<typename Data>
  void add_primitive (Data &data, const std::string &name)
  {
    m_children.emplace_back (new detail::primitive_node_t<Data> (data, m_root, name));
  }

  template<typename Data>
  void add_complex_structure (Data &data, const std::string &name)
  {
    m_children.emplace_back (new node_t (m_root, name));
    data.build_saveload_tree (*m_children.back ());
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
  virtual bool is_default_self () const override
  {
    return typed_is_default (m_data);
  }

private:
  Primitive &m_data;
};

template<typename DataT, typename ElemT>
class container_node_t : public node_t
{
public:
  virtual ~container_node_t () {}
  container_node_t (DataT &data, xml_doc_t &root, const std::string &name, const std::string &elem_name)
    : node_t (root, name), m_data (data), m_elem_name (elem_name)
  {
  }

  err_t save () override { return save_private (false /*ignore_defaults*/); }
  err_t load () override
  {
    assert_check (m_node, "Node not set when trying to load");

    for (xml_node_t *current_node = m_node->first_node (); current_node; current_node = current_node->next_sibling ())
      {
        if (current_node->name () != m_elem_name)
          return string_printf (
              "Unexpected data \"%s\", expected element with name \"%s\"",
              xml_node_to_string (*current_node).c_str (), m_elem_name.c_str ());

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
  virtual bool is_default_self () const override
  {
    DataT empty;
    return m_data == empty;
  }

private:
  DataT &m_data;
  std::string m_elem_name;
};
}
}
