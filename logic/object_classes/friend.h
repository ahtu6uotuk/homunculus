#pragma once

#include "logic/policies/name_policy.h"
#include "logic/policies/plot_tags_policy.h"
#include "logic/policies/talk_policy.h"
#include "logic/policies/health_policy.h"
#include "logic/policies/get_text_for_gui_policy.h"
#include "logic/object/object.h"
#include "logic/dialog.h"

enum class mood { happy, sad, melancholic, COUNT };
const char *enum_to_string (mood m);
enum class bloodtype { o, a, b, ab, COUNT };
const char *enum_to_string (bloodtype m);

typedef plot_tag_set<
    named_enum<LITERAL ("mood"), mood>,
    named_enum<LITERAL ("blood_type"), bloodtype>>
    generic_propset;

class friend_t
  : public object<
        friend_t,
        simple_name_policy,
        simple_get_text_for_gui_policy,
        simple_plot_tags_policy<named_enum<LITERAL ("mood"), mood>, named_enum<LITERAL ("blood_type"), bloodtype>>,
        simple_talk_policy<LITERAL ("some_dialog")>>
{
public:
  static std::string objtype_name () { return "friend"; }
};
