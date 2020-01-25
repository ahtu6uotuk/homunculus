#include "gui_textline.h"
#include "engine/renderer/renderer.h"


gui_textline_t::gui_textline_t (renderer_t &renderer,
                                const unsigned int x,
                                const unsigned int y,
                                const unsigned int width,
                                const unsigned int height,
                                gui_horizontal_alignment_t h_align,
                                gui_vertical_alignment_t v_align,
                                const char *text,
                                const glm::vec3 &color,
                                const unsigned int font_size,
                                const gui_element_t *pivot):
  gui_element_t (renderer, x, y, width, height, h_align, v_align, pivot),
  m_text (text),
  m_color (color),
  m_font_size (font_size)
{}

gui_textline_t::gui_textline_t (renderer_t &renderer,
                                const unsigned int x,
                                const unsigned int y,
                                const unsigned int width,
                                const unsigned int height,
                                gui_horizontal_alignment_t h_align,
                                gui_vertical_alignment_t v_align,
                                const string &text, const glm::vec3 &color,
                                const unsigned int font_size, const gui_element_t *pivot):
  gui_textline_t (renderer, x, y, width, height, h_align, v_align, text.c_str (), color, font_size, pivot)
{}

void gui_textline_t::set_color (const glm::vec3 &color)
{
  m_color = color;
}

void gui_textline_t::draw ()
{
  auto &renderer = get_renderer ();
  glm::vec2 pos = glm::vec2 (static_cast<float> (get_x ()), static_cast<float> (get_y ()));
  renderer.render_text (m_text, pos, m_color, m_font_size);
}
