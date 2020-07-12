#pragma once

#include "common/common.h"
#include "common/string/string_utils.h"
#include "object/object.h"
class world_t;

class get_focus_policy : virtual public object_base
{
public:
  virtual std::string policy_describe () const = 0;
  virtual void policy_build_saveload_tree (saveload::node_t &node) = 0;
  virtual std::vector<interaction> policy_get_interactions () { return {}; }
  virtual const object_base *get_object_in_focus (const object_heap &level) const = 0;
};

class simple_get_focus_policy : public get_focus_policy
{
public:
  const object_base *get_object_in_focus(const object_heap &level) const override;
  std::string policy_describe () const override
  {
    return string_printf ("Choosing closest object in 5 radius as focus");
  }
  void policy_build_saveload_tree (saveload::node_t &) override {}
  bool operator== (const simple_get_focus_policy &) const { return true; }
};




