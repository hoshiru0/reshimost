#pragma once
#include <memory>
#include <glm/ext.hpp>

#include "transform.hpp"
#include <gui/window.hpp>

struct Camera {
    float zoom = 0;
    Transform transform;
    glm::mat4 projection;

    Camera();

    glm::mat4 getMatrix();
    
    void update();
};

