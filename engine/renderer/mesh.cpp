#include <GL/glew.h>
#include "mesh.h"
#include "engine/logger.h"

void mesh_t::init_gl ()
{
  glGenVertexArrays (1, &m_vao);
  glGenBuffers (1, &m_vbo);
  glGenBuffers (1, &m_ibo);
  glBindVertexArray (m_vao);
  glBindBuffer (GL_ARRAY_BUFFER, m_vbo);
  glBufferData (GL_ARRAY_BUFFER, m_vertices.size () * sizeof (vertex_data_t), m_vertices.data (), GL_STATIC_DRAW);
  glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, m_ibo);
  glBufferData (GL_ELEMENT_ARRAY_BUFFER, m_indices.size () * sizeof (GLuint), m_indices.data (), GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof (vertex_data_t), (void*)0);
  // vertex normals
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof (vertex_data_t), (void*)offsetof (vertex_data_t, m_normal));
  // vertex texture coords
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof (vertex_data_t), (void*)offsetof (vertex_data_t, m_uv));

  glBindVertexArray(0);
}

mesh_t::mesh_t ():
  m_vao (0),
  m_vbo (0),
  m_ibo (0),
  m_vertices (),
  m_indices (),
  m_textures ()
{}

mesh_t::mesh_t (vector<vertex_data_t> &&vertices, vector<GLuint> &&indeces, vector<GLuint> &&textures):
  m_vertices (std::move (vertices)),
  m_indices (std::move (indeces)),
  m_textures (std::move (textures))
{
  init_gl ();
}

mesh_t::mesh_t (mesh_t &&b):
  m_vao (std::move (b.m_vao)),
  m_vbo (std::move (b.m_vbo)),
  m_ibo (std::move (b.m_ibo)),
  m_vertices (std::move (b.m_vertices)),
  m_indices(std::move (b.m_indices)),
  m_textures (std::move (b.m_textures))
{
  b.m_vao = 0;
  b.m_vbo = 0;
  b.m_ibo = 0;
}

mesh_t &mesh_t::operator= (mesh_t &&b)
{
  m_vao = b.m_vao;
  m_vbo = b.m_vbo;
  m_ibo = b.m_ibo;
  m_vertices = std::move (b.m_vertices);
  m_indices = std::move (b.m_indices);
  m_textures = std::move (b.m_textures);
  return *this;
}

err_t mesh_t::load ()
{
  return ERR_OK;
}

void mesh_t::draw ()
{
  glBindVertexArray (m_vao);
  glEnableVertexAttribArray (0);
  glEnableVertexAttribArray (1);
  glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, m_ibo);
  glDrawElements (GL_TRIANGLES, m_indices.size (), GL_UNSIGNED_INT, m_indices.data ());
  glDisableVertexAttribArray (0);
  glDisableVertexAttribArray (1);
}

void mesh_t::print_debug_info (logger_t &logger)
{
  do_nothing (&logger);
}

mesh_t::~mesh_t ()
{
  if (glIsVertexArray (m_vao))
    glDeleteVertexArrays (1, &m_vao);
  if (glIsBuffer (m_vbo))
    glDeleteBuffers (1, &m_vbo);
  if (glIsBuffer (m_ibo))
    glDeleteBuffers (1, &m_ibo);
}
