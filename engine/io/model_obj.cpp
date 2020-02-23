#include <fstream>
#include <sstream>
#include <map>
#include "engine/renderer/mesh.h"
#include "engine/logger.h"
#include "model_obj.h"
#include "engine/logger_utils.h"


void model_obj_t::parse_position_3d (stringstream &ss, vector<glm::vec3> &vec_pos)
{
  double x, y, z;
  ss >> x >> y >> z;

  vec_pos.emplace_back (x, y, z);
}

void model_obj_t::parse_vertex_line (stringstream &ss)
{
  return parse_position_3d (ss, m_vertices);
}

void model_obj_t::parse_vertex_texture_coordinate_line (stringstream &ss)
{
  double u, v;
  ss >> u >> v;

  m_uv.emplace_back (u, v);
}

void model_obj_t::parse_vertex_normal_line (stringstream &ss)
{
  return parse_position_3d (ss, m_normals);
}

void model_obj_t::parse_face_line (stringstream &ss)
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

err_t model_obj_t::load (const string &filename)
{
  ifstream ifs;
  ifs.open (filename);
  if (!ifs.is_open ())
    {
      return err_t (string ("Can't open file ").append (filename));
    }
  string line;
  size_t line_number = 1;
  while (getline (ifs, line))
    {
      stringstream ss (line);
      string buffer;
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
          return err_t (string ("failed to load model ").append (filename) + ": line " + to_string (line_number));
        }

      line_number++;
    }

  return ERR_OK;
}

void model_obj_t::print_debug_info (logger_t &logger)
{
  logger_utils::print_var_info (logger, "m_vertices", m_vertices);
  logger_utils::print_var_info (logger, "m_normals", m_normals);
  logger_utils::print_var_info (logger, "m_uv", m_uv);
  logger_utils::print_var_info (logger, "m_vertex_indices", m_vertex_indices);
  logger_utils::print_var_info (logger, "m_normals", m_normals);
  logger_utils::print_var_info (logger, "m_uv_indices", m_uv_indices);
}

mesh_t model_obj_t::to_mesh ()
{
  map<vertex_data_view_t, GLuint> indexation;
  std::vector<vertex_data_t> mesh_vertices;
  std::vector<GLuint> mesh_indices;

  size_t last_vertex_index = 0;
  const size_t vertices_num = m_vertex_indices.size ();
  for (size_t i = 0; i < vertices_num; i++)
    {
      vertex_data_view_t vertex_view = {m_vertices[m_vertex_indices[i]],
                                        m_normals[m_normal_indices[i]],
                                        m_uv[m_uv_indices[i]]};
      auto it = indexation.find (vertex_view);
      if (it != indexation.end ())
        {
          mesh_indices.push_back (it->second);
        }
      else
        {
          mesh_vertices.emplace_back (vertex_view);
          mesh_indices.push_back (last_vertex_index);
          indexation[vertex_view] = last_vertex_index;
          last_vertex_index++;
        }
    }
  return mesh_t (std::move (mesh_vertices), std::move (mesh_indices), std::vector<GLuint> ());
}
