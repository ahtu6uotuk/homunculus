#pragma once
#ifndef ANIMATION_T_H
#define ANIMATION_T_H
#include <vector>

/// @brief Base virtual class for animation
class animation_t
{

};


// Not implemented yet
class vertex_animation_t : public animation_t
{};

enum class animation_action_t
{
  TRANSLATION,
  ROTATION,
  SCALE,
  WEIGHTS,
  COUNT
};

enum class animation_interpolation_t
{
  STEP,
  LINEAR,
  CUBIC_SPLINE,
  COUNT
};

// Not implemented yet
class animation_frame_t
{

};

// Not implemented yet
class skeletal_animation_t : public animation_t
{
  std::vector<animation_frame_t> m_frames;
};

#endif // ANIMATION_T_H
