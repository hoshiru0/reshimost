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
    Texture* texture {};
    glm::uvec2 size {};
    Offsets offsets;

    uint32_t speed;
    double timeline {};

    Sprite(Texture* texture, glm::uvec2 size, Offsets offsets, uint32_t speed = 24);
    Sprite(glm::uvec2 size, Offsets offsets);
    
    void use();
};
