#include "logic_tests.h"

#include "common/template_tricks/string_literal.h"
#include "datastructs/dialog.h"
#include "datastructs/plot_tag.h"
#include "world/classes/friend.h"

void plot_tag_set_test ()
{
  generic_propset propset;

  propset.set ("mood", "happy");
  propset.set ("blood_type", "a");

  save_and_load_test (propset);

  dialog_tree empty_dialog;
  std::string res1;
  assert_error (from_gamedata_file (res1, "assets/some_dialog.xml"));
  assert_error (saveload::load (empty_dialog, res1));

  std::string res2;
  assert_error (saveload::save (empty_dialog, res2));
  assert_error (to_gamedata_file (res2, "assets/some_dialog.xml"));

  object_heap heap;
  friend_t *some_human = heap.allocate_and_get<friend_t> ();
  save_and_load_test (*some_human);

//  moody_human *pc = heap.allocate_and_get<moody_human> ();
//  some_human->get_talked_by (*pc);
}















