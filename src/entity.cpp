#include "entity.hpp"
#include "scene.hpp"

Shader entity_shader {
R"(#version 300 es
precision mediump float;
in vec2 a_vert;
in vec3 a_color;

out vec3 color;

uniform mat4 u_MVP;

void main() {
    gl_Position = u_MVP * vec4(a_vert, 0.0f, 1.0f);
    color = a_color;
})",
R"(#version 300 es
precision mediump float;
out vec4 FragCoord;
in vec3 color;

void main() {
    FragCoord = vec4(color, 1.0f);
})"
};

static std::initializer_list<float> entity_vertices  {
    -0.5f, -0.5f,
    -0.5f,  0.5f,
    0.5f,  0.5f,
    0.5f, -0.5f
};
static std::initializer_list<float> color  {
    1.f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f,  0.0f, 1.0f,
    1.0f,  0.0f, 1.0f
};

Entity::Entity(EntityParams&& params) :
    vao(),
    params(params) {
    float x {};
    std::initializer_list<float> a{ x };
    
    params.shader->setAttributeOnce("a_vert", params.vertices, 2);
    params.shader->setAttributeOnce("a_color", color, 3);
    vao.unbind();
}

void Entity::updateEntity() {
    params.shader->use();
    glm::mat4 mvp = camera->getMatrix() * getMatrix();
    // * camera->getMatrix() *
    params.shader->uniformMat4f("u_MVP", mvp);
    vao.bind();
    update();
}