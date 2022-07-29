#include "entity.hpp"

#include <glad/glad.hpp>
#include <scene/scene.hpp>

static Shader entity_shader {
R"(#version 300 es
precision mediump float;
in vec2 a_vert;
in vec2 a_tex_coord;
out vec2 tex_coord;
uniform mat4 u_MVP;
void main() {
    tex_coord = a_tex_coord;
    gl_Position = u_MVP * vec4(a_vert, 0.f, 1.f);
}
)",
R"(#version 300 es
precision mediump float;
in vec2 tex_coord;
out vec4 frag_color;

uniform sampler2D u_tex;
uniform float u_time;
uniform vec2 u_tex_size;
uniform vec2 u_tex_offset;

void main() {
    frag_color = texture(u_tex, tex_coord * u_tex_size + u_tex_offset);
    if (frag_color.a < 0.5f) {
        discard;
    }
})"
};


static std::initializer_list<float> entity_vertices  {
    -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f,   1.0f, 1.0f,
    0.5f, 0.5f,    1.0f, 0.0f,
    -0.5f, 0.5f,   0.0f, 0.0f
};

Entity::Entity() : shader(&entity_shader) {
    shader->use();
    shared_vbo_vertex = shader->setAttribute<true>({"a_vert", "a_tex_coord"}, entity_vertices);
    vao.unbind();
}

void Entity::setSprite(Sprite& anim) {
    sprite = &anim;
    sprite->timeline = 0;
    // Adjust scale
    transform.scale.x *= ((float) anim.size.x/anim.size.y);
}

void Entity::update() {
    
}

void Entity::render() {
    shared_vbo_vertex->use();
    shader->use();
    sprite->use();
    updateMVP();
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void Entity::updateMVP() {
    glm::mat4 mvp = current_scene->camera.getMatrix() * transform.getMatrix();
    shader->uniform("u_MVP", mvp);
}

Entity::~Entity() {
    
}
