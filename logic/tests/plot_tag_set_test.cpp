#include "logic_tests.h"

#include "common/template_tricks/string_literal.h"
#include "logic/dialog.h"
#include "logic/plot_tag.h"
#include "objects/object_classes/friend.h"

void plot_tag_set_test ()
{
  generic_propset propset;

  propset.set ("mood", "happy");
  propset.set ("blood_type", "a");

  save_and_load_test (propset);

  dialog_tree empty_dialog;
  std::string res1;
  assert_error (from_asset_file (res1, "some_dialog"));
  assert_error (saveload::load (empty_dialog, res1));

  std::string res2;
  assert_error (saveload::save (empty_dialog, res2));
  assert_error (to_asset_file (res2, "some_dialog"));

  object_heap heap;
  friend_t *some_human = heap.allocate_and_get<friend_t> ();
  save_and_load_test (*some_human);

//  moody_human *pc = heap.allocate_and_get<moody_human> ();
//  some_human->get_talked_by (*pc);
}















