#include "saveload_tree.h"

#include "common/string/string_utils.h"
#include "external/rapidxml/rapidxml_print.hpp"

std::string saveload::detail::xml_node_to_string (const rapidxml::xml_node<> &node)
{
  std::string s;
  print (std::back_inserter (s), node, 0);
  return s;
}

// saveload_node---------------------------------------------------------------

saveload::node_t::~node_t () {}

saveload::node_t::node_t (xml_doc_t &root_node, const std::string &name)
  : m_name (name), m_root (root_node)
{
  assert_check (!m_name.empty (), "Object must have a valid name!");
}

err_t saveload::node_t::load ()
{
  assert_check (m_node, "Node not set when trying to load");
  std::unordered_map<xml_node_t *, bool> all_loaded;
  for (xml_node_t *node = m_node->first_node (); node; node = node->next_sibling ())
    all_loaded[node] = false;

  for (size_t i = 0; i < m_children.size (); i++)
    {
      xml_node_t *current_node = m_node->first_node (m_children[i]->m_name.c_str ());
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

err_t saveload::node_t::save ()
{
  return save_private ();
}

err_t saveload::node_t::save_private (bool ignore_defaults)
{
  std::unique_ptr<node_t> default_self;
  if (ignore_defaults)
    default_self = m_default_holder->make_node ();

  for (size_t i = 0; i < m_children.size (); i++)
    {
      if (ignore_defaults && m_children[i] == default_self->m_children[i])
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

void saveload::node_t::set_node_value (const std::string &value)
{
  if (value.empty ())
    return;
  char *node_value = m_root.allocate_string (value.c_str ());
  m_node->value (node_value);
}

bool saveload::node_t::operator == (const node_t &other) const
{
  return m_children == other.m_children;
}

saveload::node_t &saveload::node_t::last_child () { return *m_children.back (); }


// container_node_t---------------------------------------------------------------



// saveload_root---------------------------------------------------------------

saveload::detail::root_node_t::~root_node_t () {}
saveload::detail::root_node_t::root_node_t ()
  : node_t (m_root_ownership, "doc")
{
}
void saveload::detail::root_node_t::set_node (xml_node_t *node)
{
  m_node = node;
}
