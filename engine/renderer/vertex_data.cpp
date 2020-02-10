#include "vertex_data.h"

vertex_data_t::vertex_data_t(glm::vec3 &&vertex, glm::vec3 &&normal, glm::vec2 &&uv):
  m_vertex (vertex), m_normal (normal), m_uv (uv)
{}

vertex_data_t::vertex_data_t (const vertex_data_view_t &vertex_view):
  m_vertex (vertex_view.m_vertex),
  m_normal (vertex_view.m_normal),
  m_uv (vertex_view.m_uv)
{}
