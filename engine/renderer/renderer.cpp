#include "renderer.h"

#include <GL/glew.h>

#include "engine/engine.h"
#include "engine/gui/gui_context.h"
#include "datastructs/mesh.h"
#include "engine/renderer/shader.h"

renderer_t::renderer_t (engine_t &engine):
  m_engine (engine),
  m_window (engine.get_sfml_window ()),
  m_gui (engine.get_gui_system ()),
  m_font ("FreeSerif.ttf", 48),
  m_camera (glm::vec3 (0.f, 0.f, 5.f)),
  m_test_mesh (nullptr)
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

  return ERR_OK;
}

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "gl/gl_ext.h"
void renderer_t::render ()
{
  glClearColor (0., 0., 1., 0.);
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //... Draw something here
  m_test_shader->use ();
  glm::mat4 projection = glm::perspective (glm::radians (45.f), 800.f / 600.f, 0.1f, 100.0f);
  glm::mat4 view = m_camera.get_view_matrix ();
  glm::mat4 model_matrix = glm::mat4 (1.);
  glm::mat4 mvp = projection * view * model_matrix;
  m_test_shader->set_uniform_mat4 ("MVP", glm::value_ptr (mvp));

  glActiveTexture (GL_TEXTURE0);

  glBindTexture (GL_TEXTURE_2D, m_tex);

  m_test_shader->set_uniform_1i ("myTextureSampler", 0);

  m_test_mesh->draw ();
//  glEnable (GL_BLEND);
//  m_gui.draw ();
//  glDisable (GL_BLEND);
  GL_DEBUG_INFO (nullptr);
}

void renderer_t::set_mesh (mesh_t *test, shader_t *shader, unsigned int tex)
{
  m_test_mesh = test;
  m_test_mesh->print_debug_info ();
  m_test_shader = shader;
  m_tex = static_cast<int> (tex);
}

renderer_t::~renderer_t ()
{}
