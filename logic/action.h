#pragma once
#include "common/string/string_utils.h"
// TODO: move action out of logic
#include "engine/renderer/camera.h"
class dialog_tree;
class world_t;
class object_base;

class action
{
public:
  virtual ~action () {}
  void exec (int actor_id, world_t &world);
protected:
  virtual void exec_impl (object_base &actor, world_t &world) = 0;
};

class no_action : public action
{
public:
  ~no_action () {}
  void exec_impl (object_base &, world_t &) override {}
};

class move_action : public action
{
public:
  ~move_action () {}
  move_action (movement_direction_t direction, float speed, float dt)
    : m_direction (direction), m_speed (speed), m_dt (dt)
  {
  }
  void exec_impl (object_base &actor, world_t &world) override;

private:
  movement_direction_t m_direction;
  float m_speed;
  float m_dt;
};














