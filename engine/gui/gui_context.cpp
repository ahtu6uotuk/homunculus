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
          if (e->is_mouse_pointer_inside (m_system.get_pivot_x (e->get_horizontal_alignment ()),
                                          m_system.get_pivot_y (e->get_vertical_alignment ()),
                                          x,
                                          y))
            e->on_mouse_move ();
        }
    }
}

void gui_context_t::handle_mouse_press_event (const int x, const int y)
{
  for (auto &e : m_context_interactive)
    {
      if (e->is_active ())
        {
          if (e->is_mouse_pointer_inside (m_system.get_pivot_x (e->get_horizontal_alignment ()),
                                          m_system.get_pivot_y (e->get_vertical_alignment ()),
                                          x,
                                          y))
            e->on_mouse_button_pressed ();
        }
    }
}

gui_context_t::~gui_context_t ()
{}
