#pragma once

#include "objects/policies/name_policy.h"
#include "objects/policies/plot_tags_policy.h"
#include "objects/policies/talk_policy.h"
#include "objects/policies/health_policy.h"
#include "logic/object/object.h"

class human : public object<
                  human,
                  simple_name_policy,
                  simple_talk_policy<LITERAL ("some_dialog")>,
                  hp_health_policy>
{
public:
  static std::string objtype_name () { return "human"; }
};

class immortal : public object<
                     immortal,
                     simple_name_policy,
                     simple_talk_policy<LITERAL ("some_dialog")>,
                     hit_count_health_policy>
{
public:
  static std::string objtype_name () { return "immortal"; }
};

class other : public object<
                  other,
                  simple_name_policy,
                  simple_talk_policy<LITERAL ("some_dialog")>,
                  hit_count_health_policy>
{
public:
  static std::string objtype_name () { return "other"; }
};
