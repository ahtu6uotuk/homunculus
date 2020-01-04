#ifndef GUI_SYSTEM_H
#define GUI_SYSTEM_H
#include <vector>
#include "common/common.h"

class gui_context_t;


class gui_system_t
{
  vector<unique_ptr<gui_context_t>> m_context;
  unsigned int m_active_id = 0;
  unsigned int m_width;
  unsigned int m_height;
public:
  gui_system_t (const unsigned int width, const unsigned int height);
  gui_context_t *get_active_context () const {return m_context[m_active_id].get ();}
  void set_active_context (const unsigned int id);
  void draw ();
  void resize (const unsigned int width, const unsigned height);
  void handle_mouse_move_event (const int x, const int y);
  void handle_mouse_press_event (const int x, const int y);
  unsigned int get_width () const {return m_width;}
  unsigned int get_height () const {return m_height;}
  unsigned int make_context ();
  bool is_ok () const {return !m_context.empty ();}
  ~gui_system_t ();
};

#endif // GUI_SYSTEM_H
