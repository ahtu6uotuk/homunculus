#ifndef FONT_H
#define FONT_H
#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <map>
#include "common/err_t.h"

typedef struct FT_LibraryRec_  *FT_Library;
typedef struct FT_FaceRec_*  FT_Face;

class shader_t;

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
  map<GLubyte, font_character_t> m_eng_chars;
  map<GLubyte, font_character_t> m_ru_chars;
  const unsigned int m_font_height;
  GLuint m_vao;
  GLuint m_vbo;
  shader_t *m_text_shader;
private:
  err_t load_chars (FT_Library &ftlib, FT_Face &ftface, size_t start, map<GLubyte, font_character_t> &chars);
  const font_character_t &process_character (const unsigned char *&ch) const;
  GLfloat get_scale (const unsigned int font_size) const;
public:
  font_t (string &&font_name, const unsigned int font_height);
  err_t load ();
  const string &get_font_name () const {return m_font_name;}
  void render_text (const string &text,
                    GLfloat x, GLfloat y, GLuint scale,
                    const glm::vec3 &color) const;
  unsigned int get_font_height () const {return m_font_height;}
  unsigned int get_text_width (const string &text) const;
  void set_text_shader (shader_t *shader);
  ~font_t ();
};

#endif // FONT_H
