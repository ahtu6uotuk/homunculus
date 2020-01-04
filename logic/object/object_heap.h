#pragma once
#include <memory>
#include <unordered_map>
#include <functional>

#include "logic/saveload.h"

class object_heap;
struct obj_heap_helper { vector<function<void (object_heap &)>> m_type_adders; };
extern obj_heap_helper object_heap_helper_singleton;

class object_heap
{
public:
  object_heap ();

  vector<object_base *> get_all ();
  object_base *get (int id);
  void build_saveload_tree (saveload_node &node);

  template<typename T, typename... ConstructorArgs>
  T *allocate_and_get (ConstructorArgs... constructor_args)
  {
    return get<T> (allocate<T> (forward<ConstructorArgs> (constructor_args)...));
  }

  template<typename T, typename ... ConstructorArgs>
  int allocate (ConstructorArgs ... constructor_args)
  {
    string name_of_type = T::objtype_name ();
    assert_check (m_obj_maps.count (name_of_type), "Object type not registered!");

    obj_map_base *corresp_vector = m_obj_maps[name_of_type].get ();
    obj_map<T> *typed_vector = dynamic_cast<obj_map<T> *> (corresp_vector);
    unique_ptr<T> created_obj = make_unique<T> (forward<ConstructorArgs> (constructor_args)...);
    typed_vector->m_data[++m_max_id] = move (created_obj);
    return m_max_id;
  }

  template<typename T>
  T *get (int id)
  {
    string name_of_type = T::objtype_name ();
    assert_check (m_obj_maps.count (name_of_type), "Object type not registered!");

    return dynamic_cast<T *> (m_obj_maps[name_of_type]->get_by_id (id));
  }

  bool operator== (const object_heap &other) const;

private:
  struct obj_map_base;
  unordered_map<string, unique_ptr<obj_map_base>> m_obj_maps;
  int m_max_id = -1;

private:
  struct obj_map_base
  {
    virtual ~obj_map_base () {};
    virtual bool operator== (const obj_map_base &other) = 0;
    virtual vector<object_base *> get_all () = 0;
    virtual object_base *get_by_id (int id) = 0;
    virtual void add_to_tree (saveload_node &node) = 0;
  };

  template<typename T>
  struct obj_map : obj_map_base
  {
    virtual ~obj_map () {};

    virtual vector<object_base *> get_all () override
    {
      vector<object_base *> res;
      for (pair<const int, unique_ptr<T>> &it : m_data)
        res.push_back (it.second.get ());
      return res;
    }

    virtual bool operator== (const obj_map_base &other) override
    {
      const obj_map<T> *typed_other = dynamic_cast<const obj_map<T> *> (&other);
      if (!typed_other)
        return false;
      for (const pair<const int, unique_ptr<T>> &it : m_data)
        {
          auto other_it = typed_other->m_data.find (it.first);
          if (other_it == typed_other->m_data.end ())
            return false;
          if (!uptrs_are_equal (it.second, other_it->second))
            return false;
        }
      return true;
    }

    virtual object_base *get_by_id (int id) override
    {
      return m_data.count (id) ? m_data[id].get () : nullptr;
    }

    virtual void add_to_tree (saveload_node &node) override
    {
      node.add (m_data, T::objtype_name ());
    }

    unordered_map<int, unique_ptr<T>> m_data;
  };

  template<typename T>
  void add_type ()
  {
    string name_of_type = T::objtype_name ();
    assert_check (!m_obj_maps.count (name_of_type), "Object type name is copy-pasted!");
    m_obj_maps.insert ({name_of_type, make_unique<obj_map<T>> ()});
  }
  template<typename Self, typename... Args> friend class object;
};
