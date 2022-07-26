#pragma once
#define IS_FROM_TEMPLATE(NAME, L1, L2) \
template<template<L1> typename, typename> \
struct is_from_##NAME##_template : std::false_type {}; \
template<template<L1> typename Tm, L1> \
struct is_from_##NAME##_template<Tm, Tm<L2>> : std::true_type {}; \
template<template<L1> typename Tm, typename T> \
inline constexpr bool is_from_##NAME##_template_v = is_from_##NAME##_template<Tm, T>::value;

IS_FROM_TEMPLATE(ts, typename... Ts, Ts...);
IS_FROM_TEMPLATE(auto, auto... Vs, Vs...);