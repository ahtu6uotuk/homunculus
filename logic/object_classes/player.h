#pragma once

#include "common/common.h"
#include "logic/object/object.h"

#include "logic/policies/name_policy.h"
#include "logic/policies/plot_tags_policy.h"

class player_t : public object<player_t, simple_name_policy>
{
public:
  static string objtype_name () { return "player"; }
};
