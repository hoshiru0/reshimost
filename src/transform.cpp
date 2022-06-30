#include <transform.hpp>
#include <glm/gtx/string_cast.hpp>

glm::mat4 Transform::getMatrix() {
    glm::mat4 m { 1.f };
    rotation = fmod(rotation, 360.f);
    m = glm::translate(m, position);
    m = glm::rotate(m, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    return m;
}