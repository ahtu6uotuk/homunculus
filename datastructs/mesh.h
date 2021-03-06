#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <vector>
#include <string>

#include "datastructs/vertex_data.h"
class err_t;

class mesh_t
{
  GLuint m_vao; ///< vertex array object
  GLuint m_vbo; ///< vertext buffer object
  GLuint m_ibo; ///< index buffer object
  std::vector<vertex_data_t> m_vertices;
  std::vector<GLuint> m_indices;
private:
  void init_gl ();
  void reset_gl_objects ();
public:
  err_t load_custom (const std::string &asset_name);
  mesh_t ();
  mesh_t (std::vector<vertex_data_t> &&vertices, std::vector<GLuint> &&indeces);
  mesh_t (mesh_t &&b);
  mesh_t (const mesh_t &) = delete;
  mesh_t &operator= (mesh_t &&b);
  mesh_t &operator= (const mesh_t &) = delete;
  void draw ();
  void print_debug_info ();
  ~mesh_t ();
};
