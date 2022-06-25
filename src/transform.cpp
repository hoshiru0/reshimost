#include "transform.hpp"
#include <glm/gtx/string_cast.hpp>

glm::mat4 Transform::getMatrix() {
    glm::mat4 m { 1.f };
    m = glm::translate(m, position);
    m = glm::rotate(m, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    return m;
    //return glm::lookAt(position, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0, 1, 0));
}