#pragma once
#include <iostream>

#include "common/common.h"
#include "common/string/string_utils.h"
#include "object/object.h"
#include "resource/saveload/saveload.h"

class get_text_for_gui_policy : virtual public object_base
{
public:
  virtual std::string policy_describe () const = 0;
  virtual void policy_build_saveload_tree (saveload::node_t &node) = 0;
  std::vector<interaction> policy_get_interactions () { return {}; }

  virtual std::string get_text () const = 0;
};

class simple_get_text_for_gui_policy : public get_text_for_gui_policy
{
public:
  bool operator== (const simple_get_text_for_gui_policy &other) const { return get_text () == other.get_text (); }
  std::string policy_describe() const override { return string_printf ("Describes himself for gui"); }
  void policy_build_saveload_tree (saveload::node_t &) override {}

  std::string get_text () const override { return describe (); }
};
