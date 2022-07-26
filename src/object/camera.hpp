#pragma once
#include <memory>
#include <glm/ext.hpp>

#include "transform.hpp"
#include <gui/window.hpp>
#include <iostream>

struct Camera : Transform {
    float zoom = 0;
    glm::mat4 projection;

    Camera() {
        position.z -= 1.f;
        //transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, -1.0f));
    }

    glm::mat4 getMatrix() override {
        return projection * Transform::getMatrix();
    }
    
    void update() {
        float w = window.width/(200+(zoom*10));
        float h = window.height/(200+(zoom*10));
        projection = glm::ortho(-w, w, -h, h, 0.1f, 1000.0f);
    }
};


inline std::unique_ptr<Camera> camera = std::make_unique<Camera>();
