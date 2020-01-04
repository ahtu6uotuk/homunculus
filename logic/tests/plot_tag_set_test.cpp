#include "logic_tests.h"

#include "common/template_tricks/string_literal.h"
#include "logic/dialog.h"
#include "logic/plot_tag.h"
#include "logic/policies/plot_tags_policy.h"
#include "logic/policies/talk_policy.h"

enum class mood
{
  happy,
  sad,
  melancholic,
  COUNT
};

const char *enum_to_string (mood m);
const char *enum_to_string (mood m)
{
  switch (m)
    {
    case mood::happy:
      return "happy";
    case mood::sad:
      return "sad";
    case mood::melancholic:
      return "melancholic";
    case mood::COUNT:
      return "";
    }
  return "";
}

enum class bloodtype
{
  o,
  a,
  b,
  ab,
  COUNT
};

const char *enum_to_string (bloodtype m);
const char *enum_to_string (bloodtype m)
{
  switch (m)
    {
    case bloodtype::o:
      return "o";
    case bloodtype::a:
      return "a";
    case bloodtype::b:
      return "b";
    case bloodtype::ab:
      return "ab";
    case bloodtype::COUNT:
      return "";
    }
  return "";
}

typedef plot_tag_set<
    named_enum<LITERAL ("mood"), mood>,
    named_enum<LITERAL ("blood_type"), bloodtype>>
    generic_propset;

class moody_human
  : public object<
        moody_human,
        simple_plot_tags_policy<named_enum<LITERAL ("mood"), mood>, named_enum<LITERAL ("blood_type"), bloodtype>>,
        simple_talk_policy<LITERAL ("some_dialog")>>
{
public:
  static std::string objtype_name () { return "moody_human"; }
};

void plot_tag_set_test ()
{
  generic_propset propset;

  propset.set ("mood", "happy");
  propset.set ("blood_type", "a");

  save_and_load_test (propset);

  dialog_tree empty_dialog;
  string res1;
  assert_error (from_asset_file (res1, "some_dialog"));
  assert_error (load (empty_dialog, res1));

  string res2;
  assert_error (save (empty_dialog, res2));
  assert_error (to_asset_file (res2, "some_dialog"));

  object_heap heap;
  moody_human *some_human = heap.allocate_and_get<moody_human> ();
  save_and_load_test (*some_human);

  /// uncomment to talk to guy in terminal
//  moody_human *pc = heap.allocate_and_get<moody_human> ();
//  some_human->talk (*pc);
}















