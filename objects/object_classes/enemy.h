#pragma once

#include "common/common.h"
#include "logic/object/object.h"

#include "objects/policies/name_policy.h"
#include "objects/policies/health_policy.h"
#include "objects/policies/plot_tags_policy.h"
#include "objects/policies/get_text_for_gui_policy.h"

class enemy_t : public object<
                    enemy_t,
                    simple_name_policy,
                    simple_get_text_for_gui_policy,
                    hp_health_policy>
{
public:
  static std::string objtype_name () { return "enemy"; }
};
