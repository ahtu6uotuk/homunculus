#include "gui_element.h"
#include "engine/renderer/renderer.h"
#include "engine/gui/gui_system.h"


gui_element_t::gui_element_t (renderer_t &renderer,
                              const int x,
                              const int y,
                              const int w,
                              const int h,
                              gui_horizontal_alignment_t h_align,
                              gui_vertical_alignment_t v_align,
                              const gui_element_t *pivot):
  m_renderer (renderer),
  m_x (x),
  m_y (y),
  m_width (w),
  m_height (h),
  m_align_h (h_align),
  m_align_v (v_align),
  m_pivot (pivot)
{}

int gui_element_t::get_absolute_x () const
{
  return m_pivot ? m_pivot->get_absolute_x () + m_x : m_renderer.get_gui ().get_pivot_x (m_align_h);
}

int gui_element_t::get_absolute_y () const
{
  return m_pivot ? m_pivot->get_absolute_y () + m_y : m_renderer.get_gui ().get_pivot_y (m_align_v);
}

gui_element_t::~gui_element_t ()
{}
