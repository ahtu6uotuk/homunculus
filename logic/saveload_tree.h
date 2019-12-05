#pragma once
#include <vector>
#include <memory>
#include "common/common.h"
#include "common/err_t.h"
#include "common/string_converters.h"
#include "common/string_utils.h"
#include "external/rapidxml_helpers/rapidxml_wrapper.h"

template<typename Data>
err_t save (const Data &src, string &dst);

template <typename Data>
err_t load (Data &dst, const string &src);

class saveload_node
{
public:
/// This part should be modified when new types of data are added.
///
  void add (double &data, const string &name) { add_primitive (data, name); }
  void add (int &data, const string &name) { add_primitive (data, name); }
  void add (string &data, const string &name) { add_primitive (data, name); }

  template<typename VectElem>
  void add (vector<VectElem> &data, const string &name)
  {
    m_children.push_back (unique_ptr<saveload_node> (new saveload_node (m_root, name)));
    for (VectElem &elem : data)
      m_children.back ()->add_primitive (elem, "elem");
  }

  template<typename Data>
  void add (Data &data, const string &name) { add_complex_structure (data, name); }

/// Everything below this is details. They should be changed in case of bugs,
/// but not by design.

public:
  virtual err_t load ();
  virtual err_t save ();

  using node_t = rapidxml::xml_node<>;
  using doc_t = rapidxml::xml_document<>;
  virtual ~saveload_node ();

protected:
  saveload_node (doc_t &root_node, const string &name);
  void set_node_name (const string &name);
  void set_node_value (const string &value);
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
class saveload_root : public saveload_node
{
public:
  virtual ~saveload_root ();
  saveload_root ();

  void set_node (node_t *node);
  doc_t m_root_ownership;
};

template <typename Data>
class saveload_data_node : public saveload_node
{
public:
  virtual ~saveload_data_node () {}
  saveload_data_node (Data &data, doc_t &root, const string &name)
    : saveload_node (root, name), m_data (data) {}
  virtual err_t load ();
  virtual err_t save ();
private:
  Data &m_data;
};
}

template<typename Data>
err_t save (const Data &src, string &dst)
{
  detail::saveload_root root;

  saveload_node::node_t *root_node = root.m_root_ownership.allocate_node (rapidxml::node_type::node_element, "root");
  root.set_node (root_node);
  root.m_root_ownership.append_node (root_node);

  const_cast<Data &> (src).build_saveload_tree (root);
  // It would be great to get rid of this const_cast.
  // I don't know how though.

  err_t err = root.save ();
  if (err.ok ())
    dst = xml_node_to_string (root.m_root_ownership);

  return err;
}

template <typename Data>
err_t load (Data &dst, const string &src)
{
  detail::saveload_root root;

  vector<char> copy (src.begin (), src.end ());
  copy.push_back ('\0');

  string errstr = "";
  try { root.m_root_ownership.parse<0> (&copy[0]); }
  catch (const std::runtime_error& e) { errstr = string ("Runtime error was: ") + e.what (); }
  catch (const rapidxml::parse_error& e) { errstr = string ("Parse error was: ") + e.what (); }
  catch (const std::exception& e) { errstr = string ("Error was: ") + e.what (); }
  catch (...) { errstr = string ("Internal error"); }

  err_t err (errstr);
  if (!err.ok ())
    return err_t (string_printf ("Error encountered while parsing xml: %s\n", errstr.c_str ()));

  root.set_node (root.m_root_ownership.first_node ());
  dst.build_saveload_tree (root);
  return root.load ();
}

template<typename Data>
void saveload_node::add_primitive (Data &data, const string &name)
{
  m_children.push_back (make_unique<detail::saveload_data_node<Data>> (data, m_root, name));
}

template<typename Data>
void saveload_node::add_complex_structure (Data &data, const string &name)
{
  m_children.push_back (unique_ptr<saveload_node> (new saveload_node (m_root, name)));
  data.build_saveload_tree (*m_children.back ());
}

template <typename Data>
err_t detail::saveload_data_node<Data>::load ()
{
  string src = m_node->value ();
  err_t err = string_to_data (src, m_data);
  if (!err.ok ())
    return err;
  return saveload_node::load ();
}

template <typename Data>
err_t detail::saveload_data_node<Data>::save ()
{
  string dst;
  err_t err = string_from_data (dst, m_data);
  if (!err.ok ())
    return err;
  set_node_value (dst);
  return saveload_node::save ();
}
