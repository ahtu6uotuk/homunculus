#pragma once
#ifndef SCENE_T_H
#define SCENE_T_H
#include <memory>
#include <vector>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
class model_t;


/// @brief Abstract light source class
class light_t
{
public:
  virtual ~light_t () = default;
};

class point_light_t : public light_t
{
  glm::vec3 m_position;
  glm::vec4 m_color;
public:
  point_light_t (glm::vec3 position, glm::vec4 color): m_position (position), m_color (color) {}
  const auto &get_position () const { return m_position; }
  const auto &get_color () const {  return m_color; }
};

/// @brief Class to store all entities for current scene rendering
class scene_t
{
  std::vector<model_t *> m_models;
  std::vector<light_t> m_light_sources;
public:
  scene_t ();
  void render ();
};

#endif // SCENE_T_H
