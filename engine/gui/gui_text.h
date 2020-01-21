#ifndef GUI_TEXT_H
#define GUI_TEXT_H
#include "gui_element.h"
#include "common/common.h"
#include <glm/vec3.hpp>


class gui_text_t : public gui_element_t
{
  string m_text;
  glm::vec3 m_color;
public:
  gui_text_t () = delete;
  gui_text_t (renderer_t &renderer,
              const unsigned int x,
              const unsigned int y,
              const unsigned int width,
              const unsigned int height,
              gui_horizontal_alignment_t h_align,
              gui_vertical_alignment_t v_align,
              const char *text);
  void draw () override;
};

#endif // GUI_TEXT_H
