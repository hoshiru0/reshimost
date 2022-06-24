#pragma once
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Transform {
    glm::mat4 transform;

    Transform() {
        
    }

    void setPos(int x, int y) {
        glm::translate(transform, glm::vec3(x, y, 0));
    }
};