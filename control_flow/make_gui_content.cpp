#include "make_gui_content.h"

#include "engine/engine.h"
#include "world/world.h"
#include "world/policies/get_text_for_gui_policy.h"
#include "world/policies/camera_policy.h"
#include "engine/gui/gui_textline.h"
#include "engine/gui/gui_context.h"
#include "common/thread_info.h"
#include "control_flow/request_to_gui.h"
#include "control_flow/request_to_calc.h"
#include "world/policies/shader_policy.h"
#include "world/policies/mesh_policy.h"
#include "world/policies/texture_policy.h"

void make_gui_content (engine_t &engine, world_t &world, thread_info_t &thr_info, std::vector<std::unique_ptr<request_to_gui_base>> &result)
{
  // TODO: this should be parallel
  if (!thr_info.is_main_thread ())
    return;

  std::unique_ptr<gui_context_t> new_content = std::make_unique<gui_context_t> (engine.get_gui_system ());
  std::vector<object_base *> objs = world.get_all ();

  struct model_info
  {
    shader_t *shader;
    mesh_t *mesh;
    texture_t *texture;
  };
  std::vector<model_info> all_models;

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

      {
        mesh_policy *m_p = obj->get_policy<mesh_policy> ();
        shader_policy *s_p = obj->get_policy<shader_policy> ();
        texture_policy *t_p = obj->get_policy<texture_policy> ();

        assert_check ((m_p && s_p && t_p) || (!m_p && !s_p && !t_p), "Object should have either all of these or none");
        if (!m_p)
          continue;

        model_info model = {s_p->get_shader (), m_p->get_mesh (), t_p->get_texture ()};
        assert_check (model.shader && model.mesh && model.texture, "Sanity");
        all_models.push_back (model);
      }
    }

  assert_check (all_models.size () >= 1, "At least one object with a model");
  model_info model = all_models[0];

  result.clear ();
  result.emplace_back (
      new request_to_gui_t ([new_content = move (new_content), model = std::move (model), &world] (engine_t &eng) mutable -> err_t {
        simple_camera_policy *coord = world.get_player ().get_policy<simple_camera_policy> ();

        eng.get_renderer ().get_gui ().set_world_content (move (new_content));
        eng.get_renderer ().get_camera ().set_current_data (coord->get ());
        eng.get_renderer ().set_mesh (model.mesh, model.shader, model.texture);
        return ERR_OK;
      }));
}
