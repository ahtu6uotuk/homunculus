#ifndef RENDERER_H
#define RENDERER_H
#include "common/err_t.h"

class renderer_t
{
public:
  renderer_t ();
  err_t init ();
  void render ();
};

#endif // RENDERER_H
