#include "make_gui_content.h"

#include "engine/engine.h"
#include "logic/world.h"
#include "logic/policies/get_text_for_gui_policy.h"
#include "logic/policies/coordinates_policy.h"
#include "engine/gui/gui_textline.h"
#include "engine/gui/gui_context.h"
#include "common/thread_info.h"
#include "control_flow/request_to_gui.h"
#include "control_flow/request_to_calc.h"

void make_gui_content (engine_t &engine, world_t &world, thread_info_t &thr_info, std::vector<std::unique_ptr<request_to_gui_base>> &result)
{
  // TODO: this should be parallel
  if (!thr_info.is_main_thread ())
    return;

  std::unique_ptr<gui_context_t> new_content = std::make_unique<gui_context_t> (engine.get_gui_system ());
  std::vector<object_base *> objs = world.get_all ();

  int i = 0;
  for (object_base *obj : objs)
    {
      {
        name_policy *pl = obj->get_policy<name_policy> ();
        if (pl)
          new_content->add_element (std::make_unique<gui_textline_t> (
              engine.get_renderer (), 10, ++i * 24, gui_horizontal_alignment_t::LEFT,
              gui_vertical_alignment_t::DOWN, pl->get_name (), glm::vec3 (.7f, .15f, .15f), 24));
      }
      // other types of gui elements here...
    }

  result.clear ();
  result.emplace_back (
      new request_to_gui_t ([new_content = move (new_content), &world] (engine_t &eng) mutable -> err_t {
        simple_coordinates_policy *coord = world.get_player ().get_policy<simple_coordinates_policy> ();

        eng.get_renderer ().get_gui ().set_world_content (move (new_content));
        eng.get_renderer ().get_camera ().set_position (coord->get_x (), coord->get_y (), coord->get_z ());
        return ERR_OK;
      }));
}
