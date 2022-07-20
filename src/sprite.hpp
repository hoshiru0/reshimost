#pragma once
#include <gl/texture.hpp>
#include <gl/shader.hpp>
#include <glm/vec2.hpp>
#include <iostream>
#include <glm/gtx/string_cast.hpp>

struct Sprite {
    Texture* texture {};
    glm::uvec2 size {};
    glm::uvec2 offset {};
    
    void use();

};
