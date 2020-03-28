#pragma once

#include "common/common.h"
#include "common/string/string_utils.h"
#include "logic/object/object.h"
class dialog_tree;
class world_t;

class coordinates_policy : virtual public object_base
{
public:
  virtual std::string policy_describe () const = 0;
  virtual void policy_build_saveload_tree (saveload::node_t &node) = 0;
  virtual std::vector<interaction> policy_get_interactions () { return {}; }
  };

class simple_coordinates_policy : public coordinates_policy
{
public:
  double get_x () { return m_x; }
  double get_y () { return m_y; }
  double get_z () { return m_z; }
  void move (double dx, double dy, double dz)
  {
    m_x += dx;
    m_y += dy;
    m_z += dz;
  }

  std::string policy_describe () const override
  {
    return string_printf ("My coordinates are (%f; %f; %f)", m_x, m_y, m_z);
  }
  void policy_build_saveload_tree (saveload::node_t &node) override
  {
    saveload::add (node, m_x, "x");
    saveload::add (node, m_y, "y");
    saveload::add (node, m_z, "z");
  }
  bool operator== (const simple_coordinates_policy &other) const
  {
    return !fuzzycmp (m_x, other.m_x) && !fuzzycmp (m_y, other.m_y) && !fuzzycmp (m_z, other.m_z);
  }

private:
  double m_x = 0;
  double m_y = 0;
  double m_z = 5;
};




