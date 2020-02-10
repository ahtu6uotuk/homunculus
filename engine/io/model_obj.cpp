#include <fstream>
#include <sstream>
#include <map>
#include "engine/renderer/mesh.h"
#include "model_obj.h"


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
  unsigned int vertex_index[3], uv_index[3], normal_index[3];
  char delim;
  ss >> vertex_index[0] >> delim >> uv_index[0] >> delim >> normal_index[0];
  ss >> vertex_index[1] >> delim >> uv_index[1] >> delim >> normal_index[1];
  ss >> vertex_index[2] >> delim >> uv_index[2] >> delim >> normal_index[2];

  m_vertex_indices.emplace_back (vertex_index[0], vertex_index[1], vertex_index[2]);
  m_uv_indices.emplace_back (uv_index[0], uv_index[1], uv_index[2]);
  m_normal_indices.emplace_back (normal_index[0], normal_index[1], normal_index[2]);
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
          err_t (string ("failed to load model ").append (filename) + ": line " + to_string (line_number));
        }

      line_number++;
    }

  return ERR_OK;
}

mesh_t model_obj_t::to_mesh ()
{
  map<vertex_data_view_t, GLuint> indexation;
  const auto vertices_num = m_vertices.size ();
  std::vector<vertex_data_t> vertices;
  std::vector<GLuint> indeces;
  size_t last_vertex_index = 0;
  for (size_t i = 0; i < vertices_num; i++)
    {
      vertex_data_view_t vertex_view = {m_vertices[i], m_normals[i], m_uv[i]};
      auto it = indexation.find (vertex_view);
      if (it != indexation.end ())
        {
          indeces.push_back (it->second);
        }
      else
        {
          vertices.emplace_back (vertex_view);
          indexation[vertex_view] = last_vertex_index;
          last_vertex_index++;
        }
    }
  return mesh_t (std::move (vertices), std::move (indeces), std::vector<GLuint> ());
}
