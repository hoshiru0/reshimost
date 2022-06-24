#pragma once
#include <iostream>

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
