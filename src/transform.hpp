#pragma once
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <iostream>

struct Transform {
    //glm::mat4 transform { 1.f };

    glm::vec3 scale {};
    glm::quat rotation {};
    glm::vec3 position {};

    virtual glm::mat4 getMatrix();

    Transform() {
        
    }
};
