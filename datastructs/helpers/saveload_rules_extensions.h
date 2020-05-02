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
  fill_node_func_t<glm::vec3> fill_func = [] (node_t &inode, glm::vec3 &idata) {
    add (inode, idata.x, "x");
    add (inode, idata.y, "y");
    add (inode, idata.z, "z");
  };

  node.add_external_complex_structure (data, name, fill_func);
}

}  // namespace rules
}  // namespace saveload

