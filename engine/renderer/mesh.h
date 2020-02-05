#ifndef MESH_H
#define MESH_H
#include <GL/gl.h>
#include "common/err_t.h"
#include <vector>
class logger_t;

class mesh_t
{
  GLuint m_vao; ///< vertex array object
  GLuint m_vbo; ///< vertext buffer object
  GLuint m_ibo; ///< index buffer object
  vector<double> m_vertices;
  vector<GLuint> m_indeces;
  vector<GLuint> m_textures;
public:
  mesh_t ();
  mesh_t (mesh_t &&b);
  mesh_t (const mesh_t &) = delete;
  err_t load ();
  void draw ();
  void print_debug_info (logger_t &logger);
  ~mesh_t ();
};

#endif // MESH_H
