#include "triangle.hpp"
#include "../input.hpp"

#include "../gl/shader.hpp"
#include <glad/glad.h>

static Shader tshader {
R"(#version 300 es
precision mediump float;
in vec2 a_vert;
in vec3 a_color;

out vec3 color;

uniform mat4 u_MVP;

void main() {
    gl_Position = u_MVP * vec4(a_vert, 0.0, 1.0);
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

static std::initializer_list<float> vertices {
    -0.5f, -0.5f,
    0.5f, -0.5f,
    0.0f, 0.5f
};

std::initializer_list<float> color {
    1.f, 0.f, 0.0f,
     1.f, 1.f, 0.0f,
     0.f, 1.f, 0.0f
};

Triangle::Triangle() {
    Entity::shader = &tshader;
}

void Triangle::init() {
    shader->setAttributeOnce("a_vert", vertices, 2);
    shader->setAttributeOnce("a_color", color, 3);
}

void Triangle::update() {
    glLineWidth(10.f);
    glDrawArrays(GL_LINE_LOOP, 0, 3);
}

void Triangle::move() {
    float velocity = 3.0f;
    if (input.getKey(KEY_A)) {
        position.x -= delta_time * velocity;
    }
    if (input.getKey(KEY_D)) {
        position.x += delta_time * velocity;
    }
    if (input.getKey(KEY_W)) {
        position.y += delta_time * velocity;
    }
    if (input.getKey(KEY_S)) {
        position.y -= delta_time * velocity;
    }
    rotation.z += delta_time * 100.f;
    
}