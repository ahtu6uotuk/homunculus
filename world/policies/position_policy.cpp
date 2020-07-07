#include "position_policy.h"
#include "object/interaction.h"


std::string position_policy_t::policy_describe () const
{return string_printf ("position %f %f %f", m_position.x, m_position.y, m_position.z);}

void position_policy_t::policy_build_saveload_tree (saveload::node_t &node)
{
  saveload::add (node, m_position, "position");
}
