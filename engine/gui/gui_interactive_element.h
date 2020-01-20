#ifndef GUI_INTERACTIVE_ELEMENT_H
#define GUI_INTERACTIVE_ELEMENT_H
#include "engine/gui/gui_element.h"


class gui_interactive_element_t : public gui_element_t
{
private:
  bool m_is_active;
public:
  gui_interactive_element_t () = delete;
  gui_interactive_element_t (const int x,
                             const int y,
                             const unsigned int w,
                             const unsigned int h,
                             const gui_horizontal_alignment_t align_h,
                             const gui_vertical_alignment_t align_v,
                             const bool is_active);
  bool is_active () const {return m_is_active;}
  void set_active (const bool is_active) {m_is_active = is_active;}
  bool is_mouse_pointer_inside (const int pivot_x,
                                const int pivot_y,
                                const int mouse_x,
                                const int mouse_y) const;
  virtual void on_mouse_button_pressed () = 0;
  virtual void on_mouse_move () = 0;
  virtual ~gui_interactive_element_t ();
};

#endif // GUI_INTERACTIVE_ELEMENT_H
