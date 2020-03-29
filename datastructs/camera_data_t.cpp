#include "camera_data_t.h"

#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
#include <glm/geometric.hpp>

#include "datastructs/helpers/saveload_rules_extensions.h"
#include "resource/saveload/saveload.h"

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