#pragma once

#include <glm/vec3.hpp>

#include "resource/saveload/saveload_fwd.h"

enum class movement_direction_t
{
  FORWARD = 0,
  BACKWARD,
  RIGHT,
  LEFT
};

namespace camera_defaults
{
constexpr float yaw = -90.f;
constexpr float pitch = 0.f;
constexpr float zoom = 45.f;
constexpr float mouse_sensitivity = 0.05f;
}

struct camera_data_t
{
  camera_data_t ();

  bool operator == (const camera_data_t &other) const;
  void build_saveload_tree (saveload::node_t &node);

  void rotate (float d_yaw, float d_pitch);
  void compute_orientation_vectors ();

  glm::vec3 m_orientation_front;
  glm::vec3 m_orientation_up;
  glm::vec3 m_orientation_right;
  float m_yaw; ///< yaw euler angle
  float m_pitch; ///< pitch euler angle
};
