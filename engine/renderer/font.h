#ifndef FONT_H
#define FONT_H
#include <GL/glew.h>
//#include <GL/gl.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <map>
#include "common/err_t.h"


class font_character_t
{
  GLuint m_texture_id;
  glm::ivec2 m_size;
  glm::ivec2 m_base_offset;
  GLuint m_glyph_offset;
public:
  font_character_t () = delete;
  font_character_t (const font_character_t &);
  font_character_t (font_character_t &&);
  font_character_t (GLuint texture_id,
                    glm::ivec2 size,
                    glm::ivec2 base_offset,
                    GLuint glyph_offset);
  GLuint get_texture_id () const {return m_texture_id;}
  const glm::ivec2 &get_size () const {return m_size;}
  const glm::ivec2 &get_base_offset () const {return  m_base_offset;}
  GLuint get_offset_to_next_glyph () const {return m_glyph_offset;}
  ~font_character_t ();
};

class font_t
{
  string m_font_name;
  map<GLchar, font_character_t> m_char;
  const unsigned int m_font_height;
  GLuint m_vao;
  GLuint m_vbo;
public:
  font_t (string &&font_name, const unsigned int font_height);
  err_t load ();
  const string &get_font_name () const {return m_font_name;}
  const font_character_t &get_character (GLchar ch) const {return m_char.at (ch);}
  void render_text (const string &text,
                    GLfloat x, GLfloat y, GLfloat scale) const;
  unsigned int get_font_height () const {return m_font_height;}
  ~font_t ();
};

#endif // FONT_H
