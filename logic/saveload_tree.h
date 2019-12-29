#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include <type_traits>

#include "common/common.h"
#include "common/err_t.h"
#include "common/string/string_converters.h"
#include "common/string/string_utils.h"
#include "external/rapidxml/rapidxml.hpp"
template <typename Self, typename ... Args>
class object;
class object_base;
namespace detail {
class saveload_container_node_base;
template<typename DataT, typename ElemT>
class saveload_container_node;
}

template<typename Data>
err_t save (const Data &src, string &dst);

template<typename Data>
err_t load (Data &dst, const string &src);

class saveload_node
{
public:
  /// This part should be modified when new types of data are added.
  ///

  /// primitives
  void add (double &data, const string &name) { add_primitive (data, name); }
  void add (int &data, const string &name) { add_primitive (data, name); }
  void add (string &data, const string &name) { add_primitive (data, name); }

  /// pair
  template<typename Type1, typename Type2>
  void add (pair<Type1, Type2> &data, const string &name)
  {
    m_children.emplace_back (new saveload_node (m_root, name));
    m_children.back ()->add (data.first, "pair_first");
    m_children.back ()->add (data.second, "pair_second");
  }

  /// vector
  template<typename VectElem>
  void add (vector<VectElem> &data, const string &name)
  {
    add_container<vector<VectElem>, VectElem> (data, name);
    for (VectElem &elem : data)
      m_children.back ()->add (elem, "vect_elem");
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
    add_container<unordered_map<MapKey, MapValue>, pair<MapKey, MapValue>> (data, name);

    vector<pair<const MapKey, MapValue> *> ordered_pairs;
    for (pair<const MapKey, MapValue> &elem : data)
      ordered_pairs.push_back (&elem);
    sort (ordered_pairs.begin (), ordered_pairs.end (), [] (auto a, auto b) { return a->first < b->first; });

    for (pair<const MapKey, MapValue> *elem : ordered_pairs)
      {
        m_children.back ()->m_children.emplace_back (new saveload_node (m_root, "map_elem"));
        m_children.back ()->m_children.back ()->add (const_cast<MapKey &> (elem->first), "key");
        m_children.back ()->m_children.back ()->add (elem->second, "value");
      }
  }
  template<typename MapKey, typename MapValue>
  static void add_elem (unordered_map<MapKey, MapValue> &data, unique_ptr<pair<MapKey, MapValue>> elem_to_add)
  {
    data.insert (move (*elem_to_add));
  }

  /// unique_ptr
  template<typename DataT>
  void add (unique_ptr<DataT> &data, const string &name)
  {
    add_container<unique_ptr<DataT>, DataT> (data, name);
    if (data)
      m_children.back ()->add (*data, "unique_ptr_contents");
  }
  template<typename DataT>
  static void add_elem (unique_ptr<DataT> &data, unique_ptr<DataT> elem_to_add)
  {
    data = move (elem_to_add);
  }

  /// composite objects
  template<typename Data, typename ConditionallyVoid = enable_if_t<is_base_of_v<object_base, Data>, void>>
  ConditionallyVoid add (Data &data, const string &name)
  {
    m_children.emplace_back (new saveload_node (m_root, name));
    saveload_node &node = *m_children.back ();
    auto func = [&node] (auto attr) { attr->build_saveload_tree_policy (node); };
    data.for_all_attrs (func);
  }

  /// everything else
  template<typename Data, enable_if_t<!is_base_of_v<object_base, Data>, int> = 0>
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
  void set_node_name (const string &name);
  void set_node_value (const string &value);
  template<typename DataT, typename ElemT>
  void add_container (DataT &data, const string &name);
  template<typename Data>
  void add_primitive (Data &data, const string &name);
  template<typename Data>
  void add_complex_structure (Data &data, const string &name);

  doc_t &m_root;
  string m_name;

  vector<unique_ptr<saveload_node>> m_children;
  node_t *m_node;
};

