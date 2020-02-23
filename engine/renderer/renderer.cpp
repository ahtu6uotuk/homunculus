#include "renderer.h"
#include <GL/glew.h>
#include "engine/engine.h"
#include "engine/gui/gui_context.h"
#include "engine/renderer/shader.h"


// TODO: remove this function
string test_get_shader_src (const char *fname);
string test_get_shader_src (const char *fname)
{
  ifstream t (fname);
  std::string str;

  t.seekg(0, std::ios::end);
  str.reserve(t.tellg());
  t.seekg(0, std::ios::beg);

  str.assign((std::istreambuf_iterator<char>(t)),
              std::istreambuf_iterator<char>());
  return str;
}

renderer_t::renderer_t (engine_t &engine):
  m_engine (engine),
  m_window (engine.get_sfml_window ()),
  m_gui (engine.get_gui_system ()),
  m_font ("FreeSerif.ttf", 48),
  m_text_shader (nullptr)
{}

#include <glm/common.hpp>
#include <glm/gtc/type_ptr.hpp>
err_t renderer_t::init ()
{
  glewExperimental = GL_TRUE;
  if (glewInit () != GLEW_OK)
    return err_t ("failed to init OpenGL!");

  // TODO: remove this block
  // BLOCK BEGIN
  // ===>>>
  auto vs = subshader_t<GL_VERTEX_SHADER> (test_get_shader_src ("gamedata/shaders/text.vert").c_str ());
  RETURN_IF_FAIL (vs.check_compilation_status ());

  auto fs = subshader_t<GL_FRAGMENT_SHADER> (test_get_shader_src ("gamedata/shaders/text.frag").c_str ());
  RETURN_IF_FAIL (fs.check_compilation_status ());
  m_text_shader = make_unique<shader_t> (
        vs.get_id (),
        fs.get_id ()
        );
  glm::mat4 projection = glm::ortho (0.f, 800.f, 0.f, 600.f);
  RETURN_IF_FAIL (m_text_shader->check_link_status ());

  m_text_shader->use ();
  glUniformMatrix4fv(glGetUniformLocation (m_text_shader->get_program_id (), "projection"), 1, GL_FALSE, glm::value_ptr (projection));
  // <<<===
  // BLOCK END

  glEnable (GL_DEPTH_TEST);
  glEnable (GL_CULL_FACE);
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  auto ret = m_font.load ();
  if (!ret.ok ())
    return ret;

  glViewport (0., 0., 800, 600);

  init_gui_gl_objects ();

  return ERR_OK;
}

void renderer_t::render ()
{
  glClearColor (0., 0., 0., 0.);
  glClear (GL_COLOR_BUFFER_BIT);
  gluOrtho2D (0., 800, 0., 600.);
  m_gui.draw ();
}

void renderer_t::render_text (const string &text, glm::vec2 &pos, glm::vec3 &color, const unsigned int font_size)
{
  m_text_shader->use ();
  glUniform3f (glGetUniformLocation (m_text_shader->get_program_id (), "textColor"), color.r, color.g, color.b);
  m_font.render_text (text, pos.x, pos.y, m_font.get_scale (font_size));
}

renderer_t::~renderer_t ()
{}
