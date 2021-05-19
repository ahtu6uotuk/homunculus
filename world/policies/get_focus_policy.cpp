#include "get_focus_policy.h"

#include "world/policies/position_policy.h"
#include <glm/geometric.hpp>
#include <optional>

const object_base *simple_get_focus_policy::get_object_in_focus (const object_heap &level) const
{
  const position_policy_t *this_pos = get_policy<position_policy_t> ();
  if (!this_pos)
    return nullptr;

  std::optional<double> best_distance = std::nullopt;
  const object_base *best_distance_obj_id = nullptr;
  std::vector<const object_base *> all_objs = level.get_all ();

  for (const object_base *obj : all_objs)
    {
      if (obj == this)
        continue;

      const position_policy_t *pos = obj->get_policy<position_policy_t> ();

      if (!pos)
        continue;

      double distance = glm::distance (this_pos->get_position (), pos->get_position ());
      if (!best_distance || distance < *best_distance)
        {
          best_distance = distance;
          best_distance_obj_id = obj;
        }
    }

  if (!best_distance)
    return nullptr;

  if (*best_distance > 5)
    return nullptr;

  return best_distance_obj_id;
}
