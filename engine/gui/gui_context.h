#pragma once
#include <vector>
#include <memory>

class gui_system_t;
class gui_element_t;
class gui_interactive_element_t;
enum class gui_horizontal_alignment_t;
enum class gui_vertical_alignment_t;

class renderer_t;

class gui_context_t
{
  gui_system_t &m_system;
  std::vector<std::unique_ptr<gui_element_t>> m_context_element;
  std::vector<std::unique_ptr<gui_interactive_element_t>> m_context_interactive;
public:
  gui_context_t (gui_system_t &sys);
  void add_element (std::unique_ptr<gui_element_t> element);
  void add_element (std::unique_ptr<gui_interactive_element_t> element);
  void resize (const unsigned int width, const unsigned int height);
  void draw ();
  void handle_mouse_move_event (const int x, const int y);
  void handle_mouse_press_event (const int x, const int y);
  void add_test_page (renderer_t &renderer); /// plz delete me!
  ~gui_context_t ();
};
