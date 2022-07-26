#pragma once
#include <utility>
#include <utility/fromtemplate.hpp>

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
