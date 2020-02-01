#ifndef gui_textline_H
#define gui_textline_H
#include "gui_element.h"
#include "common/common.h"
#include <glm/vec3.hpp>


class gui_textline_t : public gui_element_t
{
  string m_text;
  glm::vec3 m_color;
  unsigned int m_font_size;
public:
  gui_textline_t () = delete;
  gui_textline_t (renderer_t &renderer,
                  const unsigned int x,
                  const unsigned int y,
                  gui_horizontal_alignment_t h_align,
                  gui_vertical_alignment_t v_align,
                  const string &text,
                  const glm::vec3 &color,
                  const unsigned int font_size,
                  const gui_element_t *pivot = nullptr);
  void set_color (const glm::vec3 &color);
  void draw () override;
};

#endif // gui_textline_H
