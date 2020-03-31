#include "mesh.h"

#include <memory>

#include "common/logger/logger.h"
#include "common/logger/logger_utils.h"
#include "datastructs/io/model_obj.h"

err_t mesh_t::load_custom (const std::string &file_content)
{
  model_obj_t obj_importer;

  RETURN_IF_FAIL (obj_importer.load (file_content));
  obj_importer.print_debug_info ();

  *this = obj_importer.to_mesh ();
  return ERR_OK;
}

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
//  glEnableVertexAttribArray(1);
//  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof (vertex_data_t), (void*)offsetof (vertex_data_t, m_normal));
  // vertex texture coords
  glEnableVertexAttribArray(1);
  glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, sizeof (vertex_data_t), (void*)offsetof (vertex_data_t, m_uv));

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

mesh_t::mesh_t (std::vector<vertex_data_t> &&vertices, std::vector<GLuint> &&indeces, std::vector<GLuint> &&textures):
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
  b.reset_gl_objects ();
  return *this;
}

void mesh_t::draw ()
{
  glBindBuffer (GL_ARRAY_BUFFER, m_vbo);
  glBufferData (GL_ARRAY_BUFFER, m_vertices.size () * sizeof (vertex_data_t), m_vertices.data (), GL_STATIC_DRAW);
  glBindVertexArray (m_vao);
  glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof (GLfloat), reinterpret_cast<void *> (0));
  glEnableVertexAttribArray (0);
  glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof (GLfloat), reinterpret_cast<void *> (6 * sizeof (GLfloat)));
  glEnableVertexAttribArray (1);
  glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, m_ibo);
  glBufferData (GL_ELEMENT_ARRAY_BUFFER, m_indices.size () * sizeof (GLuint), m_indices.data (), GL_STATIC_DRAW);
  glDrawElements (GL_TRIANGLES, m_indices.size (), GL_UNSIGNED_INT, nullptr);
//  glBindBuffer (GL_ARRAY_BUFFER, 0);
//  glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray (0);
}

void mesh_t::print_debug_info ()
{
  logger_utils::print_var_info ("m_vao", m_vao);
  logger_utils::print_var_info ("m_vbo", m_vbo);
  logger_utils::print_var_info ("m_ibo", m_ibo);
  logger_utils::print_var_info ("m_vertices.size ()", m_vertices.size ());
  logger_utils::print_var_info ("m_vertices", m_vertices);
  logger_utils::print_var_info ("m_indices.size ()", m_indices.size ());
  logger_utils::print_var_info ("m_indices", m_indices);
  logger_utils::print_var_info ("m_textures.size ()", m_textures.size ());
  logger_utils::print_var_info ("m_textures", m_textures);
}

void mesh_t::reset_gl_objects ()
{
  m_vao = 0;
  m_vbo = 0;
  m_ibo = 0;
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
