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

void shader_t::set_int (const string &var_name, const int value) const
{
  glUniform1i (glGetUniformLocation (m_id, var_name.c_str ()), value);
}

void shader_t::set_float (const string &var_name, const float value) const
{
  glUniform1f (glGetUniformLocation (m_id, var_name.c_str ()), value);
}

void shader_t::set_double (const string &var_name, const double value) const
{
  glUniform1d (glGetUniformLocation (m_id, var_name.c_str ()), value);
}

err_t shader_t::check_link_status ()
{
  GLint status = 0;
  glGetProgramiv (m_id, GL_LINK_STATUS, &status);
  if (!status)
    {
      string buffer (1024, 0);
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

template<GLenum SHADER_TYPE>
subshader_t<SHADER_TYPE>::subshader_t (const char *source_code)
{
  if (!source_code)
    return;

  m_id = glCreateShader (SHADER_TYPE);
  glShaderSource (m_id, 1, &source_code, nullptr);
  glCompileShader (m_id);
}

template<GLenum SHADER_TYPE>
err_t subshader_t<SHADER_TYPE>::check_compilation_status () const
{
  GLint status;
  glGetShaderiv (m_id, GL_COMPILE_STATUS, &status);
  if (!status)
    {
      string buffer (1024, 0);
      glGetShaderInfoLog (m_id, 1024, nullptr, buffer.data ());
      return err_t (buffer);
    }
  return ERR_OK;
}

template<GLenum SHADER_TYPE>
subshader_t<SHADER_TYPE>::~subshader_t()
{
  if (glIsShader (m_id))
    glDeleteShader (m_id);
}

subshader_t<GL_VERTEX_SHADER> vertex_shader (nullptr);
subshader_t<GL_FRAGMENT_SHADER> fragment_shader (nullptr);
