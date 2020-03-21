#pragma once

#include "common/string/string_utils.h"
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
  move_action (double dx, double dy, double dz) : m_dx (dx), m_dy (dy), m_dz (dz) {}
  void exec_impl (object_base &actor, world_t &world) override;

private:
  double m_dx;
  double m_dy;
  double m_dz;
};














