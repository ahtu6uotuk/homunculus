#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
#include <glm/geometric.hpp>
#include "camera.h"

namespace camera_defaults
{
  constexpr float yaw = -90.f;
  constexpr float pitch = 0.f;
  constexpr float speed = 2.5f;
  constexpr float zoom = 45.f;
}

void camera_t::compute_orientation_vectors ()
{
  m_orientation_front.x = std::cos (glm::radians (m_yaw)) * std::cos (glm::radians (m_pitch));
  m_orientation_front.y = std::sin (glm::radians (m_yaw));
  m_orientation_front.z = std::sin (glm::radians (m_yaw)) * std::cos (glm::radians (m_pitch));
  m_orientation_front = glm::normalize (m_orientation_front);
  m_orientation_right = glm::cross (m_orientation_front, m_orientation_world_up);
  m_orientation_up = glm::cross (m_orientation_right, m_orientation_front);
}

camera_t::camera_t (const glm::vec3 &position):
  m_position (position),
  m_orientation_up (0.f, 1.f, 0.f),
  m_orientation_world_up (m_orientation_up),
  m_yaw (camera_defaults::yaw),
  m_pitch (camera_defaults::pitch),
  m_movement_speed (camera_defaults::speed),
  m_zoom (camera_defaults::zoom)
{
  compute_orientation_vectors ();
}

void camera_t::move (movement_direction_t direction, float dt)
{
  switch (direction)
    {
    case movement_direction_t::FORWARD:
      m_position += m_orientation_front * dt * m_movement_speed;
      break;
    case movement_direction_t::BACKWARD:
      m_position -= m_orientation_front * dt * m_movement_speed;
      break;
    case movement_direction_t::LEFT:
      m_position -= m_orientation_right * dt * m_movement_speed;
      break;
    case movement_direction_t::RIGHT:
      m_position += m_orientation_right * dt * m_movement_speed;
      break;
    }
}

void camera_t::rotate (float d_yaw, float d_pitch)
{
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
  return glm::lookAt (m_position, m_position + m_orientation_front, m_orientation_up);
}

camera_t::~camera_t ()
{}
