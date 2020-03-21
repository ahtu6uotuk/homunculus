#pragma once

#include "common/common.h"
#include "common/string/string_utils.h"
#include "logic/object/object.h"
class dialog_tree;
class world_t;
class action;

class choose_action_policy : virtual public object_base
{
public:
  virtual std::string policy_describe () const = 0;
  virtual void policy_build_saveload_tree (saveload_node &node) = 0;
  virtual std::vector<interaction> policy_get_interactions () { return {}; }

  virtual std::unique_ptr<action> get_action (world_t &world) = 0;
};














