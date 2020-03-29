#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

struct vertex_data_view_t;

struct vertex_data_t
{
  glm::vec3 m_vertex;
  glm::vec3 m_normal;
  glm::vec2 m_uv;
  vertex_data_t (const vertex_data_view_t &vertex_view);
  ~vertex_data_t () {}
};

struct vertex_data_view_t
{
  const glm::vec3 *m_vertex;
  const glm::vec3 *m_normal;
  const glm::vec2 *m_uv;
  vertex_data_view_t (const glm::vec3 &vertex, const glm::vec3 &normal, const glm::vec2 &uv):
    m_vertex (&vertex), m_normal (&normal), m_uv (&uv)
  {}
  vertex_data_view_t (const vertex_data_t &vertex_data):
    m_vertex (&vertex_data.m_vertex), m_normal (&vertex_data.m_normal), m_uv (&vertex_data.m_uv)
  {}
  bool operator< (const vertex_data_view_t &b) const;
};
