#include "renderer.h"

#include <GL/glew.h>

#include "engine/engine.h"
#include "engine/gui/gui_context.h"
#include "datastructs/mesh.h"
#include "datastructs/shader.h"

renderer_t::renderer_t (engine_t &engine):
  m_engine (engine),
  m_window (engine.get_sfml_window ()),
  m_gui (engine.get_gui_system ()),
  m_font ("FreeSerif.ttf", 48),
  m_camera (glm::vec3 (0.f, 0.f, 5.f))
{}

err_t renderer_t::init ()
{
  glewExperimental = GL_TRUE;
  if (glewInit () != GLEW_OK)
    return err_t ("failed to init OpenGL!");

  glEnable (GL_DEPTH_TEST);
  glDepthFunc (GL_LESS);
  glEnable (GL_CULL_FACE);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  auto ret = m_font.load ();
  if (!ret.ok ())
    return ret;

  glViewport (0., 0., 800, 600);

  glClearColor (0., 0., 1., 0.);

  return ERR_OK;
}

#include <glm/gtc/matrix_transform.hpp>
#include "gl/gl_ext.h"

void renderer_t::update_matrices ()
{
  m_mat_gui = glm::ortho (0.f, 800.f, 0.f, 600.f); // unused now
  glm::mat4 projection = glm::perspective (glm::radians (45.f), 800.f / 600.f, 0.1f, 100.0f);
  glm::mat4 view = m_camera.get_view_matrix ();
  glm::mat4 model_matrix = glm::mat4 (1.);
  m_mat_view = projection * view * model_matrix;
}

void renderer_t::render ()
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  update_matrices ();

  //... Draw something here
  for (auto &model : m_drawable_models)
    model.render (m_mat_view);

  glEnable (GL_BLEND);
  m_gui.draw ();
  glDisable (GL_BLEND);
  GL_DEBUG_INFO ();
}

void renderer_t::add_drawable_models (std::vector<model_t> &&drawable_models)
{
  m_drawable_models = std::move (drawable_models);
}

renderer_t::~renderer_t ()
{}
