#include <GL/glew.h>
#include "shader.h"


shader_t::shader_t (GLuint m_vertex_id, GLuint m_fragment_id)
{
  m_id = glCreateProgram ();
  glAttachShader (m_id, m_vertex_id);
  glAttachShader (m_id, m_fragment_id);
  glLinkProgram (m_id);
}

void shader_t::use () const
{
  glUseProgram (m_id);
}

void shader_t::set_uniform_1i (const std::string &var_name, const int value) const
{
  glUniform1i (glGetUniformLocation (m_id, var_name.c_str ()), value);
}

void shader_t::set_uniform_1f (const std::string &var_name, const float value) const
{
  glUniform1f (glGetUniformLocation (m_id, var_name.c_str ()), value);
}

void shader_t::set_uniform_1d (const std::string &var_name, const double value) const
{
  glUniform1d (glGetUniformLocation (m_id, var_name.c_str ()), value);
}

void shader_t::set_uniform_3f (const std::string &var_name, const float v1, const float v2, const float v3) const
{
  glUniform3f (glGetUniformLocation (m_id, var_name.c_str ()), v1, v2, v3);
}

void shader_t::set_uniform_3f (const std::string &var_name, const float *vec3) const
{
  return set_uniform_3f (var_name.c_str (), vec3[0], vec3[1], vec3[2]);
}

void shader_t::set_uniform_mat4 (const std::string &var_name, const float *mat4, const bool is_transpose) const
{
  glUniformMatrix4fv (glGetUniformLocation (m_id, var_name.c_str ()), 1, is_transpose, mat4);
}

err_t shader_t::check ()
{
  GLint status = 0;
  glGetProgramiv (m_id, GL_LINK_STATUS, &status);
  if (!status)
    {
      std::string buffer (1024, 0);
      glGetProgramInfoLog (m_id, 1024, nullptr, buffer.data ());
      return err_t (buffer);
    }
  return ERR_OK;
}

shader_t::~shader_t ()
{
  if (glIsProgram (m_id))
    glDeleteProgram (m_id);
}

constexpr GLenum shader_type_to_GLenum (shader_type_t shader_type)
{
  switch (shader_type)
    {
    case shader_type_t::VERTEX:
      return GL_VERTEX_SHADER;
    case shader_type_t::FRAGMENT:
      return GL_FRAGMENT_SHADER;
    }
  abort (); // you shouldn't be here
}

template<shader_type_t SHADER_TYPE>
subshader_t<SHADER_TYPE>::subshader_t (const char *source_code)
{
  if (!source_code)
    return;

  m_id = glCreateShader (shader_type_to_GLenum (SHADER_TYPE));
  glShaderSource (m_id, 1, &source_code, nullptr);
  glCompileShader (m_id);
}

template<shader_type_t SHADER_TYPE>
err_t subshader_t<SHADER_TYPE>::check () const
{
  GLint status;
  glGetShaderiv (m_id, GL_COMPILE_STATUS, &status);
  if (!status)
    {
      std::string buffer (1024, 0);
      glGetShaderInfoLog (m_id, 1024, nullptr, buffer.data ());
      return err_t (buffer);
    }
  return ERR_OK;
}

template<shader_type_t SHADER_TYPE>
subshader_t<SHADER_TYPE>::~subshader_t ()
{
  if (glIsShader (m_id))
    glDeleteShader (m_id);
}

template class subshader_t<shader_type_t::VERTEX>;
template class subshader_t<shader_type_t::FRAGMENT>;
