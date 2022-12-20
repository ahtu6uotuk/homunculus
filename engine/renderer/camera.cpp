#include "camera.h"

#include <algorithm>
#include <cmath>
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>

///
///         y
///         |
///         |
///         |
///         |
///         0 ----------- z
///        /
///       /
///      /
///     x
///

camera_t::camera_t (glm::vec3 position)
  : m_position (position), m_current_data (), m_zoom (camera_defaults::zoom)
{
}

void camera_t::zoom (float d_zoom)
{
  m_zoom = std::clamp (m_zoom + d_zoom, 1.f, 90.f);
}

glm::mat4 camera_t::get_view_matrix () const
{
  return glm::lookAt (m_position, m_position + m_current_data.m_orientation_front, glm::vec3 (0.f, 1.f, 0.f));
}

camera_t::~camera_t ()
{}
