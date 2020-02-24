#include "vertex_data.h"
#include <cstring>


vertex_data_t::vertex_data_t (const vertex_data_view_t &vertex_view):
  m_vertex (*vertex_view.m_vertex),
  m_normal (*vertex_view.m_normal),
  m_uv (*vertex_view.m_uv)
{}

bool vertex_data_view_t::operator< (const vertex_data_view_t &b) const
{
  return std::memcmp (this, &b, sizeof (vertex_data_view_t)) > 0;
}
