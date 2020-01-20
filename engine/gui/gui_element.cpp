#include "gui_element.h"

gui_element_t::gui_element_t (renderer_t &renderer,
                              const int x,
                              const int y,
                              const int w,
                              const int h,
                              gui_horizontal_alignment_t h_align,
                              gui_vertical_alignment_t v_align):
  m_renderer (renderer),
  m_x (x),
  m_y (y),
  m_width (w),
  m_height (h),
  m_align_h (h_align),
  m_align_v (v_align)
{}

gui_element_t::~gui_element_t ()
{

}
