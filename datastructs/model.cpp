#include "model.h"
#include "mesh.h"
#include "texture.h"
#include "shader.h"
//#include "material.h"
//#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>


model_t::model_t (const glm::vec3 &position, shader_t *shader, mesh_t *mesh, texture_t *tex):
  m_pos (position), m_shader (shader), m_mesh (mesh), m_tex (tex)
{
}

model_t::model_t (const model_t &b):
  m_pos (b.m_pos), m_shader (b.m_shader), m_mesh (b.m_mesh), m_tex (b.m_tex)
{}

void model_t::render (const glm::mat4 &mvp)
{
  m_shader->use ();
  m_shader->set_uniform_mat4 ("MVP", glm::value_ptr (mvp));
  glActiveTexture (GL_TEXTURE0);
  glBindTexture (GL_TEXTURE_2D, m_tex->m_texture_id);
  m_shader->set_uniform_1i ("myTextureSampler", 0);
  m_shader->set_uniform_3f ("offset", glm::value_ptr (m_pos));
  m_mesh->draw ();
//  printf ("%f %f %f\n", m_pos.x, m_pos.y, m_pos.z);
//  for (auto &pair : m_parts)
//    {
//      pair.first->use ();
//      pair.second->draw ();
//    }
}

model_t::~model_t ()
{
//  if (glIsVertexArray (m_vao))
//    glDeleteVertexArrays (1, &m_vao);
//  if (glIsBuffer (m_vbo))
//    glDeleteBuffers (1, &m_vbo);
}
