#include "camera.h"

#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
#include <glm/geometric.hpp>

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
  if (m_zoom >= 1.0f && m_zoom <= 45.0f)
      m_zoom -= d_zoom;
  if (m_zoom <= 1.0f)
      m_zoom = 1.0f;
  if (m_zoom >= 45.0f)
    m_zoom = 45.0f;
}

glm::mat4 camera_t::get_view_matrix () const
{
  return glm::lookAt (m_position, m_position + m_current_data.m_orientation_front, glm::vec3 (0.f, 1.f, 0.f));
}

camera_t::~camera_t ()
{}
