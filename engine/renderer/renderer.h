#ifndef RENDERER_H
#define RENDERER_H
#include "common/err_t.h"
#include "engine/renderer/font.h"

class renderer_t
{
  font_t m_font;
public:
  renderer_t ();
  err_t init ();
  void render ();
};

#endif // RENDERER_H
