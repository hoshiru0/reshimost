#pragma once
#include <gl/texture.hpp>
#include <gl/shader.hpp>
#include <glm/vec2.hpp>
#include <iostream>
#include <glm/gtx/string_cast.hpp>

using Offsets = std::initializer_list<glm::uvec2>;

template<Offsets::value_type... o>
constexpr Offsets offsets {
    o...
};

struct Sprite {
    glm::uvec2 size {};
    Offsets offsets;

    uint16_t speed;
    int8_t loops;

    float timeline {};

    Sprite(glm::uvec2 size, Offsets offsets, uint16_t speed = 10, uint16_t loops = -1);

    void use();
};
