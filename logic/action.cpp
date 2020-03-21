#include "action.h"

#include "logic/world.h"
#include "logic/policies/coordinates_policy.h"

void action::exec (int actor_id, world_t &world)
{
  object_base *actor = world.get_by_id (actor_id);
  if (!actor)
    return; // actor is no longer in this world and cannot act

  exec_impl (*actor, world);
}


void move_action::exec_impl (object_base &actor, world_t &)
{
  simple_coordinates_policy *coord = actor.get_policy<simple_coordinates_policy> ();
  assert_check (coord, "How do i move without coord policy, I dunno");

  coord->move (m_dx, m_dy, m_dz);
}
