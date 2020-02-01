#include "gui_textline.h"
#include "engine/renderer/renderer.h"

gui_textline_t::gui_textline_t (
    renderer_t &renderer,
    const unsigned int x,
    const unsigned int y,
    gui_horizontal_alignment_t h_align,
    gui_vertical_alignment_t v_align,
    const string &text,
    const glm::vec3 &color,
    const unsigned int font_size,
    const gui_element_t *pivot)
  : gui_element_t (renderer, x, y,
                   renderer.get_font ().get_text_width (text),
                   renderer.get_font ().get_font_height (),
                   h_align, v_align, pivot),
    m_text (text),
    m_color (color),
    m_font_size (font_size)
{
}

void gui_textline_t::set_color (const glm::vec3 &color)
{
  m_color = color;
}

void gui_textline_t::draw ()
{
  auto &renderer = get_renderer ();
  glm::vec2 pos = glm::vec2 (static_cast<float> (get_absolute_x ()), static_cast<float> (get_absolute_y ()));
  renderer.render_text (m_text, pos, m_color, m_font_size);
}
