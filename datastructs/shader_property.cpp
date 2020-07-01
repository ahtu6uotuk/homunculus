#include "shader_property.h"
#include <GL/glew.h>

unsigned int shader_property_t::get_id () const
{
  return m_id;
}

inline void gl_set_uniform (unsigned int id, float value)
{glUniform1f (id, value);}
inline void gl_set_uniform (unsigned int id, double value)
{glUniform1d (id, value);}
inline void gl_set_uniform (unsigned int id, int value)
{glUniform1i (id, value);}

template<typename T>
void shader_basic_property_t<T>::use ()
{
  gl_set_uniform (m_id, m_value);
}
