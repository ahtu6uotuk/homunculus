#include "scene.h"


scene_t::scene_t ()
{
  m_light_sources.emplace_back (point_light_t ({1., 2., 1.}, {1., 0., 0., 0.}));
}

void scene_t::render ()
{

}
