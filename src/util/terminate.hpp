#pragma once
#include <iostream>
#include <type_traits>

template<std::size_t e = 1, typename... S> 
requires std::conjunction_v<std::is_convertible<S, std::string_view>...>
void terminate(const S... str) {
    if constexpr (sizeof...(S) > 0)
        (std::operator<<((1 ? std::cerr : std::cout) << str, " "), ...) << "\n";
    
    std::exit(e);
}