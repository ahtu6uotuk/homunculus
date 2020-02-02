#include "gui_interactive_element.h"
#include "gui_system.h"
#include "gui_context.h"

gui_context_t::gui_context_t (gui_system_t &sys):
  m_system (sys)
{}

void gui_context_t::add_element (unique_ptr<gui_element_t> element)
{
  m_context_element.push_back (move (element));
}

void gui_context_t::resize (const unsigned int width, const unsigned int height)
{
  do_nothing (width, height);
}

void gui_context_t::draw ()
{
  for (auto &e : m_context_element)
    e->draw ();

  for (auto &e : m_context_interactive)
    e->draw ();
}

void gui_context_t::handle_mouse_move_event (const int x, const int y)
{
  for (auto &e : m_context_interactive)
    {
      if (e->is_active ())
        {
          e->on_mouse_hover (e->is_mouse_pointer_inside (x, y));
        }
    }
}

#include "gui_textline.h"
void gui_context_t::add_test_page (renderer_t &renderer)
{
  add_element (make_unique<gui_textline_t> (renderer,
                                            10, 10, 300, 100,
                                            gui_horizontal_alignment_t::LEFT, gui_vertical_alignment_t::UP,
                                            "LU", glm::vec3 (.7f, .15f, .15f), 48));
  add_element (make_unique<gui_textline_t> (renderer,
                                            10, 10, 300, 100,
                                            gui_horizontal_alignment_t::LEFT, gui_vertical_alignment_t::DOWN,
                                            "LD", glm::vec3 (.7f, .15f, .15f), 48));
  add_element (make_unique<gui_textline_t> (renderer,
                                            10, 10, 300, 100,
                                            gui_horizontal_alignment_t::RIGHT, gui_vertical_alignment_t::DOWN,
                                            "боттом кек", glm::vec3 (.7f, .15f, .15f), 48));
  add_element (make_unique<gui_textline_t> (renderer,
                                            10, 10, 300, 100,
                                            gui_horizontal_alignment_t::RIGHT, gui_vertical_alignment_t::UP,
                                            "ТОП КЕК", glm::vec3 (.7f, .15f, .15f), 48));
  add_element (make_unique<gui_textline_t> (renderer,
                                            10, 10, 300, 100,
                                            gui_horizontal_alignment_t::CENTER, gui_vertical_alignment_t::CENTER,
                                            "ещё один кек", glm::vec3 (.7f, .15f, .15f), 48));
}

void gui_context_t::handle_mouse_press_event (const int x, const int y)
{
  for (auto &e : m_context_interactive)
    {
      if (e->is_active ())
        {
          if (e->is_mouse_pointer_inside (x, y))
            e->on_mouse_button_pressed ();
        }
    }
}

gui_context_t::~gui_context_t ()
{}
