#include "font.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H

#include "common/common.h"
#include "datastructs/shader.h"

font_character_t::font_character_t (const font_character_t &b):
  m_texture_id (b.m_texture_id),
  m_size (b.m_size),
  m_base_offset (b.m_base_offset),
  m_glyph_offset (b.m_glyph_offset)
{}

font_character_t::font_character_t (font_character_t &&b):
  m_texture_id (b.m_texture_id),
  m_size (b.m_size),
  m_base_offset (b.m_base_offset),
  m_glyph_offset (b.m_glyph_offset)
{}

font_character_t::font_character_t (GLuint texture_id,
                                    glm::ivec2 size,
                                    glm::ivec2 base_offset,
                                    GLuint glyph_offset):
  m_texture_id (texture_id),
  m_size (size),
  m_base_offset (base_offset),
  m_glyph_offset (glyph_offset)
{}

font_character_t::~font_character_t ()
{}

font_t::font_t (std::string &&font_name, const unsigned int font_height):
  m_font_name (font_name),
  m_font_height (font_height)
{}

err_t font_t::load_chars (FT_Library &ftlib, FT_Face &ftface, size_t start, std::map<GLubyte, font_character_t> &chars)
{
  for (GLubyte c = 0; c < 128; c++)
    {
      // Load character glyph
      if (FT_Load_Char (ftface, start + c, FT_LOAD_RENDER))
        {
          FT_Done_Face (ftface);
          FT_Done_FreeType (ftlib);
          return err_t (std::string ("FreeType: failed to load glyph: index ").append (std::to_string (static_cast<int> (c))));
        }
#if 0
      auto &bmp = ftface->glyph->bitmap;
      printf ("Character %c: rows = %u, width = %u\n", c, bmp.rows, bmp.width);
      for (uint r = 0; r < bmp.rows; r++)
        {
          for (uint w = 0; w < bmp.width; w++)
            {
              printf ("%4u", bmp.buffer[r * bmp.width + w]);
            }
          printf ("\n");
        }
      fflush (stdout);
#endif

      // Generate texture
      GLuint texture;
      glGenTextures (1, &texture);
      glBindTexture (GL_TEXTURE_2D, texture);
      glTexImage2D (
          GL_TEXTURE_2D,
          0,
          GL_RED,
          ftface->glyph->bitmap.width,
          ftface->glyph->bitmap.rows,
          0,
          GL_RED,
          GL_UNSIGNED_BYTE,
          ftface->glyph->bitmap.buffer
          );
      // Set texture options
      glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      chars.insert (std::make_pair (c,
                                font_character_t (texture,
                                                  glm::ivec2 (ftface->glyph->bitmap.width,
                                                              ftface->glyph->bitmap.rows),
                                                  glm::ivec2 (ftface->glyph->bitmap_left,
                                                              ftface->glyph->bitmap_top),
                                                  ftface->glyph->advance.x)
                                )
                     );
    }
  return ERR_OK;
}

