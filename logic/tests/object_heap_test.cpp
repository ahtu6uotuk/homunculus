#include "logic_tests.h"

#include "logic/dialog.h"
#include "logic/object/object_heap.h"
#include "logic/object_classes/example_classes.h"

void object_heap_test ()
{
  object_heap heap;

  human *one = heap.allocate_and_get<human> ();
  one->set_hp (11);
  one->set_name ("brian");

  human *two = heap.allocate_and_get<human> (*one);
  two->set_name ("evan");
  assert_check (two->get_hp () == one->get_hp (), "It should have been copyied");

  int three_id = heap.allocate<immortal> ();
  immortal *three = heap.get<immortal> (three_id);
  three->set_name ("ctulhu");

  immortal *four = heap.allocate_and_get<immortal> ();
  four->set_name ("azatot");

  object_heap copy_made_by_saveload = save_and_load_test (heap);

  object_base *three_in_copy_generic = copy_made_by_saveload.get (three_id);
  immortal *three_in_copy_specific = copy_made_by_saveload.get<immortal> (three_id);
  assert_check (three_in_copy_generic == three_in_copy_specific, "These two should return the same");

  three_in_copy_specific->set_name ("hastur");
  assert_check (!(heap == copy_made_by_saveload), "Now they should be different");

  std::string all_objs_description;
  for (object_base *obj : heap.get_all ())
    all_objs_description += obj->describe () + "\n";

//  cout << all_objs_description;
}

