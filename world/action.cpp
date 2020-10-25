#include "action.h"

#include "world/world.h"
#include "world/policies/camera_policy.h"
#include "world/policies/position_policy.h"

void action::exec (int actor_id, world_t &world)
{
  object_base *actor = world.get_by_id (actor_id);
  if (!actor)
    return; // actor is no longer in this world and cannot act

  exec_impl (*actor, world);
}


void move_action::exec_impl (object_base &actor, world_t &)
{
  simple_camera_policy *cam = actor.get_policy<simple_camera_policy> ();
  position_policy_t *coord = actor.get_policy<position_policy_t> ();
  assert_check (cam && coord, "How do i move without coord policy, I dunno");

  switch (m_direction)
    {
    case movement_direction_t::FORWARD:
      coord->get_position () += cam->get ().m_orientation_front * m_dt * m_speed;
      break;
    case movement_direction_t::BACKWARD:
      coord->get_position () -= cam->get ().m_orientation_front * m_dt * m_speed;
      break;
    case movement_direction_t::LEFT:
      coord->get_position () -= cam->get ().m_orientation_right * m_dt * m_speed;
      break;
    case movement_direction_t::RIGHT:
      coord->get_position () += cam->get ().m_orientation_right * m_dt * m_speed;
      break;
    }
}

void rotate_action::exec_impl (object_base &actor, world_t &)
{
  simple_camera_policy *coord = actor.get_policy<simple_camera_policy> ();
  assert_check (coord, "How do i move without coord policy, I dunno");

  coord->get ().rotate (m_yaw, m_pitch);
}
