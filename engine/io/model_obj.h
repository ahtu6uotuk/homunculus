#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>

#include "common/err_t.h"

class mesh_t;

/// @brief Class to import .obj model format
/// @details
/// .obj model format can be used for static not-animated meshes
class model_obj_t
{
  std::vector<glm::vec3> m_vertices;
  std::vector<glm::vec3> m_normals;
  std::vector<glm::vec2> m_uv;
  std::vector<unsigned int> m_vertex_indices;
  std::vector<unsigned int> m_uv_indices;
  std::vector<unsigned int> m_normal_indices;
private:
  void parse_position_3d (std::stringstream &ss, std::vector<glm::vec3> &vec);
  void parse_vertex_line (std::stringstream &ss);
  void parse_vertex_texture_coordinate_line (std::stringstream &ss);
  void parse_vertex_normal_line (std::stringstream &ss);
  void parse_face_line (std::stringstream &ss);

public:
  model_obj_t () = default;
  model_obj_t (const std::string &file_contents);
  err_t load (const std::string &file_contents);
  void print_debug_info ();
  mesh_t to_mesh ();
};
