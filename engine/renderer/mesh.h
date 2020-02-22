#ifndef MESH_H
#define MESH_H
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
  vector<vertex_data_t> m_vertices;
  vector<GLuint> m_indices;
  vector<GLuint> m_textures;
private:
  void init_gl ();
public:
  mesh_t ();
  mesh_t (vector<vertex_data_t> &&vertices, vector<GLuint> &&indeces, vector<GLuint> &&textures);
  mesh_t (mesh_t &&b);
  mesh_t (const mesh_t &) = delete;
  mesh_t &operator= (mesh_t &&b);
  err_t load ();
  void draw ();
  void print_debug_info (logger_t &logger);
  ~mesh_t ();
};

#endif // MESH_H
