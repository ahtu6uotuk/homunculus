#pragma once
#ifndef MODEL_H
#define MODEL_H
#include <map>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class material_t;
class mesh_t;
class shader_t;
class texture_t;


class model_t
{
  glm::vec3 m_pos;
  shader_t *m_shader;
  mesh_t *m_mesh;
  texture_t *m_tex;
public:
  model_t (const glm::vec3 &position, shader_t *shader, mesh_t *mesh, texture_t *tex);
  model_t (model_t &&) = delete;
  model_t (const model_t &b);
  bool is_valid () const {return m_shader && m_mesh && m_tex;}
  void render (const glm::mat4 &mvp);
  ~model_t ();
};

#endif // MODEL_H
