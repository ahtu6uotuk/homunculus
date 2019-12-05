#include "saveload_tree.h"
#include "common/string_utils.h"
#include "external/rapidxml_helpers/rapidxml_wrapper.h"

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
  node_t *current_node = m_node->first_node ();
  for (size_t i = 0; i < m_children.size (); i++)
    {
      if (!current_node)
        return err_t (string_printf ("Given xml node \"%s\" does not have enough elements",
                                     xml_node_to_string (*m_node).c_str ()));

      m_children[i]->m_node = current_node;
      err_t err = m_children[i]->load ();
      if (!err.ok ())
        return err;

      current_node = current_node->next_sibling ();
    }

  return ERR_OK;
}

err_t saveload_node::save ()
{
  for (size_t i = 0; i < m_children.size (); i++)
    {
      m_children[i]->m_node = m_root.allocate_node (rapidxml::node_type::node_element, m_children[i]->m_name.c_str ());
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

// saveload_root---------------------------------------------------------------

detail::saveload_root::~saveload_root () {}
detail::saveload_root::saveload_root () : saveload_node (m_root_ownership, "doc") {}

detail::save_root::~save_root () {}
string detail::save_root::print () { return xml_node_to_string (m_root_ownership); }
detail::load_root::~load_root () {}
detail::save_root::save_root () : saveload_root ()
{
  m_node = m_root_ownership.allocate_node (rapidxml::node_type::node_element, "root");
  m_root_ownership.append_node (m_node);
}

detail::load_root::load_root (const string &xml_to_parse)
  : saveload_root ()
{
  vector<char> copy (xml_to_parse.begin (), xml_to_parse.end ());
  copy.push_back ('\0');
  m_root_ownership.parse<0> (&copy[0]);
  m_node = m_root_ownership.first_node ();
}
