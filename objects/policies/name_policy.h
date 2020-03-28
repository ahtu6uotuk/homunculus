#pragma once
#include <iostream>

#include "common/common.h"
#include "common/string/string_utils.h"
#include "logic/object/object.h"
#include "logic/saveload/saveload.h"

class name_policy : virtual public object_base
{
public:
  virtual std::string policy_describe () const = 0;
  virtual void policy_build_saveload_tree (saveload::node_t &node) = 0;
  std::vector<interaction> policy_get_interactions () { return {}; }

  virtual std::string get_name () = 0;
};



class simple_name_policy : public name_policy
{
public:
  bool operator== (const simple_name_policy &other) const { return m_name == other.m_name; }
  std::string policy_describe() const override { return string_printf ("Name: %s", m_name.c_str ()); }
  void policy_build_saveload_tree (saveload::node_t &node) override
  {
    saveload::add (node, m_name, "name");
  }

  std::string get_name () override { return m_name; }
  void set_name (const std::string &name) { m_name = name; }

private:
  std::string m_name;
};
