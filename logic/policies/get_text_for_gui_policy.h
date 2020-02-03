#pragma once
#include <iostream>

#include "common/common.h"
#include "common/string/string_utils.h"
#include "logic/object/object.h"
#include "logic/saveload/saveload.h"

class get_text_for_gui_policy : virtual public object_base
{
public:
  virtual string policy_describe () const = 0;
  virtual void policy_build_saveload_tree (saveload_node &node) = 0;
  vector<interaction> policy_get_interactions () { return {}; }

  virtual string get_text () const = 0;
};

class simple_get_text_for_gui_policy : public get_text_for_gui_policy
{
public:
  bool operator== (const simple_get_text_for_gui_policy &other) const { return get_text () == other.get_text (); }
  string policy_describe() const override { return string_printf ("Describes himself for gui"); }
  void policy_build_saveload_tree (saveload_node &) override {}

  string get_text () const override { return describe (); }
};
