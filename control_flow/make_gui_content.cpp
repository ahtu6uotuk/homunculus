#include "make_gui_content.h"

#include "engine/engine.h"
#include "logic/world.h"
#include "logic/policies/get_text_for_gui_policy.h"
#include "engine/gui/gui_textline.h"
#include "engine/gui/gui_context.h"
#include "common/thread_info.h"

void make_gui_content (engine_t &engine, world_t &world, thread_info_t &thr_info, unique_ptr<gui_context_t> &result)
{
  // TODO: this should be parallel
  if (!thr_info.is_main_thread ())
    return;

  unique_ptr<gui_context_t> local_result = make_unique<gui_context_t> (engine.get_gui_system ());
  vector<object_base *> objs = world.get_all ();

  for (object_base *obj : objs)
    {
      {
        get_text_for_gui_policy *pl = obj->get_policy<get_text_for_gui_policy> ();
        if (pl)
          local_result->add_element (make_unique<gui_textline_t> (
              engine.get_renderer (), 10, 10, gui_horizontal_alignment_t::LEFT,
              gui_vertical_alignment_t::DOWN, pl->get_text (), glm::vec3 (.7f, .15f, .15f), 48));
      }
      // other types of gui elements here...
    }

  result = move (local_result);
}
