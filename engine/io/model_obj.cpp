#include <fstream>
#include <sstream>
#include <map>
#include "engine/renderer/mesh.h"
#include "engine/logger.h"
#include "model_obj.h"
#include "engine/logger_utils.h"


void model_obj_t::parse_position_3d (std::stringstream &ss, std::vector<glm::vec3> &vec_pos)
{
  double x, y, z;
  ss >> x >> y >> z;

  vec_pos.emplace_back (x, y, z);
}

void model_obj_t::parse_vertex_line (std::stringstream &ss)
{
  return parse_position_3d (ss, m_vertices);
}

void model_obj_t::parse_vertex_texture_coordinate_line (std::stringstream &ss)
{
  double u, v;
  ss >> u >> v;

  m_uv.emplace_back (u, v);
}

void model_obj_t::parse_vertex_normal_line (std::stringstream &ss)
{
  return parse_position_3d (ss, m_normals);
}

void model_obj_t::parse_face_line (std::stringstream &ss)
{
  unsigned int vertex_index[3] = {0};
  unsigned int uv_index[3] = {0};
  unsigned int normal_index[3] = {0};
  char delim;
  ss >> vertex_index[0] >> delim >> uv_index[0] >> delim >> normal_index[0];
  ss >> vertex_index[1] >> delim >> uv_index[1] >> delim >> normal_index[1];
  ss >> vertex_index[2] >> delim >> uv_index[2] >> delim >> normal_index[2];

  for (unsigned i = 0; i < 3; i++)
    {
      m_vertex_indices.push_back (vertex_index[i]);
      m_uv_indices.push_back (uv_index[i]);
      m_normal_indices.push_back (normal_index[i]);
    }
}

err_t model_obj_t::load (const std::string &filename)
{
  std::ifstream ifs;
  ifs.open (filename);
  if (!ifs.is_open ())
    {
      return err_t (std::string ("Can't open file ").append (filename));
    }
  std::string line;
  size_t line_number = 1;
  while (getline (ifs, line))
    {
      std::stringstream ss (line);
      std::string buffer;
      ss >> buffer;

      if (buffer == "v")
        {
          parse_vertex_line (ss);
        }
      else if (buffer == "vt")
        {
          parse_vertex_texture_coordinate_line (ss);
        }
      else if (buffer == "vn")
        {
          parse_vertex_normal_line (ss);
        }
      else if (buffer == "f")
        {
          parse_face_line (ss);
        }
      else if (buffer == "usemtl")
        {}
      else if (buffer == "mtllib")
        {}

      if (ss.fail ())
        {
          return err_t (std::string ("failed to load model ").append (filename) + ": line " + std::to_string (line_number));
        }

      line_number++;
    }

  return ERR_OK;
}

void model_obj_t::print_debug_info (logger_t &logger)
{
  logger.print (log_section_t::RESOURCE_MANAGER, log_priority_t::INFO, "IMPORT OBJ MODEL:");
  logger_utils::print_var_info (logger, "m_vertices", m_vertices);
  logger_utils::print_var_info (logger, "m_normals", m_normals);
  logger_utils::print_var_info (logger, "m_uv", m_uv);
  logger_utils::print_var_info (logger, "m_vertex_indices", m_vertex_indices);
  logger_utils::print_var_info (logger, "m_normal_indices", m_normal_indices);
  logger_utils::print_var_info (logger, "m_uv_indices", m_uv_indices);
}

mesh_t model_obj_t::to_mesh (logger_t &)
{
  std::map<vertex_data_view_t, unsigned int> indexation;
  std::vector<vertex_data_t> out_vertices = {};
  std::vector<unsigned int> out_indices = {};
  unsigned int last_index = 0;
  const auto vertices_len = m_vertex_indices.size ();
  for (size_t i = 0; i < vertices_len; i++)
    {
      vertex_data_view_t pack = {m_vertices[m_vertex_indices[i] - 1],
                                 m_normals[m_normal_indices[i] - 1],
                                 m_uv[m_uv_indices[i] - 1]};
      auto it = indexation.find (pack);
      if (it != indexation.end ())
        {
          out_indices.push_back (it->second);
        }
      else
        {
          indexation[pack] = last_index;
          out_vertices.push_back (vertex_data_t (pack));
          out_indices.push_back (last_index);
          last_index++;
        }
    }

  return mesh_t (std::move (out_vertices), std::move (out_indices), {});
}
