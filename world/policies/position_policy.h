#pragma once
#include <glm/vec3.hpp>
#include "object/interaction.h"
#include "object/object_base.h"
#include "datastructs/helpers/saveload_rules_extensions.h"
#include "resource/saveload/saveload.h"


// !temporary solution!
class position_policy_t : virtual public object_base
{
  glm::vec3 m_position;
public:
  bool operator== (const position_policy_t &other) const {return other.m_position == m_position;}
  glm::vec3 &get_position () { return m_position; }
  const glm::vec3 &get_position () const { return m_position; }
  std::string policy_describe () const;
  void policy_build_saveload_tree (saveload::node_t &node);
  std::vector<interaction> policy_get_interactions () { return {}; }
};
