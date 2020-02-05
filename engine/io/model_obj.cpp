#include <fstream>
#include <sstream>
#include "model_obj.h"

err_t model_obj_t::parse_position_3d (stringstream &ss, vector<glm::vec3> &vec_pos)
{
  double x, y, z;
  ss >> x >> y >> z;
  vec_pos.emplace_back (x, y, z);
  return ERR_OK;
}

err_t model_obj_t::parse_vertex_line (stringstream &ss)
{
  return parse_position_3d (ss, m_vertices);
}

err_t model_obj_t::parse_vertex_texture_coordinate_line (stringstream &ss)
{
  double u, v;
  ss >> u >> v;
  m_uv.emplace_back (u, v);

  return ERR_OK;
}

err_t model_obj_t::parse_vertex_normal_line (stringstream &ss)
{
  return parse_position_3d (ss, m_normals);
}

err_t model_obj_t::parse_face_line (stringstream &ss)
{
  unsigned int vertex_index[3], uv_index[3], normal_index[3];
  char delim;
  ss >> vertex_index[0] >> delim >> uv_index[0] >> delim >> normal_index[0];
  ss >> vertex_index[1] >> delim >> uv_index[1] >> delim >> normal_index[1];
  ss >> vertex_index[2] >> delim >> uv_index[2] >> delim >> normal_index[2];
  m_vertex_indices.emplace_back (vertex_index[0], vertex_index[1], vertex_index[2]);
  m_uv_indices.emplace_back (uv_index[0], uv_index[1], uv_index[2]);
  m_normal_indices.emplace_back (normal_index[0], normal_index[1], normal_index[2]);

  return ERR_OK;
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
  while (getline (ifs, line))
    {
      stringstream ss (line);
      string buffer;
      ss >> buffer;
      if (buffer == "v")
        {
          RETURN_IF_FAIL (parse_vertex_line (ss));
        }
      else if (buffer == "vt")
        {
          RETURN_IF_FAIL (parse_vertex_texture_coordinate_line (ss));
        }
      else if (buffer == "vn")
        {
          RETURN_IF_FAIL (parse_vertex_normal_line (ss));
        }
      else if (buffer == "f")
        {
          RETURN_IF_FAIL (parse_face_line (ss));
        }
      else if (buffer == "usemtl")
        {}
      else if (buffer == "mtllib")
        {}
    }

  return ERR_OK;
}
