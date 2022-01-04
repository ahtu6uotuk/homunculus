#pragma once

#include "gui_element.h"

/// @brief Base class for all GUI objects that can be clicked
class gui_interactive_element_t : public gui_element_t
{
private:
  bool m_is_active;
public:
  gui_interactive_element_t () = delete;
  gui_interactive_element_t (renderer_t &renderer,
                             const int x,
                             const int y,
                             const unsigned int w,
                             const unsigned int h,
                             const gui_horizontal_alignment_t align_h,
                             const gui_vertical_alignment_t align_v,
                             const gui_element_t *pivot = nullptr,
                             const bool is_active = true);
  bool is_active () const {return m_is_active;}
  void set_active (const bool is_active) {m_is_active = is_active;}
  bool is_mouse_pointer_inside (const int mouse_x,
                                const int mouse_y) const;
  virtual void on_mouse_button_pressed () = 0;
  virtual void on_mouse_hover (const bool is_mouse_pointer_inside) = 0;
  virtual ~gui_interactive_element_t ();
};
