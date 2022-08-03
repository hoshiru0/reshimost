#pragma once
#define constexpr_for(ini, cmp, inc, expr) [&] () constexpr {   \
    const auto f = [&] <ini> (const auto& fref) constexpr {     \
        if constexpr (cmp) {                                    \
            expr;                                               \
            return fref.template operator()<inc>(fref);         \
        }                                                       \
    };                                                          \
    return f.template operator()(f);                            \
}();

#define AND ,
