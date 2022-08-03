#pragma once
#include <tuple>
#include "constexpr_cond.hpp"

#ifndef AND
#define AND ,
#endif

// Remove type from tuple
template<typename Tdel, typename T1, typename T2 = std::tuple<>>
struct remove_T_tuple : std::type_identity<void> {};

template<typename Tdel, typename Result>
struct remove_T_tuple<Tdel, std::tuple<>, Result> : std::type_identity<Result> {};

template<typename Tdel, typename T, typename... Ts, typename... Ts2>
struct remove_T_tuple<Tdel, std::tuple<T, Ts...>, std::tuple<Ts2...>> : remove_T_tuple<Tdel, std::tuple<Ts...>, std::tuple<Ts2..., T>> {};

template<typename Tdel, typename... Ts, typename... Ts2>
struct remove_T_tuple<Tdel, std::tuple<Tdel, Ts...>, std::tuple<Ts2...>> : remove_T_tuple<Tdel, std::tuple<Ts...>, std::tuple<Ts2...>> {};

template<typename DelT, typename Tupl>
using remove_T_tuple_t = typename remove_T_tuple<DelT, Tupl>::type;

// Lessthan
template<auto v1, auto v2>
inline constexpr bool less_than = v1 < v2;

// Slice tuple
template<typename, std::size_t, std::size_t, typename>
struct slice_tuple {};

template<typename T, std::size_t start, std::size_t end, typename... Ts>
struct slice_tuple<T, start, end, std::tuple<Ts...>> : 
    std::conditional_t<less_than<start, end>, slice_tuple<T, start+1, end, std::tuple<Ts..., std::tuple_element_t<start, T>>>,
    std::type_identity<std::tuple<Ts..., std::tuple_element_t<start, T>>>> {};

template<typename T, std::size_t start, std::size_t end = std::tuple_size_v<T>>
using slice_tuple_t = typename slice_tuple<T, start, end-1, std::tuple<>>::type;

// Join tuple 
template<typename T, typename...>
struct join_tuple : std::type_identity<T> {};

template<typename... Ts1, typename... Ts2, typename... Ts3>
struct join_tuple<std::tuple<Ts1...>, std::tuple<Ts2...>, Ts3...> : join_tuple<std::tuple<Ts1..., Ts2...>, Ts3...> {};

template<typename... Ts>
using join_tuple_t = typename join_tuple<Ts...>::type;


// No repeated tuple
template<typename T, std::size_t i = 0>
struct norepeated_tuple : 
    constexpr_cond(less_than<i AND std::tuple_size_v<T>-1> && std::tuple_size_v<T>, norepeated_tuple<join_tuple_t<
        slice_tuple_t<T AND 0 AND i+1> 
        AND 
        remove_T_tuple_t<std::tuple_element_t<i AND T> AND slice_tuple_t<T AND i+1>
    >> AND i+1
>, std::type_identity<T>) {};

template<typename T>
using norepeated_tuple_t = typename norepeated_tuple<T>::type;
