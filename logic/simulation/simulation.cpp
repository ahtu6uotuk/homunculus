#include "simulation.h"

#include "logic/object/object_heap.h"
#include "logic/simulation/simulation_helpers.h"
#include "logic/world.h"
#include "objects/object_classes/enemy.h"
#include "objects/object_classes/friend.h"

void  run_simulation (bool cont)
{
  world_t world ("test_story");

  std::string save_name = cont ? "simulation_state" : "initial_state";
  assert_error (world.load (save_name));

  while (true)
    {
      printf ("\nObjects to interact with:\n");

      std::vector<object_base *> objs_on_level = world.get_level ().get_all ();

      std::function<std::string (object_base *const &)> obj_print_func = [] (object_base *const &obj) {
        return obj->get_policy<simple_name_policy> ()->get_name ();
      };

      int obj_to_interact_num = print_choices_and_get_answer (objs_on_level, obj_print_func, true);
      if (obj_to_interact_num < 0)
        break;

      {
        object_base *obj_to_interact = objs_on_level[obj_to_interact_num];

        std::vector<interaction> interactions = obj_to_interact->get_interactions ();
        interactions.insert (interactions.begin (), interaction ("Inspect", [&] (object_base &) {
                               printf ("Description: %s\n", obj_to_interact->describe ().c_str ());
                             }));

        std::function<std::string (const interaction &)> int_print_func
            = [] (const interaction &inter) { return inter.get_name (); };

        int interaction_num = print_choices_and_get_answer (interactions, int_print_func, true);
        if (interaction_num < 0)
          break;

        if (obj_to_interact_num >= 0)
          interactions[interaction_num].interact (world.get_player ());
      }

      do_nothing (obj_to_interact_num);
    }

  assert_error (world.save ("simulation_state"));
}
