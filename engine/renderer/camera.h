#ifndef CAMERA_H
#define CAMERA_H
#pragma once
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>
#include "common/common.h"
#include "logic/saveload/saveload_fwd.h"

enum class movement_direction_t
{
  FORWARD = 0,
  BACKWARD,
  RIGHT,
  LEFT
};

struct camera_data_t
{
  camera_data_t (glm::vec3 position);
  camera_data_t () {};

  bool operator == (const camera_data_t &other) const;
  void build_saveload_tree (saveload::node_t &node);

  void move (movement_direction_t direction, float dt, float speed);
  void rotate (float d_yaw, float d_pitch);
  void compute_orientation_vectors ();

  glm::vec3 m_position;
  glm::vec3 m_orientation_front;
  glm::vec3 m_orientation_up;
  glm::vec3 m_orientation_right;
  float m_yaw; ///< yaw euler angle
  float m_pitch; ///< pitch euler angle
};

///@brief Camera class for renderer
class camera_t
{
  camera_data_t m_current_data;
  float m_mouse_sensitivity;
  float m_zoom;
public:
  camera_t () = delete;
  camera_t (const camera_t &) = delete;
  camera_t (camera_t &&) = delete;
  camera_t &operator= (const camera_t &) = delete;
  camera_t &operator= (camera_t &&) = delete;
  camera_t (glm::vec3 position);

  void set_current_data (const camera_data_t &data) { m_current_data = data; }

  /// @brief Zoom camera
  void zoom (float zoom);
  /// @brief Compute view matrix
  glm::mat4 get_view_matrix () const;

  ~camera_t ();
};

#endif // CAMERA_H
