#ifndef GUI_ELEMENT_H
#define GUI_ELEMENT_H


class renderer_t;
class gui_context_t;

enum class gui_horizontal_alignment_t
{
  ABSOLUTE,
  LEFT,
  CENTER,
  RIGHT,
  COUNT
};

enum class gui_vertical_alignment_t
{
  ABSOLUTE,
  UP,
  CENTER,
  DOWN,
  COUNT
};


/// @brief Parent class for all GUI objects
class gui_element_t
{
private:
  renderer_t &m_renderer;
  int m_x; ///< x-position according to horizontal alignment
  int m_y; ///< y-position according to vertical alignment
  int m_width;
  int m_height;
  gui_horizontal_alignment_t m_align_h;
  gui_vertical_alignment_t m_align_v;
  gui_element_t *m_pivot;
private:
public:
  gui_element_t () = delete;
  gui_element_t (renderer_t &renderer,
                 const int x, const int y,
                 const int w, const int h,
                 gui_horizontal_alignment_t h_align,
                 gui_vertical_alignment_t v_align,
                 gui_element_t *pivot = nullptr);
  virtual void draw () = 0;
  int get_x () const {return m_x;}
  int get_y () const {return m_y;}
  int get_width () const {return m_width;}
  int get_height () const {return m_height;}
  void set_x (const int x) {m_x = x;}
  void set_y (const int y) {m_y = y;}
  void set_width (const int width) {m_width = width;}
  void set_height (const int height) {m_height = height;}
  gui_horizontal_alignment_t get_horizontal_alignment () const {return m_align_h;}
  gui_vertical_alignment_t get_vertical_alignment () const {return m_align_v;}
  renderer_t &get_renderer () {return m_renderer;}
  int get_absolute_x () const;
  int get_absolute_y () const;
  virtual ~gui_element_t ();
};

#endif // GUI_ELEMENT_H
