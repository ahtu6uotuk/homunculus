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
#include "external/rapidxml/rapidxml.hpp"
#include "logic/saveload/saveload_tree_fwd.h"

class saveload_node
{
public:
  /// This part should be modified when new types of data are added.
  ///

  /// primitives
  void add (double &data, const string &name) { add_primitive (data, name); }
  void add (int &data, const string &name) { add_primitive (data, name); }
  void add (string &data, const string &name) { add_primitive (data, name); }
  void add (bool &data, const string &name) { add_primitive (data, name); }

  /// pair
  template<typename Type1, typename Type2>
  void add (pair<Type1, Type2> &data, const string &name)
  {
    m_children.emplace_back (new saveload_node (m_root, name));
    m_children.back ()->add (data.first, "first");
    m_children.back ()->add (data.second, "second");
  }

  /// vector
  template<typename VectElem>
  void add (vector<VectElem> &data, const string &name)
  {
    string elem_name = "elem";
    add_container<vector<VectElem>, VectElem> (data, name, elem_name);
    for (VectElem &elem : data)
      m_children.back ()->add (elem, elem_name);
  }
  template<typename VectElem>
  static void add_elem (vector<VectElem> &data, unique_ptr<VectElem> elem_to_add)
  {
    data.push_back (move (*elem_to_add));
  }

  /// map
  template<typename MapKey, typename MapValue>
  void add (unordered_map<MapKey, MapValue> &data, const string &name)
  {
    string elem_name = "entry";
    add_container<unordered_map<MapKey, MapValue>, pair<MapKey, MapValue>> (data, name, elem_name);

    vector<pair<const MapKey, MapValue> *> ordered_pairs;
    for (pair<const MapKey, MapValue> &elem : data)
      ordered_pairs.push_back (&elem);

    sort (ordered_pairs.begin (), ordered_pairs.end (), [] (auto a, auto b) { return a->first < b->first; });

    for (pair<const MapKey, MapValue> *elem : ordered_pairs)
      {
        pair<MapKey &, MapValue &> unconst_pair (const_cast<MapKey &> (elem->first), elem->second);
        m_children.back ()->add (unconst_pair, elem_name);
      }
  }
  template<typename MapKey, typename MapValue>
  static void add_elem (unordered_map<MapKey, MapValue> &data, unique_ptr<pair<MapKey, MapValue>> elem_to_add)
  {
    assert_check (!data.count (elem_to_add->first), "Map can't have two elements with same key");
    data.insert (move (*elem_to_add));
  }

  /// unique_ptr
  template<typename DataT>
  void add (unique_ptr<DataT> &data, const string &name)
  {
    string elem_name = "entry";
    add_container<unique_ptr<DataT>, DataT> (data, name, elem_name);
    if (data)
      m_children.back ()->add (*data, elem_name);
  }
  template<typename DataT>
  static void add_elem (unique_ptr<DataT> &data, unique_ptr<DataT> elem_to_add)
  {
    data = move (elem_to_add);
  }

  /// enums
  template<typename Data, enable_if_t<is_enum_v<Data>, int> = 0>
  void add (Data &data, const string &name)
  {
    add_primitive (data, name);
  }

  /// composite objects
  template<typename Data, enable_if_t<is_base_of_v<object_base, Data>, int> = 0>
  void add (Data &data, const string &name)
  {
    m_children.emplace_back (new saveload_node (m_root, name));
    saveload_node &node = *m_children.back ();
    auto func = [&node] (auto attr) { attr->policy_build_saveload_tree (node); };
    data.for_all_attrs (func);
  }

  /// everything else
  template<typename Data, enable_if_t<detail::can_build_saveload_tree<Data>::value, int> = 0>
  void add (Data &data, const string &name)
  {
    add_complex_structure (data, name);
  }

  /// Everything below this is details. They should be changed in case of bugs,
  /// but not by design.

public:
  virtual err_t load ();
  virtual err_t save ();

  using node_t = rapidxml::xml_node<>;
  using doc_t = rapidxml::xml_document<>;
  virtual ~saveload_node ();

protected:
  template<typename DataT, typename ElemT>
  friend class detail::saveload_container_node;
  saveload_node (doc_t &root_node, const string &name);
  virtual err_t save_private (bool ignore_defaults = true);
  void set_node_name (const string &name);
  void set_node_value (const string &value);
  bool is_default () const
  {
    if (!is_default_self ())
      return false;
    return all_of (m_children.begin (), m_children.end (), [] (auto &a) { return a->is_default (); });
  }
  virtual bool is_default_self () const { return true; }
  template<typename DataT, typename ElemT>
  void add_container (DataT &data, const string &name, const string &elem_name)
  {
    m_children.emplace_back (
        new detail::saveload_container_node<DataT, ElemT> (data, m_root, name, elem_name));
  }
  template<typename Data>
  void add_primitive (Data &data, const string &name)
  {
    m_children.emplace_back (new detail::saveload_primitive_node<Data> (data, m_root, name));
  }
  template<typename Data>
  void add_complex_structure (Data &data, const string &name)
  {
    m_children.emplace_back (new saveload_node (m_root, name));
    data.build_saveload_tree (*m_children.back ());
  }

  doc_t &m_root;
  string m_name;

  vector<unique_ptr<saveload_node>> m_children;
  node_t *m_node;
};

namespace detail
{
std::string xml_node_to_string (const rapidxml::xml_node<> &node);

template<typename T>
class can_build_saveload_tree
{
  typedef char Yes[1];
  typedef char No[2];

  template<typename C>
  static Yes &test (decltype (&C::build_saveload_tree));
  template<typename C>
  static No &test (...);

public:
  enum { value = sizeof (test<T> (0)) == sizeof (Yes) };
};

class saveload_root : public saveload_node
{
public:
  virtual ~saveload_root ();
  saveload_root ();
  err_t save () override { return save_private (false /*ignore_defaults*/); }

  void set_node (node_t *node);
  doc_t m_root_ownership;
};

template<typename Primitive>
class saveload_primitive_node : public saveload_node
{
public:
  virtual ~saveload_primitive_node () {}
  saveload_primitive_node (Primitive &data, doc_t &root, const string &name)
    : saveload_node (root, name), m_data (data)
  {
  }
  virtual err_t load () override
  {
    string src = m_node->value ();
    err_t err = string_to_data (src, m_data);
    if (!err.ok ())
      return err;

    return ERR_OK;
  }
  virtual err_t save_private (bool) override
  {
    string dst;
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
class saveload_container_node : public saveload_node
{
public:
  virtual ~saveload_container_node () {}
  saveload_container_node (DataT &data, doc_t &root, const string &name, const string &elem_name)
    : saveload_node (root, name), m_data (data), m_elem_name (elem_name)
  {
  }

  err_t save () override { return save_private (false /*ignore_defaults*/); }
  err_t load () override
  {
    assert_check (m_node, "Node not set when trying to load");

    for (node_t *current_node = m_node->first_node (); current_node; current_node = current_node->next_sibling ())
      {
        if (current_node->name () != m_elem_name)
          return string_printf (
              "Unexpected data \"%s\", expected element with name \"%s\"",
              detail::xml_node_to_string (*current_node).c_str (), m_elem_name.c_str ());

        unique_ptr<ElemT> load_target = make_unique<ElemT> ();
        add (*load_target, m_name); // this is going to make a null reference. but so what?
        m_children.back ()->m_node = current_node;

        err_t err = m_children.back ()->load ();
        if (!err.ok ())
          return err;

        add_elem (m_data, move (load_target));
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
  string m_elem_name;
};
}  // namespace detail
