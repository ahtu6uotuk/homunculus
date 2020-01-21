#ifndef SHADER_H
#define SHADER_H
#include <GL/gl.h>
#include "common/err_t.h"


template<GLenum SHADER_TYPE>
class subshader_t
{
  GLuint m_id = 0;
public:
  subshader_t () = delete;
  subshader_t (const subshader_t &) = delete;
  subshader_t (subshader_t &&) = delete;
  explicit subshader_t (const char *source_code);
  GLuint get_id () const {return m_id;}
  err_t check_compilation_status () const;
  ~subshader_t ();
};

class shader_t
{
  GLuint m_id = 0;
public:
  shader_t () = delete;
  shader_t (const shader_t &) = delete;
  shader_t (shader_t &&) = delete;
  shader_t (GLuint m_vertex_id, GLuint m_fragment_id);
  void use () const;
  void set_int (const string &var_name, const int value) const;
  void set_float (const string &var_name, const float value) const;
  void set_double (const string &var_name, const double value) const;
  GLuint get_program_id () const {return m_id;}
  err_t check_link_status ();
  ~shader_t ();
};

#endif // SHADER_H