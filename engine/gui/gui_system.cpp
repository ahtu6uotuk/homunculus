#include "gui_context.h"
#include "gui_system.h"

gui_system_t::gui_system_t (const unsigned int width, const unsigned int height):
  m_width (width), m_height (height)
{}

void gui_system_t::set_active_context (const unsigned int id)
{
  m_active_id = id;
}

void gui_system_t::draw ()
{
  m_context[m_active_id]->draw ();
}

void gui_system_t::resize (unsigned int width, unsigned height)
{
  m_width = width;
  m_height = height;
  m_context[m_active_id]->resize (width, height);
}

void gui_system_t::handle_mouse_move_event (const int x, const int y)
{
  do_nothing (x, y);
}

void gui_system_t::handle_mouse_press_event (const int x, const int y)
{
  get_active_context ()->handle_mouse_press_event (x, y);
}

unsigned int gui_system_t::make_context ()
{
  m_context.push_back (make_unique<gui_context_t> (*this));
  return static_cast<unsigned int> (m_context.size ());
}

gui_system_t::~gui_system_t ()
{}
