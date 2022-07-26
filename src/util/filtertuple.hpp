#pragma once
#include <tuple>
// Filter type from tuple 
template<typename, auto, typename T>
struct filter_tuple : std::type_identity<T> {};

template<auto f, typename T, typename... Ts, typename... TsF>
struct filter_tuple<std::tuple<T, Ts...>, f, std::tuple<TsF...>> :
    std::conditional_t<
        f.TO()<T>(),
            filter_tuple<std::tuple<Ts...>, f, std::tuple<TsF..., T>>,
            filter_tuple<std::tuple<Ts...>, f, std::tuple<TsF...>>> 
        {};

template<typename T, auto f>
using filter_tuple_t = typename filter_tuple<T, f, std::tuple<>>::type;

template<typename, auto> 
struct filter1_tuple : std::type_identity<void> {};

template<auto f, typename T, typename... Ts>
struct filter1_tuple<std::tuple<T, Ts...>, f> :
    std::conditional_t<
        f.TO()<T>(),
            std::type_identity<T>,
            filter1_tuple<std::tuple<Ts...>, f>> 
        {};


#define FILTER_TUPLE(NAME, EXPR)                                                    \
template<typename, typename T>                                                      \
struct filter_tuple_##NAME : std::type_identity<T> {};                              \
template<typename T, typename... Ts, typename... TsF>                               \
struct filter_tuple_##NAME<std::tuple<T, Ts...>, std::tuple<TsF...>> :              \
    std::conditional_t<                                                             \
        EXPR,                                                                       \
            filter_tuple_##NAME<std::tuple<Ts...>, std::tuple<TsF..., T>>,          \
            filter_tuple_##NAME<std::tuple<Ts...>, std::tuple<TsF...>>>             \
        {};                                                                         \
template<typename T>                                                                \
using filter_tuple_##NAME##_t = typename filter_tuple_##NAME<T, std::tuple<>>::type;
