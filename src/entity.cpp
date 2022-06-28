#include <glad/glad.h>

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
uniform float time;

void main() {
    FragCoord = vec4(color.x + cos(time)/2.0f+0.5, color.y, color.z, 1.0f);
})"
};

static std::initializer_list<float> entity_vertices  {
    -0.5f, -0.5f,
    -0.5f,  0.5f,
    0.5f,  0.5f,
    0.5f, -0.5f
};
static std::initializer_list<float> entity_color  {
    1.f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f,  0.0f, 1.0f,
    1.0f,  0.0f, 1.0f
};

Entity::Entity() : shader(&entity_shader) {
}

void Entity::initEntity() {
    shader->use();
    vao.bind();
    init();
    vao.unbind();
}

void Entity::init() { // default initialization
    shared_vbo_vertex = shader->setSharedAttribute("a_vert", entity_vertices);
    shared_vbo_color = shader->setSharedAttribute("a_color", entity_color);
}

void Entity::update() {
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void Entity::updateEntity() {
    shader->use();
    glm::mat4 mvp = camera->getMatrix() * getMatrix();
    // * camera->getMatrix() *
    shader->uniformMat4f("u_MVP", mvp);
    vao.bind();
    update();
}

void Entity::destroy() {
    current_scene->destroyEntity(index);
}