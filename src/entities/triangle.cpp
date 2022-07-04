#include <entities/triangle.hpp>
#include <input.hpp>
#include <gl/texture.hpp>

#include <gl/shader.hpp>
#include <glad/glad.hpp>

static Shader tshader {
R"(#version 300 es
precision mediump float;
in vec2 a_vert;
in vec3 a_color;
in vec2 a_tex_coord;

out vec2 tex_coord;
out vec3 color;

uniform mat4 u_MVP;

void main() {
    color = a_color;
    tex_coord = a_tex_coord;
    gl_Position = u_MVP * vec4(a_vert, 0.0, 1.0);
})",
R"(#version 300 es
precision mediump float;

in vec2 tex_coord;
in vec3 color;

out vec4 frag_color;


uniform sampler2D u_texture;
uniform float u_time;

void main() {
    frag_color = texture(u_texture, tex_coord) * vec4(cos(color.x + u_time * 5.)/2.0+0.5, sin(color.y + u_time * 5.)/2.0+0.5, color.z, 1.);
    if (frag_color.a < 0.5) {
        discard;
    }
})"
};

static std::initializer_list<float> vertices {
    -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
    0.5f, -0.5f,   0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
    0.5f, 0.5f,    0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
    -0.5f, 0.5f,   0.0f, 1.0f, 1.0f,  0.0f, 0.0f
};


Triangle::Triangle() {
    Entity::texture = &textures<"gentoo">;
    Entity::shader = &tshader;
}

void Triangle::init() {
    shared_vbo_vertex = shader->setAttribute<true>({"a_vert", "a_color", "a_tex_coord"}, vertices);
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
    if (input.getKey(KEY_LEFT)) {
        scale.x += delta_time * velocity;
    }
    if (input.getKey(KEY_RIGHT)) {
        scale.x -= delta_time * velocity;
    }
    if (input.getKey(KEY_UP)) {
        scale.y += delta_time * velocity;
    }
    if (input.getKey(KEY_DOWN)) {
        scale.y -= delta_time * velocity;
    }
    if (input.getKey(KEY_DELETE)) {
        destroy();
        return;
    }
    //rotation += delta_time * 500.f;
}