#pragma once

#include "object/object.h"
#include "datastructs/dialog.h"
#include "world/policies/health_policy.h"
#include "world/policies/name_policy.h"
#include "world/policies/plot_tags_policy.h"
#include "world/policies/talk_policy.h"

enum class mood { happy, sad, melancholic, COUNT };
const char *enum_to_string (mood m);
enum class bloodtype { o, a, b, ab, COUNT };
const char *enum_to_string (bloodtype m);

typedef plot_tag_set<
    named_enum<LITERAL ("mood"), mood>,
    named_enum<LITERAL ("blood_type"), bloodtype>>
    generic_propset;

class human : public object<
                  human,
                  simple_name_policy,
                  simple_plot_tags_policy<named_enum<LITERAL ("mood"), mood>, named_enum<LITERAL ("blood_type"), bloodtype>>,
                  simple_talk_policy<LITERAL ("assets/some_dialog.xml")>,
                  hp_health_policy>
{
public:
  static std::string objtype_name () { return "human"; }
};

class immortal : public object<
                     immortal,
                     simple_name_policy,
                     simple_talk_policy<LITERAL ("assets/some_dialog.xml")>,
                     hit_count_health_policy>
{
public:
  static std::string objtype_name () { return "immortal"; }
};

class other : public object<
                  other,
                  simple_name_policy,
                  simple_talk_policy<LITERAL ("assets/some_dialog.xml")>,
                  hit_count_health_policy>
{
public:
  static std::string objtype_name () { return "other"; }
};
