#include "camera.hpp"

Camera::Camera() {
    transform.position.z = -1.f;
}

glm::mat4 Camera::getMatrix() {
    return projection * transform.getMatrix();
}

void Camera::update() {
    float w = window.width/(200+(zoom*10));
    float h = window.height/(200+(zoom*10));
    projection = glm::ortho(-w, w, -h, h, 0.1f, 1000.0f);
}