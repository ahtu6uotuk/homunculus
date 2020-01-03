#include "gui_interactive_element.h"
#include "gui_system.h"
#include "gui_context.h"

gui_context_t::gui_context_t (gui_system_t &sys):
  m_system (sys)
{}

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

int gui_context_t::get_x_by_alignment (gui_horizontal_alignment_t align_h) const
{
  switch (align_h)
    {
    case gui_horizontal_alignment_t::ABSOLUTE:
    case gui_horizontal_alignment_t::LEFT:
      return 0;
    case gui_horizontal_alignment_t::CENTER:
      return static_cast<int> (m_system.get_width () / 2);
    case gui_horizontal_alignment_t::RIGHT:
      return static_cast<int> (m_system.get_width ()) - 1;
    case gui_horizontal_alignment_t::COUNT:
      abort ();
      return -1;
    }
  abort ();
  return -1;
}

int gui_context_t::get_y_by_alignment (gui_vertical_alignment_t align_v) const
{
  switch (align_v)
    {
    case gui_vertical_alignment_t::ABSOLUTE:
    case gui_vertical_alignment_t::UP:
      return 0;
    case gui_vertical_alignment_t::CENTER:
      return static_cast<int> (m_system.get_height () / 2);
    case gui_vertical_alignment_t::DOWN:
      return static_cast<int> (m_system.get_height ()) - 1;
    case gui_vertical_alignment_t::COUNT:
      abort ();
      return -1;
    }
  abort ();
  return -1;
}

void gui_context_t::handle_mouse_press_event (const int x, const int y)
{
  for (auto &e : m_context_interactive)
    {
      if (e->is_active ())
        {
          const auto xpos = e->get_x () + get_x_by_alignment (e->get_horizontal_alignment ());
          const auto ypos = e->get_y () + get_y_by_alignment (e->get_vertical_alignment ());
          if (   x >= xpos && x < (xpos + toi (e->get_width ()))
              && y >= ypos && y < (ypos + toi (e->get_height ())))
            e->on_mouse_pressed ();
        }
    }
}

gui_context_t::~gui_context_t ()
{

}
