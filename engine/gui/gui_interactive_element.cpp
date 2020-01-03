#include "gui_interactive_element.h"


gui_interactive_element_t::gui_interactive_element_t (
    const int x,
    const int y,
    const unsigned int w,
    const unsigned int h,
    gui_horizontal_alignment_t align_h,
    gui_vertical_alignment_t align_v,
    const bool is_active):
  gui_element_t (x, y, w, h, align_h, align_v),
  m_is_active (is_active)
{}

gui_interactive_element_t::~gui_interactive_element_t ()
{

}
