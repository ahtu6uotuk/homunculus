#ifndef CAMERA_H
#define CAMERA_H
#pragma once
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>

enum class movement_direction_t
{
  FORWARD = 0,
  BACKWARD,
  RIGHT,
  LEFT
};

///@brief Camera class for renderer
class camera_t
{
  glm::vec3 m_position;
  glm::vec3 m_orientation_front;
  glm::vec3 m_orientation_up;
  glm::vec3 m_orientation_right;
  const glm::vec3 m_orientation_world_up; ///< world up orientation vector
  float m_yaw; ///< yaw euler angle
  float m_pitch; ///< pitch euler angle
  float m_movement_speed;
  float m_mouse_sensitivity;
  float m_zoom;
private:
  /// @brief Compute camera front, up and right vectors
  void compute_orientation_vectors ();
public:
  camera_t () = delete;
  camera_t (const camera_t &) = delete;
  camera_t (camera_t &&) = delete;
  camera_t &operator= (const camera_t &) = delete;
  camera_t &operator= (camera_t &&) = delete;
  camera_t (const glm::vec3 &position);
  /// @brief Move camera in direction during time dt
  void move (movement_direction_t direction, float dt);
  /// @brief Rotate camera
  void rotate (float d_yaw, float d_pitch);
  /// @brief Zoom camera
  void zoom (float zoom);
  /// @brief Compute view matrix
  glm::mat4 get_view_matrix () const;

  ~camera_t ();
};

#endif // CAMERA_H
