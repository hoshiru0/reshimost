#pragma once

#include <algorithm>
#include <string_view>

template<std::size_t S>
struct FixedString {
    size_t size {S};
    char str[S+1] {};

    consteval FixedString(char (&str_)[S+1]) {
        std::copy_n(str_, S, str);
    }

    consteval FixedString(const char (&str_)[S+1]) {
        std::copy_n(str_, S, str);
    }

    consteval const char* data() const {
        return str;
    }

    operator const char*() const {
        return str;
    }

    operator std::string_view() const {
        return str;
    }

    template<std::size_t s1>
    consteval auto operator+(const FixedString<s1> str1) const {
        char newchar[s1+S+1] {};
        std::copy_n(str, size, newchar);
        std::copy_n(str1.str, s1, newchar+size);
        return FixedString<s1+S>(newchar);
    }

    template<std::size_t s1>
    consteval bool operator==(const FixedString<s1> str2) const {
        if (str2.size != size) { return false; }
        for (std::size_t i=0; i<str2.size;i++) {
            if (str2.str[i] != str[i]) {
                return false;
            }
        }
        return true;
    }

    template<std::size_t s1>
    consteval bool operator==(const char (&str2) [s1]) const {
        return (*this) == FixedString<s1-1>(str2);
    }

};

template<std::size_t N> FixedString(const char (&) [N]) -> FixedString<N-1>;
template<std::size_t N> FixedString(char (&) [N]) -> FixedString<N-1>;


template<std::size_t s1, std::size_t s2>
consteval auto operator+(FixedString<s1> fs, const char (&str1) [s2]) {
    return fs + FixedString<s2-1>(str1);
}

template<std::size_t s1, std::size_t s2>
consteval auto operator+(const char (&str1) [s2], FixedString<s1> fs) {
    return FixedString<s2-1>(str1) + fs;
}
