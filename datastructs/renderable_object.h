#pragma once
#ifndef RENDERABLE_OBJECT_T_H
#define RENDERABLE_OBJECT_T_H

/// @brief Base renderable object class
class renderable_object_t
{
public:
  renderable_object_t ();
  virtual void render () = 0;
  virtual ~renderable_object_t () = 0;
};

#endif // RENDERABLE_OBJECT_T_H
