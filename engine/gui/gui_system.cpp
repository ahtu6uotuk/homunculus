#include "gui_system.h"

#include "engine/gui/gui_context.h"
#include "engine/gui/gui_element.h"

gui_system_t::gui_system_t (const unsigned int width, const unsigned int height):
  m_width (width), m_height (height)
{
}

void gui_system_t::set_active_context (const unsigned int id)
{
  m_active_id = id;
}

void gui_system_t::draw ()
{
  if (m_world_content)
    {
      m_world_content->draw ();
      m_world_content.reset ();
    }
  m_context[m_active_id]->draw ();
}

void gui_system_t::set_world_content (std::unique_ptr<gui_context_t> world_content)
{
  m_world_content = move (world_content);
}

void gui_system_t::resize (unsigned int width, unsigned height)
{
  m_width = width;
  m_height = height;
  m_context[m_active_id]->resize (width, height);
}

void gui_system_t::handle_mouse_move_event (const int x, const int y)
{
  get_active_context ()->handle_mouse_move_event (x, y);
}

void gui_system_t::handle_mouse_press_event (const int x, const int y)
{
  get_active_context ()->handle_mouse_press_event (x, y);
}

unsigned int gui_system_t::make_context ()
{
  m_context.push_back (std::make_unique<gui_context_t> (*this));
  return static_cast<unsigned int> (m_context.size ());
}


int gui_system_t::get_pivot_x (gui_horizontal_alignment_t align_h) const
{
  switch (align_h)
    {
    case gui_horizontal_alignment_t::ABSOLUTE:
    case gui_horizontal_alignment_t::LEFT:
      return 0;
    case gui_horizontal_alignment_t::CENTER:
      return static_cast<int> (get_width () / 2);
    case gui_horizontal_alignment_t::RIGHT:
      return static_cast<int> (get_width ());
    case gui_horizontal_alignment_t::COUNT:
      abort ();
      return -1;
    }
  abort ();
  return -1;
}

int gui_system_t::get_pivot_y (gui_vertical_alignment_t align_v) const
{
  switch (align_v)
    {
    case gui_vertical_alignment_t::UP:
      return static_cast<int> (get_height ());
    case gui_vertical_alignment_t::CENTER:
      return static_cast<int> (get_height () / 2);
    case gui_vertical_alignment_t::ABSOLUTE:
    case gui_vertical_alignment_t::DOWN:
      return 0;
    case gui_vertical_alignment_t::COUNT:
      abort ();
      return -1;
    }
  abort ();
  return -1;
}

gui_system_t::~gui_system_t ()
{}
