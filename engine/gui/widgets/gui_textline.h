#pragma once

#include <glm/vec3.hpp>

#include "common/common.h"
#include "gui_element.h"

class font_t;

class gui_textline_t : public gui_element_t
{
  font_t &m_font;
  std::string m_text;
  glm::vec3 m_color;
  unsigned int m_font_size;
public:
  gui_textline_t () = delete;
  gui_textline_t (renderer_t &renderer,
                  const unsigned int x,
                  const unsigned int y,
                  gui_horizontal_alignment_t h_align,
                  gui_vertical_alignment_t v_align,
                  const std::string &text,
                  const glm::vec3 &color,
                  const unsigned int font_size,
                  const gui_element_t *pivot = nullptr);
  void set_color (const glm::vec3 &color);
  void set_text (const std::string &text);
  void draw () override;
  ~gui_textline_t ();
};
