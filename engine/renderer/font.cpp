#include "font.h"
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H

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

font_t::font_t (string &&font_name):
  m_font_name (font_name)
{

}

err_t font_t::load ()
{
  string ttf_filename = m_font_name;
  FT_Library ftlib;
  if (FT_Init_FreeType (&ftlib))
    return err_t ("failed to init FreeType Library!");
  FT_Face ftface;
  if (FT_New_Face (ftlib, ttf_filename.c_str (), 0, &ftface))
    {
      FT_Done_FreeType (ftlib);
      return err_t ("FreeType font init error!");
    }
  FT_Set_Pixel_Sizes (ftface, 0, 48);

  glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
  for (GLubyte c = 0; c < 128; c++)
    {
      // Load character glyph
      if (FT_Load_Char (ftface, c, FT_LOAD_RENDER))
        {
          FT_Done_Face (ftface);
          FT_Done_FreeType (ftlib);
          return err_t (string ("failed to load glyph: index ").append (to_string (static_cast<int> (c))));
        }
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

      m_char.insert (make_pair (c,
                                font_character_t (texture,
                                                  glm::ivec2 (ftface->glyph->bitmap.width,
                                                              ftface->glyph->bitmap.rows),
                                                  glm::ivec2 (ftface->glyph->bitmap_left,
                                                              ftface->glyph->bitmap_top),
                                                  ftface->glyph->advance.x)
                                )
                     );
    }
  FT_Done_Face (ftface);
  FT_Done_FreeType (ftlib);
  return ERR_OK;
}
