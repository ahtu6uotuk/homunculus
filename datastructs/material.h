#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H
#include <vector>
#include <memory>
#include "datastructs/shader_fwd.h"

class shader_property_t;

/// @brief
/// Material is just shader with specified properties
/// (textures, parameters, etc.)
class material_t
{
  const shader_t &m_shader;
  std::vector<std::unique_ptr<shader_property_t>> m_properties;
public:
  material_t () = delete;
  material_t (const shader_t &shader);
  void set_property (std::unique_ptr<shader_property_t> property);
  const shader_property_t &get_property () const;
  void use ();
  ~material_t ();
};

#endif // MATERIAL_H
