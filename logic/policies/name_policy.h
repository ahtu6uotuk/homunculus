#pragma once
#include <iostream>

#include "common/common.h"
#include "common/string/string_utils.h"
#include "logic/object/object.h"
#include "logic/saveload/saveload.h"

class name_policy : virtual public object_base
{
public:
  virtual string policy_describe () const = 0;
  virtual void policy_build_saveload_tree (saveload_node &node) = 0;
  vector<interaction> policy_get_interactions () { return {}; }

  virtual string get_name () = 0;
};



class simple_name_policy : public name_policy
{
public:
  bool operator== (const simple_name_policy &other) const { return m_name == other.m_name; }
  string policy_describe() const override { return string_printf ("Name: %s", m_name.c_str ()); }
  void policy_build_saveload_tree (saveload_node &node) override
  {
    node.add (m_name, "name");
  }

  string get_name () override { return m_name; }
  void set_name (const string &name) { m_name = name; }

private:
  string m_name;
};
