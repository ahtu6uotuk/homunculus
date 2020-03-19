#ifndef GUI_SYSTEM_H
#define GUI_SYSTEM_H
#include <vector>
#include <memory>

class gui_context_t;
class gui_element_t;
enum class gui_horizontal_alignment_t;
enum class gui_vertical_alignment_t;


class gui_system_t
{
  std::vector<std::unique_ptr<gui_context_t>> m_context;
  std::unique_ptr<gui_context_t> m_world_content; // should be changed to contain different class

  unsigned int m_active_id = 0;
  unsigned int m_width;
  unsigned int m_height;
public:
  gui_system_t (const unsigned int width, const unsigned int height);
  gui_context_t *get_active_context () const {return m_context[m_active_id].get ();}
  gui_context_t *get_context (const unsigned int id) {return m_context[id].get ();}
  void set_active_context (const unsigned int id);
  void draw ();
  void resize (const unsigned int width, const unsigned height);
  void handle_mouse_move_event (const int x, const int y);
  void handle_mouse_press_event (const int x, const int y);
  int get_pivot_x (gui_horizontal_alignment_t align_h) const;
  int get_pivot_y (gui_vertical_alignment_t align_v) const;
  unsigned int get_width () const {return m_width;}
  unsigned int get_height () const {return m_height;}
  unsigned int make_context ();
  bool is_ok () const {return !m_context.empty ();}
  void set_world_content (std::unique_ptr<gui_context_t> world_content);
  ~gui_system_t ();
};

#endif // GUI_SYSTEM_H
