#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
#include <glm/geometric.hpp>

// fuck, i guess i have to fix this dependency too
#include "objects/helpers/saveload_rules_extensions.h"
#include "logic/saveload/saveload.h"
#include "camera.h"

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


bool camera_data_t::operator== (const camera_data_t &other) const
{
  return m_position == other.m_position && !fuzzycmp (m_yaw, other.m_yaw)
         && !fuzzycmp (m_pitch, other.m_pitch);
}
void camera_data_t::build_saveload_tree (saveload::node_t &node)
{
  saveload::add (node, m_position, "position");
  saveload::add (node, m_yaw, "yaw");
  saveload::add (node, m_pitch, "pitch");

  saveload::add (node, m_orientation_front, "orientation_front");
  saveload::add (node, m_orientation_up, "orientation_up");
  saveload::add (node, m_orientation_right, "orientation_right");
}

namespace camera_defaults
{
  constexpr float yaw = -90.f;
  constexpr float pitch = 0.f;
  constexpr float zoom = 45.f;
  constexpr float mouse_sensitivity = 0.05f;
  constexpr glm::vec3 orientation_world_up = {0.f, 1.f, 0.f};
}

camera_data_t::camera_data_t (glm::vec3 position):
   m_position (position),
   m_orientation_front (0.f, 0.f, -1.f),
   m_orientation_up (0.f, 1.f, 0.f),
   m_yaw (camera_defaults::yaw),
   m_pitch (camera_defaults::pitch)
{
  compute_orientation_vectors ();
}

void camera_data_t::compute_orientation_vectors ()
{
  m_orientation_front.x = std::cos (glm::radians (m_yaw)) * std::cos (glm::radians (m_pitch));
  m_orientation_front.y = std::sin (glm::radians (m_pitch));
  m_orientation_front.z = std::sin (glm::radians (m_yaw)) * std::cos (glm::radians (m_pitch));
  m_orientation_front = glm::normalize (m_orientation_front);
  m_orientation_right = glm::normalize (glm::cross (m_orientation_front, camera_defaults::orientation_world_up));
  m_orientation_up = glm::normalize (glm::cross (m_orientation_right, m_orientation_front));
}

camera_t::camera_t (glm::vec3 position):
  m_current_data (position),
  m_mouse_sensitivity (camera_defaults::mouse_sensitivity),
  m_zoom (camera_defaults::zoom)
{
}

void camera_data_t::move (movement_direction_t direction, float dt, float speed)
{
  switch (direction)
    {
    case movement_direction_t::FORWARD:
      m_position += m_orientation_front * dt * speed;
      break;
    case movement_direction_t::BACKWARD:
      m_position -= m_orientation_front * dt * speed;
      break;
    case movement_direction_t::LEFT:
      m_position -= m_orientation_right * dt * speed;
      break;
    case movement_direction_t::RIGHT:
      m_position += m_orientation_right * dt * speed;
      break;
    }
}

void camera_data_t::rotate (float d_yaw, float d_pitch)
{
  if (fabs (d_yaw) < 1.e-6f && fabs (d_pitch) < 1.e-6f)
    return;
  d_yaw *= camera_defaults::mouse_sensitivity;
  d_pitch *= camera_defaults::mouse_sensitivity;
  m_yaw += d_yaw;
  m_pitch += d_pitch;
  if (m_pitch > 89.f)
    m_pitch = 89.f;
  if (m_pitch < -89.f)
    m_pitch = -89.f;

  return compute_orientation_vectors ();
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
