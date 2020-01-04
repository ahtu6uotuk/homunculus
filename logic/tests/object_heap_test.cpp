#include "logic_tests.h"

#include "logic/policies/example/health_policy.h"
#include "logic/policies/example/talk_policy.h"
#include "logic/policies/example/name_policy.h"
#include "logic/object/object_heap.h"

/// these three classes below are composed from "policies" -
/// component classes, which can be reused between different types of objects.
/// For example, classes "wall" and "enemy" should both have coordinates,
/// and classes "npc" and "enemy" both have hp.
/// If we use policies, we can avoid code duplication.
class human : public object<
                  human,
                  simple_name_policy,
                  about_health_talk_policy,
                  hp_health_policy>
{
public:
  /// You need to define this function when making a new object subtype
  static string objtype_name () { return "human"; }
};

class immortal : public object<
                     immortal,
                     simple_name_policy,
                     weather_talk_policy,
                     immortal_bragging_health_policy>
{
public:
  static string objtype_name () { return "immortal"; }
};

class other : public object<
                  other,
                  simple_name_policy,
                  weather_talk_policy,
                  immortal_bragging_health_policy>
{
public:
  static string objtype_name () { return "other"; }
};


void object_heap_test ()
{
  /// Heap owns all of the objects. It should be used to create them.
  /// If we store all objects there, we will have no trobles with save-load,
  /// and with memory management.
  object_heap heap;

  /// This is how you can trivially create an object.
  human *one = heap.allocate_and_get<human> ();
  /// Human has function "set hp", because it has hp_health_policy.
  /// class immortal does not have it.
  one->set_hp (11);
  one->set_name ("brian");

  /// You can pass constructor arguments to "allocate_and_get".
  /// Here we copy the previous human.
  human *two = heap.allocate_and_get<human> (*one);
  two->set_name ("evan");
  assert_check (two->get_hp () == one->get_hp (), "It should have been copyied");

  /// Heap tracks ids of all allocated objects.
  /// If you need to store the object, store its id.
  /// That way you can check if object is still on the heap, or is it deleted.
  int three_id = heap.allocate<immortal> ();
  immortal *three = heap.get<immortal> (three_id);
  three->set_name ("ctulhu");

  immortal *four = heap.allocate_and_get<immortal> ();
  four->set_name ("azatot");

  /// You can save heap, load it, and compare two heaps.
  object_heap copy_made_by_saveload = save_and_load_test (heap);

  /// You can get generic object by non-template function
  object_base *three_in_copy_generic = copy_made_by_saveload.get (three_id);
  /// Or you can get typed object by using template function
  immortal *three_in_copy_specific = copy_made_by_saveload.get<immortal> (three_id);
  assert_check (three_in_copy_generic == three_in_copy_specific, "These two should return the same");

  three_in_copy_specific->set_name ("hastur");
  assert_check (!(heap == copy_made_by_saveload), "Now they should be different");

  string all_objs_description;
  /// Object can describe itself, calling "describe" for all its policies.
  for (object_base *obj : heap.get_all ())
    all_objs_description += obj->describe () + "\n";

  /// Uncomment if you want to take a look at the description of all objects.
//  cout << all_objs_description;
}

