#pragma once
#include <type_traits>

#define GENERATE_HAS_MEMBER(member)                                               \
template < class T >                                                              \
class has_member_##member                                                         \
{                                                                                 \
private:                                                                          \
    typedef char Yes[19];                                                         \
    typedef char No[7];                                                           \
    template<typename C>                                                          \
    static Yes &test (decltype (&C::member));                                     \
    template<typename C>                                                          \
    static No &test (...);                                                        \
public:                                                                           \
    enum { value = sizeof (test<T> (0)) == sizeof (Yes) };                        \
};                                                                                \