err_t font_t::load ()
{
  std::string ttf_filename = std::string ("gamedata/fonts/").append (m_font_name);
  FT_Library ftlib;
  if (FT_Init_FreeType (&ftlib))
    return err_t ("FreeType: failed to init library!");
  FT_Face ftface;
  if (FT_New_Face (ftlib, ttf_filename.c_str (), 0, &ftface))
    {
      FT_Done_FreeType (ftlib);
      return err_t (std::string ("FreeType: failed to load font ").append (ttf_filename));
    }
  FT_Set_Pixel_Sizes (ftface, 0, m_font_height);

  glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
  RETURN_IF_FAIL (load_chars (ftlib, ftface, 0, m_eng_chars));
  RETURN_IF_FAIL (load_chars (ftlib, ftface, 1024, m_ru_chars));
  FT_Done_Face (ftface);
  FT_Done_FreeType (ftlib);
  glGenVertexArrays (1, &m_vao);
  glGenBuffers (1, &m_vbo);
  glBindVertexArray (m_vao);
  glBindBuffer (GL_ARRAY_BUFFER, m_vbo);
  glBufferData (GL_ARRAY_BUFFER, 6 * 4 * sizeof (float), nullptr, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray (0);
  glVertexAttribPointer (0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof (GLfloat), nullptr);
  glBindBuffer (GL_ARRAY_BUFFER, 0);
  glBindVertexArray (0);

  return ERR_OK;
}

const font_character_t &font_t::process_character (const unsigned char *&ch) const
{
  assert_check (ch, "Sanity");
  if (*ch < 128)
    return m_eng_chars.at (*ch);

  assert_check (*ch == 208 || *ch == 209, "Russian letters");
  unsigned char shift = (*ch == 209 ? 64 : 0);

  assert_check (++ch, "Sanity");
  return m_ru_chars.at (*ch + shift - 128);
}

void font_t::render_text (const std::string &text,
                          GLfloat x,
                          GLfloat y,
                          GLuint font_size,
                          const glm::vec3 &color) const
{
  m_text_shader->use ();
  m_text_shader->set_uniform_3f ("textColor", color.r, color.g, color.b);
  GLfloat scale = get_scale (font_size);
  glActiveTexture (GL_TEXTURE0);
  glBindVertexArray (m_vao);

  for (const unsigned char *c = (unsigned char *) text.c_str (); *c; c++)
    {
      const auto &ch = process_character (c);
      const auto &ch_size = ch.get_size ();
      const auto base_offset = ch.get_base_offset ();
      GLfloat xpos = x + base_offset.x * scale;
      GLfloat ypos = y - (ch_size.y - base_offset.y) * scale;

      GLfloat w = ch_size.x * scale;
      GLfloat h = ch_size.y * scale;
      GLfloat vertices[6][4] = {
                  { xpos,     ypos + h,   0.0, 0.0 },
                  { xpos,     ypos,       0.0, 1.0 },
                  { xpos + w, ypos,       1.0, 1.0 },

                  { xpos,     ypos + h,   0.0, 0.0 },
                  { xpos + w, ypos,       1.0, 1.0 },
                  { xpos + w, ypos + h,   1.0, 0.0 }
              };
      // Render glyph texture over quad
      glBindTexture (GL_TEXTURE_2D, ch.get_texture_id ());
      // Update content of VBO memory
      glBindBuffer (GL_ARRAY_BUFFER, m_vbo);
      glBufferSubData (GL_ARRAY_BUFFER, 0, sizeof (vertices), vertices);
      glBindBuffer (GL_ARRAY_BUFFER, 0);
      // Render quad
      glDrawArrays (GL_TRIANGLES, 0, 6);
      // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
      x += (ch.get_offset_to_next_glyph () >> 6) * scale;
    }
  glBindVertexArray (0);
  glBindTexture (GL_TEXTURE_2D, 0);
}

unsigned int font_t::get_text_width (const std::string &text) const
{
  unsigned int width = 0;
  for (const unsigned char *c = (unsigned char *) text.c_str (); *c; c++)
    {
      const auto &ch = process_character (c);
      width += ch.get_size ().x;
    }
  return width;
}

GLfloat font_t::get_scale (const unsigned int font_size) const
{
  return static_cast<GLfloat> (font_size) / static_cast<GLfloat> (m_font_height);
}

void font_t::set_text_shader (shader_t *shader)
{
  m_text_shader = shader;
  m_text_shader->use ();
  glm::mat4 mat = glm::ortho (0.f, 800.f, 0.f, 600.f);
  m_text_shader->set_uniform_mat4 ("projection", glm::value_ptr (mat));
  m_text_shader->set_uniform_3f ("textColor", .7f, .15f, .15f);
}

font_t::~font_t ()
{
  if (glIsVertexArray (m_vao))
    glDeleteVertexArrays (1, &m_vao);
  if (glIsBuffer (m_vbo))
    glDeleteBuffers (1, &m_vbo);
}
