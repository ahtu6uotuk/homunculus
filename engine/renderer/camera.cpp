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

camera_t::camera_t (glm::vec3 position):
  m_current_data (position),
  m_mouse_sensitivity (camera_defaults::mouse_sensitivity),
  m_zoom (camera_defaults::zoom)
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
  return glm::
      lookAt (m_current_data.m_position,
              m_current_data.m_position + m_current_data.m_orientation_front,
              camera_defaults::orientation_world_up);
}

camera_t::~camera_t ()
{}
