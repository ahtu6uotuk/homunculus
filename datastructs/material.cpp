#include "material.h"
#include "shader.h"
#include "shader_property.h"

void material_t::use ()
{
  m_shader.use ();
  for (const auto &property : m_properties)
    property->use ();
}
