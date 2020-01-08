#pragma once

template <typename Self, typename ... Args>
class object;
class object_base;
namespace detail {
class saveload_container_node_base;
template<typename DataT, typename ElemT>
class saveload_container_node;
template<typename T>
class can_build_saveload_tree;
template <typename Data>
class saveload_primitive_node;
}
