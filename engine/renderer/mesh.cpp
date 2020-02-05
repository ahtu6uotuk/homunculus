#include <GL/glew.h>
#include "mesh.h"
#include "engine/logger.h"

mesh_t::mesh_t ()
{
  glGenVertexArrays (1, &m_vao);
  glGenBuffers (1, &m_vbo);
  glGenBuffers (1, &m_ibo);
}

void mesh_t::print_debug_info (logger_t &logger)
{
  do_nothing (&logger);
}

mesh_t::~mesh_t ()
{
  if (glIsBuffer (m_vbo))
    glDeleteBuffers (1, &m_vbo);
  if (glIsBuffer (m_ibo))
    glDeleteBuffers (1, &m_ibo);
}
