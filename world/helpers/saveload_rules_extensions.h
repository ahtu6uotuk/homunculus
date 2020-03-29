#pragma once
#include <glm/vec3.hpp>

#include "resource/saveload/saveload_tree.h"

namespace saveload
{
namespace rules
{

/// glvec3
inline void add_impl (node_t &node, glm::vec3 &data, const std::string &name)
{
  node.spawn_empty_child (name);
  add (node.last_child (), data.x, "x");
  add (node.last_child (), data.y, "y");
  add (node.last_child (), data.z, "z");
}

}  // namespace rules
}  // namespace saveload

