#pragma once

#include <glm/matrix.hpp>

#include "common/common.h"
#include "datastructs/camera_data_t.h"

///@brief Camera class for renderer
class camera_t
{
  glm::vec3 m_position; ///< Camera position
  camera_data_t m_current_data;
  float m_zoom;
public:
  camera_t () = delete;
  camera_t (const camera_t &) = delete;
  camera_t (camera_t &&) = delete;
  camera_t &operator= (const camera_t &) = delete;
  camera_t &operator= (camera_t &&) = delete;
  camera_t (glm::vec3 position);

  void set_current_data (const camera_data_t &data) { m_current_data = data; }
  void set_position (const glm::vec3 &position) { m_position = position; }

  /// @brief Zoom camera
  void zoom (float zoom);

  /// @brief Get zoom value
  auto get_zoom () const { return m_zoom; }

  /// @brief Compute view matrix
  glm::mat4 get_view_matrix () const;

  ~camera_t ();
};
