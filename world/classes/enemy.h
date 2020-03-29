#pragma once

#include "common/common.h"
#include "object/object.h"
#include "world/policies/get_text_for_gui_policy.h"
#include "world/policies/health_policy.h"
#include "world/policies/name_policy.h"
#include "world/policies/plot_tags_policy.h"

class enemy_t : public object<
                    enemy_t,
                    simple_name_policy,
                    simple_get_text_for_gui_policy,
                    hp_health_policy>
{
public:
  static std::string objtype_name () { return "enemy"; }
};
