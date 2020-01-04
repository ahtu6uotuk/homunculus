#pragma once

#include "logic/saveload_tree.h"

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
    dst = detail::xml_node_to_string (*root.m_root_ownership.first_node ()->first_node ());

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

  root.set_node (&root.m_root_ownership);
  root.add (dst, "data");
  return root.load ();
}
