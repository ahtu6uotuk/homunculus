#pragma once
#include <iostream>

#include "common/common.h"
#include "common/string/string_utils.h"
#include "logic/object/object.h"
#include "logic/saveload.h"

/// All classes probably should have this policy.
/// Its convenient for objects to have a name.
class name_policy : virtual public object_base
{
public:
  virtual string describe_policy () const = 0;
  virtual void build_saveload_tree_policy (saveload_node &node) = 0;

  virtual string get_name () = 0;
};



class simple_name_policy : public name_policy
{
public:
  bool operator== (const simple_name_policy &other) const { return m_name == other.m_name; }
  string describe_policy() const override { return string_printf ("Name: %s\n", m_name.c_str ()); }
  void build_saveload_tree_policy (saveload_node &node) override
  {
    node.add (m_name, "name");
  }

  string get_name () override { return m_name; }
  void set_name (const string &name) { m_name = name; }

private:
  string m_name;
};
