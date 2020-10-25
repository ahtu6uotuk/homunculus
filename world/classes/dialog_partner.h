#pragma once

#include "datastructs/dialog.h"
#include "object/object.h"
#include "world/policies/name_policy.h"
#include "world/policies/plot_tags_policy.h"
#include "world/policies/talk_policy.h"

class dialog_partner_t
  : public object<
        dialog_partner_t,
        simple_name_policy,
        string_tags_policy,
        simple_talk_policy<LITERAL ("assets/some_dialog.xml")>
        >
{
public:
  static std::string objtype_name () { return "dialog_partner"; }
};
