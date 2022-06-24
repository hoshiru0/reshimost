#pragma once
#include <glm/ext.hpp>
#include "transform.hpp"

struct Camera : Transform {
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f); 

    void update() {

    }
};
