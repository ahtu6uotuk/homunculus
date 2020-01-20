#ifndef GUI_CONTEXT_H
#define GUI_CONTEXT_H
#include <vector>
#include "common/common.h"

class gui_system_t;
class gui_element_t;
class gui_interactive_element_t;
enum class gui_horizontal_alignment_t;
enum class gui_vertical_alignment_t;


class gui_context_t
{
  gui_system_t &m_system;
  vector<unique_ptr<gui_element_t>> m_context_element;
  vector<unique_ptr<gui_interactive_element_t>> m_context_interactive;
public:
  gui_context_t (gui_system_t &sys);
  void add_element (unique_ptr<gui_element_t> element);
  void add_element (unique_ptr<gui_interactive_element_t> element);
  void resize (const unsigned int width, const unsigned int height);
  void draw ();
  void handle_mouse_move_event (const int x, const int y);
  void handle_mouse_press_event (const int x, const int y);
  ~gui_context_t ();
};

#endif // GUI_CONTEXT_H
