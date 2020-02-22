#ifndef TYPE_TRAITS_EXT_H
#define TYPE_TRAITS_EXT_H
#include <type_traits>

template<typename T, typename = void>
struct is_iterable : std::false_type {};
template<typename T>
struct is_iterable<T, std::void_t<decltype (std::declval<T> ().begin ()),
                                  decltype (std::declval<T> ().end ())>
                  > : std::true_type {};
template<typename T>
inline constexpr bool is_iterable_v = is_iterable<T>::value;

#endif // TYPE_TRAITS_EXT_H
