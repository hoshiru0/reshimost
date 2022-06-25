#include "triangle.hpp"
#include "../input.hpp"

#include "../gl/shader.hpp"

static Shader tshader {
R"(#version 300 es
precision mediump float;
in vec2 vert;
in vec3 f_color;

out vec3 color;

uniform mat4 u_MVP;

void main() {
    gl_Position = u_MVP * vec4(vert, 0.0, 1.0);
    color = f_color;
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
    -0.5f,  0.5f,
    0.5f,  0.5f,
    0.5f, -0.5f
};

std::initializer_list<float> color {
    1.f, 0.f, 0.0f,
     1.f, 1.f, 0.0f,
     0.f, 1.f, 0.0f,
     0.0f,  0.0f, 1.0f
};

Triangle::Triangle() {
    
}
void Triangle::update() {
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
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