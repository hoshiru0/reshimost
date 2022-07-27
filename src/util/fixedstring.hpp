#pragma once
#include <iostream>
#include <algorithm>
#include <string_view>

template<std::size_t S>
class FixedString;

template<FixedString str>
constexpr FixedString fs { str };

template<std::size_t N> FixedString(const char (&) [N]) -> FixedString<N-1>;
template<std::size_t N> FixedString(char (&) [N]) -> FixedString<N-1>;

template<std::size_t S>
struct FixedString {
    std::size_t size_ {S};
    char str[S+1] {};

    consteval FixedString(const char* str_) {
        std::copy_n(str_, S, str);
    }

    consteval std::size_t size() const {
        return size_;
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
        std::copy_n(str, size(), newchar);
        std::copy_n(str1.str, s1, newchar+size());
        return FixedString<s1+S>(newchar);
    }

    template<std::size_t s1>
    consteval bool operator==(const FixedString<s1> str2) const {
        if (str2.size() != size()) { return false; }
        for (std::size_t i=0; i<str2.size();i++) {
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

    template<std::size_t s1>
    consteval std::size_t find(FixedString<s1> fs, std::size_t pos = 0) const {
        for (std::size_t i=pos; i<size(); i++) {
            bool d {true};
            for (std::size_t j=0; j<s1-1; j++) {
                if (str[i+j] != fs.str[j]) {
                    d = false;
                    break;
                }
            }
            if (d) {
                return i;
            }
        }
        return -1;
    }
};


template<std::size_t s1, std::size_t s2>
consteval auto operator+(FixedString<s1> fs, const char (&str1) [s2]) {
    return fs + FixedString<s2-1>(str1);
}


template<std::size_t s1, std::size_t s2>
consteval auto operator+(const char (&str1) [s2], FixedString<s1> fs) {
    return FixedString<s2-1>(str1) + fs;
}

template<FixedString S>
consteval auto operator""_fs(){
    return S;
}