namespace detail
{
std::string xml_node_to_string (const rapidxml::xml_node<> &node);

class saveload_root : public saveload_node
{
public:
  virtual ~saveload_root ();
  saveload_root ();

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
  virtual err_t load () override;
  virtual err_t save () override;

private:
  Primitive &m_data;
};

template<typename DataT, typename ElemT>
class saveload_container_node : public saveload_node
{
public:
  virtual ~saveload_container_node () {}
  saveload_container_node (DataT &data, doc_t &root, const string &name)
    : saveload_node (root, name), m_data (data)
  {
  }

  err_t load () override
  {
    assert_check (m_node, "Node not set when trying to load");
    node_t *current_node = m_node->first_node ();
    for (; current_node; current_node = current_node->next_sibling ())
      {
        unique_ptr<ElemT> load_target = make_unique<ElemT> ();
        add (*load_target, m_name); // this is going to make a null reference. but so what?
        m_children.back ()->m_node = current_node;

        err_t err = m_children.back ()->load ();
        if (!err.ok ())
          return err;

        add_elem (m_data, move (load_target));
      }

    if (current_node)
      return err_t (string_printf (
          "Given xml node \"%s\" has too many elements", detail::xml_node_to_string (*m_node).c_str ()));

    return ERR_OK;
  }

private:
  DataT &m_data;
};
}  // namespace detail

template<typename Data>
err_t save (const Data &src, string &dst)
{
  detail::saveload_root root;

  saveload_node::node_t *root_node
      = root.m_root_ownership.allocate_node (rapidxml::node_type::node_element, "root");
  root.set_node (root_node);
  root.m_root_ownership.append_node (root_node);

  root.add (const_cast<Data &> (src), "data");
  // It would be great to get rid of this const_cast.
  // I don't know how though.

  err_t err = root.save ();
  if (err.ok ())
    dst = detail::xml_node_to_string (root.m_root_ownership);

  return err;
}

template<typename Data>
err_t load (Data &dst, const string &src)
{
  detail::saveload_root root;

  vector<char> copy (src.begin (), src.end ());
  copy.push_back ('\0');

  string errstr = "";
  try
    {
      root.m_root_ownership.parse<0> (&copy[0]);
    }
  catch (const std::runtime_error &e)
    {
      errstr = string ("Runtime error was: ") + e.what ();
    }
  catch (const rapidxml::parse_error &e)
    {
      errstr = string ("Parse error was: ") + e.what ();
    }
  catch (const std::exception &e)
    {
      errstr = string ("Error was: ") + e.what ();
    }
  catch (...)
    {
      errstr = string ("Internal error");
    }

  err_t err (errstr);
  if (!err.ok ())
    return err_t (string_printf ("Error encountered while parsing xml: %s\n", errstr.c_str ()));

  root.set_node (root.m_root_ownership.first_node ());
  root.add (dst, "data");
  return root.load ();
}

template<typename DataT, typename ElemT>
void saveload_node::add_container (DataT &data, const string &name)
{
  m_children.emplace_back (new detail::saveload_container_node<DataT, ElemT> (data, m_root, name));
}

template<typename Data>
void saveload_node::add_primitive (Data &data, const string &name)
{
  m_children.push_back (make_unique<detail::saveload_primitive_node<Data>> (data, m_root, name));
}

template<typename Data>
void saveload_node::add_complex_structure (Data &data, const string &name)
{
  m_children.emplace_back (new saveload_node (m_root, name));
  data.build_saveload_tree (*m_children.back ());
}

template<typename Primitive>
err_t detail::saveload_primitive_node<Primitive>::load ()
{
  string src = m_node->value ();
  err_t err = string_to_data (src, m_data);
  if (!err.ok ())
    return err;

  return ERR_OK;
}

template<typename Primitive>
err_t detail::saveload_primitive_node<Primitive>::save ()
{
  string dst;
  err_t err = string_from_data (dst, m_data);
  if (!err.ok ())
    return err;
  set_node_value (dst);

  return ERR_OK;
}
