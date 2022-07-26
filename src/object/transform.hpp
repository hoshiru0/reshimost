#pragma once
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

struct Transform {
    glm::vec3 scale {1, 1, 1};
    float rotation {};
    glm::vec3 position {};

    glm::mat4 getMatrix();
};
