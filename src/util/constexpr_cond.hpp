#pragma once
// Conditional constexpr
#define constexpr_cond(cond, type1, type2) decltype([] () consteval { \
    if constexpr (cond) { \
        return std::type_identity<type1>{}; \
    } else { \
        return std::type_identity<type2>{}; \
    } \
}())::type
