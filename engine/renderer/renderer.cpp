#include "renderer.h"

#include <GL/glew.h>

#include "engine/engine.h"
#include "engine/gui/gui_system.h"


/// @brief Special storage for GL view matrices
/// @details glPushMatrix/glPopMatrix replacement
class matrix_holder_t
{
  glm::mat4 m_gui_view_matrix;
  glm::mat4 m_model_matrix;
  glm::mat4 m_view_matrix;
  glm::mat4 m_projection_matrix;
  glm::mat4 m_mvp_matrix;
public:
  matrix_holder_t () = default;
  const auto &get_model_matrix () const { return m_model_matrix; }
  const auto &get_view_matrix () const { return m_view_matrix; }
  const auto &get_projection_matrix () const { return m_projection_matrix; }
  const auto &get_model_view_projection_matrix () const { return m_mvp_matrix; }
  const auto &get_gui_view_matrix () const { return m_gui_view_matrix; }
  ~matrix_holder_t () = default;
};


renderer_t::renderer_t (engine_t &engine):
  m_window (sf::VideoMode (800, 600, 32), "Homunculus", sf::Style::Default,
            sf::ContextSettings (0, 0, 0, 3, 3, sf::ContextSettings::Attribute::Core)),
  m_gui (engine.get_gui_system ()),
  m_font ("FreeSerif.ttf", 48),
  m_camera (glm::vec3 (0.f, 0.f, 5.f)),
  m_matrix_holder (std::make_unique<matrix_holder_t> ())
{
  m_window.setFramerateLimit (60);
  m_window.requestFocus ();
}

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

  glViewport (0, 0, m_gui.get_width (), m_gui.get_height ());

  glClearColor (0., 0., 1., 0.);

  return ERR_OK;
}

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "gl/gl_ext.h"

void renderer_t::update_matrices ()
{
  auto width = static_cast<float> (m_gui.get_width ());
  auto height = static_cast<float> (m_gui.get_height ());
  m_mat_gui = glm::ortho (0.f, width,
                          0.f, height);
  glm::mat4 projection = glm::perspective (glm::radians (m_camera.get_zoom ()),
                                           width / height,
                                           0.1f, 100.0f);
  glm::mat4 view = m_camera.get_view_matrix ();
  glm::mat4 model_matrix = glm::mat4 (1.);
  m_mat_view = projection * view * model_matrix;
  m_font.update_text_shader_matrix (glm::value_ptr(m_mat_gui));
}

void renderer_t::render ()
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  update_matrices ();

  m_scene.render ();

  //... Draw something here
  for (auto &model : m_drawable_models)
    model.render (m_mat_view);

  glEnable (GL_BLEND);
  m_gui.draw ();
  glDisable (GL_BLEND);
  GL_DEBUG_INFO ();
  m_window.display ();
}

void renderer_t::add_drawable_models (std::vector<model_t> &&drawable_models)
{
  m_drawable_models = std::move (drawable_models);
}

void renderer_t::resize_screen (unsigned int width, unsigned int height)
{
  m_gui.resize (width, height);
  glViewport (0, 0, width, height);
  update_matrices ();
}

renderer_t::~renderer_t ()
{}
