#pragma once
#include "logic/saveload/saveload_tree.h"
#include <glm/vec3.hpp>

namespace saveload
{
namespace rules
{

/// glvec3
void add_impl (node_t &node, glm::vec3 &data, const std::string &name)
{
  node.spawn_empty_child (name);
  add (node.last_child (), data.x, "x");
  add (node.last_child (), data.y, "y");
  add (node.last_child (), data.z, "z");
}

}  // namespace rules
}  // namespace saveload

