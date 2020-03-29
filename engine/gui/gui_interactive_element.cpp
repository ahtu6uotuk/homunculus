#include "gui_interactive_element.h"

gui_interactive_element_t::gui_interactive_element_t (
    renderer_t &renderer,
    const int x,
    const int y,
    const unsigned int w,
    const unsigned int h,
    gui_horizontal_alignment_t align_h,
    gui_vertical_alignment_t align_v,
    const gui_element_t *pivot,
    const bool is_active):
  gui_element_t (renderer, x, y, w, h, align_h, align_v, pivot),
  m_is_active (is_active)
{}

bool gui_interactive_element_t::is_mouse_pointer_inside (const int mouse_x, const int mouse_y) const
{
  const int abs_x = get_absolute_x ();
  const int abs_y = get_absolute_y ();
  return     (mouse_x >= abs_x) && (mouse_x < abs_x + get_width ())
          && (mouse_y >= abs_y) && (mouse_y < abs_y + get_height ());
}

gui_interactive_element_t::~gui_interactive_element_t ()
{}
