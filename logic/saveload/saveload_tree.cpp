#include "saveload_tree.h"

#include "common/string/string_utils.h"
#include "external/rapidxml/rapidxml_print.hpp"
#include "logic/saveload/saveload.h"

std::string detail::xml_node_to_string (const rapidxml::xml_node<> &node)
{
  std::string s;
  print (std::back_inserter (s), node, 0);
  return s;
}

// saveload_node---------------------------------------------------------------

saveload_node::~saveload_node () {}

saveload_node::saveload_node (doc_t &root_node, const string &name)
  : m_root (root_node), m_name (name)
{
  assert_check (!m_name.empty (), "Object must have a valid name!");
}

err_t saveload_node::load ()
{
  assert_check (m_node, "Node not set when trying to load");
  unordered_map<node_t *, bool> all_loaded;
  for (node_t *node = m_node->first_node (); node; node = node->next_sibling ())
    all_loaded[node] = false;

  for (size_t i = 0; i < m_children.size (); i++)
    {
      node_t *current_node = m_node->first_node (m_children[i]->m_name.c_str ());
      if (!current_node)
        continue;
      all_loaded[current_node] = true;

      m_children[i]->m_node = current_node;
      err_t err = m_children[i]->load ();
      if (!err.ok ())
        return err;
    }

  auto it = find_if (all_loaded.begin (), all_loaded.end (), [] (auto &a) { return !a.second; });
  if (it != all_loaded.end ())
    return string_printf (
        "Encountered unexpected data: \"%s\"", detail::xml_node_to_string (*it->first).c_str ());

  return ERR_OK;
}

err_t saveload_node::save ()
{
  return save_private ();
}

err_t saveload_node::save_private (bool ignore_defaults)
{
  for (size_t i = 0; i < m_children.size (); i++)
    {
      if (ignore_defaults && m_children[i]->is_default ())
        continue;

      m_children[i]->m_node = m_root.allocate_node (
          rapidxml::node_type::node_element, m_children[i]->m_name.c_str ());
      m_node->append_node (m_children[i]->m_node);
      err_t err = m_children[i]->save ();
      if (!err.ok ())
        return err;
    }
  return ERR_OK;
}

void saveload_node::set_node_value (const string &value)
{
  if (value.empty ())
    return;
  char *node_value = m_root.allocate_string (value.c_str ());
  m_node->value (node_value);
}

// saveload_container_node---------------------------------------------------------------



// saveload_root---------------------------------------------------------------

detail::saveload_root::~saveload_root () {}
detail::saveload_root::saveload_root ()
  : saveload_node (m_root_ownership, "doc")
{
}
void detail::saveload_root::set_node (saveload_node::node_t *node)
{
  m_node = node;
}
