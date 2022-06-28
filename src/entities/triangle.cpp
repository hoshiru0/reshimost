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
    color = a_color;
    gl_Position = u_MVP * vec4(a_vert, 0.0, 1.0);
})",
R"(#version 300 es
precision mediump float;
out vec4 FragCoord;
in vec3 color;
uniform float time;

void main() {
    FragCoord = vec4(color.x, color.y + cos(time * 5.f)/2.0f+0.3f, color.z + cos(time * 5.f)/2.0f+0.3f, 1.0f);
})"
};

static std::initializer_list<float> vertices {
    -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
    0.5f, -0.5f,   1.0f, 1.0f, 0.0f,
    0.5f, 0.5f,    0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f,   1.0f, 0.0f, 0.0f
};


Triangle::Triangle() {
    Entity::shader = &tshader;
}

void Triangle::init() {
    shared_vbo_vertex = shader->setAttribute<true>({"a_vert", "a_color"}, vertices);
    //vbo2 = shader->setAttribute("a_color", color, 3);
}

void Triangle::update() {
    //glLineWidth(5.f);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void Triangle::move() {
    float velocity = 5.0f;
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
    if (input.getKey(KEY_DELETE)) {
        destroy();
        return;
    }
    rotation += delta_time * 500.f;
    
}