#include <GL/glew.h>
#include "mesh.h"
#include "engine/logger.h"

mesh_t::mesh_t ():
  m_vao (0),
  m_vbo (0),
  m_ibo (0),
  m_vertices (),
  m_indeces (),
  m_textures ()
{}

mesh_t::mesh_t (mesh_t &&b):
  m_vao (std::move (b.m_vao)),
  m_vbo (std::move (b.m_vbo)),
  m_ibo (std::move (b.m_ibo)),
  m_vertices (std::move (b.m_vertices)),
  m_indeces(std::move (b.m_indeces)),
  m_textures (std::move (b.m_textures))
{
  b.m_vao = 0;
  b.m_vbo = 0;
  b.m_ibo = 0;
}

err_t mesh_t::load()
{
  glGenVertexArrays (1, &m_vao);
  glGenBuffers (1, &m_vbo);
  glGenBuffers (1, &m_ibo);
  return ERR_OK;
}

void mesh_t::draw ()
{
  glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, m_ibo);
  glDrawElements (GL_TRIANGLES, m_indeces.size (), GL_UNSIGNED_INT, m_indeces.data ());
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
