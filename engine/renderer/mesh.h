#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <vector>

#include "common/err_t.h"
#include "engine/renderer/vertex_data.h"

class logger_t;

class mesh_t
{
  GLuint m_vao; ///< vertex array object
  GLuint m_vbo; ///< vertext buffer object
  GLuint m_ibo; ///< index buffer object
  std::vector<vertex_data_t> m_vertices;
  std::vector<GLuint> m_indices;
  std::vector<GLuint> m_textures;
private:
  void init_gl ();
public:
  mesh_t ();
  mesh_t (std::vector<vertex_data_t> &&vertices, std::vector<GLuint> &&indeces, std::vector<GLuint> &&textures);
  mesh_t (mesh_t &&b);
  mesh_t (const mesh_t &) = delete;
  mesh_t &operator= (mesh_t &&b);
  mesh_t &operator= (const mesh_t &) = delete;
  err_t load ();
  void draw ();
  void print_debug_info (logger_t &logger);
  ~mesh_t ();
};
