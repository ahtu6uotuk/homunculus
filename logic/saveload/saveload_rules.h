#pragma once

#include "logic/saveload/saveload_tree.h"

namespace saveload
{
namespace rules
{
/// primitives
inline void add_impl (node_t &node, double &data, const std::string &name)
{
  node.add_primitive (data, name);
}
inline void add_impl (node_t &node, int &data, const std::string &name)
{
  node.add_primitive (data, name);
}
inline void add_impl (node_t &node, std::string &data, const std::string &name)
{
  node.add_primitive (data, name);
}
inline void add_impl (node_t &node, bool &data, const std::string &name)
{
  node.add_primitive (data, name);
}

/// pair
template<typename Type1, typename Type2>
void add_impl (node_t &node, std::pair<Type1, Type2> &data, const std::string &name)
{
  node.spawn_empty_child (name);
  add (node.last_child (), data.first, "first");
  add (node.last_child (), data.second, "second");
}

/// vector
template<typename VectElem>
void add_impl (node_t &node, std::vector<VectElem> &data, const std::string &name)
{
  std::string elem_name = "elem";
  node.add_container<std::vector<VectElem>, VectElem> (data, name, elem_name);
  for (VectElem &elem : data)
    add (node.last_child (), elem, elem_name);
}
template<typename VectElem>
void add_elem_impl (std::vector<VectElem> &data, std::unique_ptr<VectElem> elem_to_add_impl)
{
  data.push_back (std::move (*elem_to_add_impl));
}

/// map
template<typename MapKey, typename MapValue>
void add_impl (node_t &node, std::unordered_map<MapKey, MapValue> &data, const std::string &name)
{
  std::string elem_name = "entry";
  node.add_container<std::unordered_map<MapKey, MapValue>, std::pair<MapKey, MapValue>> (data, name, elem_name);

  std::vector<std::pair<const MapKey, MapValue> *> ordered_pairs;
  for (std::pair<const MapKey, MapValue> &elem : data)
    ordered_pairs.push_back (&elem);

  sort (ordered_pairs.begin (), ordered_pairs.end (), [] (auto a, auto b) {
    return a->first < b->first;
  });

  for (std::pair<const MapKey, MapValue> *elem : ordered_pairs)
    {
      std::pair<MapKey &, MapValue &> unconst_pair (const_cast<MapKey &> (elem->first), elem->second);
      add (node.last_child (), unconst_pair, elem_name);
    }
}
template<typename MapKey, typename MapValue>
void add_elem_impl (
    std::unordered_map<MapKey, MapValue> &data,
    std::unique_ptr<std::pair<MapKey, MapValue>> elem_to_add_impl)
{
  assert_check (!data.count (elem_to_add_impl->first), "Map can't have two elements with same key");
  data.insert (move (*elem_to_add_impl));
}

/// unique_ptr
template<typename DataT>
void add_impl (node_t &node, std::unique_ptr<DataT> &data, const std::string &name)
{
  std::string elem_name = "entry";
  node.add_container<std::unique_ptr<DataT>, DataT> (data, name, elem_name);
  if (data)
    add (node.last_child (), *data, elem_name);
}
template<typename DataT>
void add_elem_impl (std::unique_ptr<DataT> &data, std::unique_ptr<DataT> elem_to_add_impl)
{
  data = move (elem_to_add_impl);
}

/// enums
template<typename Data, std::enable_if_t<std::is_enum_v<Data>, int> = 0>
void add_impl (node_t &node, Data &data, const std::string &name)
{
  node.add_primitive (data, name);
}

/// everything else
template<typename Data, std::enable_if_t<detail::can_build_saveload_tree<Data>::value, int> = 0>
void add_impl (node_t &node, Data &data, const std::string &name)
{
  node.add_complex_structure (data, name);
}
}  // namespace rules
}  // namespace saveload
