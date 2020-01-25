#include "object_heap.h"

obj_heap_helper object_heap_helper_singleton;

object_heap::object_heap ()
{
  for (auto type_adder : object_heap_helper_singleton.m_type_adders)
    type_adder (*this);
}

bool object_heap::operator== (const object_heap & other) const
{
  if (m_max_id != other.m_max_id)
    return false;

  for (const pair<const string, unique_ptr<obj_map_base>> &it : m_obj_maps)
    {
      auto other_it = other.m_obj_maps.find (it.first);
      if (other_it == other.m_obj_maps.end ())
        return false;
      if (!uptrs_are_equal (it.second, other_it->second))
        return false;
    }

  return true;
}

vector<object_base *> object_heap::get_all ()
{
  vector <object_base *> res;

  for (pair<const string, unique_ptr<obj_map_base>> &it : m_obj_maps)
    {
      vector<object_base *> part = it.second->get_all ();
      res.insert (res.end (), part.begin (), part.end ());
    }
  return res;
}

object_base *object_heap::get (int id)
{
  for (pair<const string, unique_ptr<obj_map_base>> &it : m_obj_maps)
    if (it.second->get_by_id (id))
      return it.second->get_by_id (id);
  return nullptr;
}

void object_heap::build_saveload_tree (saveload_node &node)
{
  node.add (m_max_id, "max_id");
  for (pair<const string, unique_ptr<obj_map_base>> &it : m_obj_maps)
    it.second->add_to_tree (node);
}
