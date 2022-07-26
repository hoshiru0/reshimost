#pragma once
#include <cstdint>
#include <sprite/sprite.hpp>
#include <initializer_list>

using Offsets = std::initializer_list<glm::uvec2>;

template<Offsets::value_type... o>
constexpr Offsets offsets {
    o...
};

struct SpriteAnim {
    Sprite sprite;
    Offsets offsets;
    double speed;
    double timeline {};

    SpriteAnim(Texture* texture, glm::uvec2 size, Offsets offsets, double speed = 1./24);

    void use();
};

