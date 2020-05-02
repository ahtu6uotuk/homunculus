#pragma once

#include "resource/saveload/saveload_rules.h"

namespace saveload
{
template<typename Data>
err_t save (const Data &src, std::string &dst)
{
  detail::root_node_t root;

  xml_node_t *root_node = root.m_root_ownership.allocate_node (rapidxml::node_type::node_element, "root");
  root.set_node (root_node);
  root.m_root_ownership.append_node (root_node);

  add (root, const_cast<Data &> (src), "data");
  // It would be great to get rid of this const_cast.
  // I don't know how though.

  err_t err = root.save ();
  if (err.ok ())
    dst = detail::xml_node_to_string (*root.m_root_ownership.first_node ()->first_node ());

  return err;
}

template<typename Data>
err_t load (Data &dst, const std::string &src)
{
  detail::root_node_t root;

  std::vector<char> copy (src.begin (), src.end ());
  copy.push_back ('\0');

  std::string errstr = "";
  try
    {
      root.m_root_ownership.parse<0> (&copy[0]);
    }
  catch (const std::runtime_error &e)
    {
      errstr = std::string ("Runtime error was: ") + e.what ();
    }
  catch (const rapidxml::parse_error &e)
    {
      errstr = std::string ("Parse error was: ") + e.what ();
    }
  catch (const std::exception &e)
    {
      errstr = std::string ("Error was: ") + e.what ();
    }
  catch (...)
    {
      errstr = std::string ("Internal error");
    }

  err_t err (errstr);
  if (!err.ok ())
    return err_t (string_printf ("Error encountered while parsing xml: %s\n", errstr.c_str ()));

  root.set_node (&root.m_root_ownership);
  add (root, dst, "data");
  return root.load ();
}

template<typename DataT>
void add (node_t &node, DataT &data, const std::string &name)
{
  rules::add_impl (node, data, name);
}

namespace detail
{
template<typename ElemT, typename ContainerT>
void add_elem (ContainerT &data, std::unique_ptr<ElemT> elem_to_add_impl)
{
  rules::add_elem_impl (data, std::move (elem_to_add_impl));
}
}

}


