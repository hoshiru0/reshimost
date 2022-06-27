#pragma once
#include <iostream>

#define IS_FROM_TEMPLATE(NAME, L1, L2) \
template<template<L1> typename, typename> \
struct is_from_##NAME##_template : std::false_type {}; \
template<template<L1> typename Tm, L1> \
struct is_from_##NAME##_template<Tm, Tm<L2>> : std::true_type {}; \
template<template<L1> typename Tm, typename T> \
inline constexpr bool is_from_##NAME##_template_v = is_from_##NAME##_template<Tm, T>::value;

IS_FROM_TEMPLATE(ts, typename... Ts, Ts...);
IS_FROM_TEMPLATE(auto, auto... Vs, Vs...);

template<std::size_t e = 1, typename... S> 
requires std::conjunction_v<std::is_convertible<S, std::string_view>...>
void terminate(const S... str) {
    if constexpr (sizeof...(S) > 0)
        (std::operator<<((1 ? std::cerr : std::cout) << str, " "), ...) << "\n";
    
    std::exit(e);
}

// Overload
template<typename... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

#define validexpr(EXPR) overloaded { \
        [] <typename = void> requires requires() { \
            EXPR; \
        } () consteval { \
            return true; \
        }, \
        [] <typename = void> () consteval { \
            return false; \
        } \
    }() 


#define evalif_validexpr(EXPR, ...) if constexpr (validexpr(EXPR)) { \
    EXPR; \
} else { \
   __VA_ARGS__; \
}

template<typename... Ts>
struct CustomTuple {
    using type = decltype([] () {
        auto f = [] <typename T, typename... TTs> (const auto& fref) {
            if constexpr (sizeof...(TTs)) {
                return std::pair<T, decltype(fref.template operator()<TTs...>(fref))>{};
            } else {
                return T{};
            }
        };
        return decltype(f.template operator()<Ts...>(f)){};
    }());
    type a;

    template<typename... Args>
    constexpr void setValues(Args&&... args) {
        if constexpr (sizeof...(Ts) > 1) {
            auto f = [] <typename T, typename... TTs> (const auto& fref, auto& tupl, T&& v, TTs&&... vs) {
                tupl.first = std::forward<T>(v);
                if constexpr (sizeof...(TTs) > 1) {
                    fref(fref, tupl.second, std::forward<TTs>(vs)...);
                } else {
                    tupl.second = (std::forward<TTs>(vs), ...);
                }
            };
            f(f, a, std::forward<Ts>(args)...);
        } else {
            a = (std::forward<Args>(args), ...);    
        }
    }
    template<auto index>
    constexpr auto& get() {
        if constexpr (sizeof...(Ts) > 1) {
            auto f = [] <auto i = 0, typename T> (const auto& fref, T& v) -> auto& {
                if constexpr (is_from_ts_template_v<std::pair, T>) {
                    if constexpr (i == index) 
                        return v.first;
                    else 
                        return fref.template operator()<i+1>(fref, v.second);
                } else {
                    return v;
                }
            };
            return f(f, a);
        } else {
            if constexpr (index == 0) {
                return a;
            }
        }
    }

    constexpr CustomTuple() {

    }

    template<typename... Args>
    constexpr CustomTuple(Args&&... args) {
        setValues(std::forward<Args>(args)...);
    }

    constexpr CustomTuple(Ts&&... args) {
        setValues(std::forward<Ts>(args)...);
    }
};