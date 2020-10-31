#include "simulation.h"

#include "object/object_heap.h"
#include "tests/simulation/simulation_helpers.h"
#include "world/classes/player.h"
#include "world/classes/dialog_partner.h"
#include "world/world.h"
#include "windows.h"
#include "tchar.h"
#include <fcntl.h>
#include <io.h>
#include <stdio.h>

void run_simulation (bool cont)
{
  SetConsoleOutputCP (CP_UTF8);
  setvbuf(stdout, nullptr, _IOFBF, 1000);

  HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_FONT_INFOEX info;
  memset(&info, 0, sizeof(CONSOLE_FONT_INFOEX));
  info.cbSize = sizeof(CONSOLE_FONT_INFOEX);              // prevents err=87 below
  if (GetCurrentConsoleFontEx(StdOut, FALSE, &info))
    {
      info.FontFamily   = FF_DONTCARE;
      info.dwFontSize.X = 0;  // leave X as zero
      info.dwFontSize.Y = 16;
      info.FontWeight   = 400;
      wcscpy_s(info.FaceName, L"Consolas");
      if (SetCurrentConsoleFontEx(StdOut, FALSE, &info))
        {
        }
    }

  std::string save_name = cont ? "simul_state_con" : "initial_state_con";
  world_t world ("test_story");
  assert_error (world.load (save_name));

  while (true)
    {
      //temp
      //printf ("\nObjects to interact with:\n");

      std::vector<object_base *> objs_on_level = world.get_level ().get_all ();

      std::function<std::string (object_base *const &)> obj_print_func = [] (object_base *const &obj) {
        return obj->get_policy<simple_name_policy> ()->get_name ();
      };

      // temp
      int obj_to_interact_num = 0;
//      int obj_to_interact_num = print_choices_and_get_answer (objs_on_level, obj_print_func, true);
//      if (obj_to_interact_num < 0)
//        break;


      {
        object_base *obj_to_interact = objs_on_level[obj_to_interact_num];

        std::vector<interaction> interactions = obj_to_interact->get_interactions ();
        interactions.insert (interactions.begin (), interaction ("Inspect", [&] (object_base &) {
                               printf ("Description: %s\n", obj_to_interact->describe ().c_str ());
                             }));

        std::function<std::string (const interaction &)> int_print_func
            = [] (const interaction &inter) { return inter.get_name (); };

        // temp
        int interaction_num = 1;
//        int interaction_num = print_choices_and_get_answer (interactions, int_print_func, true);
//        if (interaction_num < 0)
//          break;

        if (obj_to_interact_num >= 0)
          interactions[interaction_num].interact (world.get_player ());
      }

      do_nothing (obj_to_interact_num);

      //temp
      break;
    }

//  assert_error (world.save ("simul_state_con"));
}
