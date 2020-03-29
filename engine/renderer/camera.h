#pragma once

#include <glm/matrix.hpp>

#include "common/common.h"
#include "datastructs/camera_data_t.h"

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
