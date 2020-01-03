#ifndef GUI_ELEMENT_H
#define GUI_ELEMENT_H


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
  int m_x; ///< x-position according to horizontal alignment
  int m_y; ///< y-position according to vertical alignment
  unsigned int m_width;
  unsigned int m_height;
  gui_horizontal_alignment_t m_align_h;
  gui_vertical_alignment_t m_align_v;
private:
public:
  gui_element_t () = delete;
  gui_element_t (const int x, const int y,
                 const unsigned int w, const unsigned int h,
                 gui_horizontal_alignment_t h_align,
                 gui_vertical_alignment_t v_align);
  virtual void draw () = 0;
  int get_x () const {return m_x;}
  int get_y () const {return m_y;}
  unsigned int get_width () const {return m_width;}
  unsigned int get_height () const {return m_height;}
  void set_x (const int x) {m_x = x;}
  void set_y (const int y) {m_y = y;}
  void set_width (const unsigned int width) {m_width = width;}
  void set_height (const unsigned int height) {m_height = height;}
  gui_horizontal_alignment_t get_horizontal_alignment () const {return m_align_h;}
  gui_vertical_alignment_t get_vertical_alignment () const {return m_align_v;}
  virtual ~gui_element_t ();
};

#endif // GUI_ELEMENT_H
