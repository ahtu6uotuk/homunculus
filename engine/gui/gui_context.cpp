#include "gui_context.h"

#include "common/common.h"
#include "widgets/gui_interactive_element.h"
#include "engine/gui/gui_system.h"

gui_context_t::gui_context_t (gui_system_t &sys):
  m_system (sys)
{}

void gui_context_t::add_element (std::unique_ptr<gui_element_t> element)
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

gui_context_t::~gui_context_t () = default;
