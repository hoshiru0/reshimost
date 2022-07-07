#include <glad/glad.hpp>

#include <entity.hpp>
#include <scene.hpp>

static Shader entity_shader {
R"(#version 300 es
precision mediump float;
in vec2 a_vert;
in vec2 a_tex_coord;

out vec2 tex_coord;

uniform mat4 u_MVP;

void main() {
    tex_coord = a_tex_coord;
    gl_Position = u_MVP * vec4(a_vert, 0.0, 1.0);
})",
R"(#version 300 es
precision mediump float;

in vec2 tex_coord;
out vec4 frag_color;

uniform sampler2D u_tex;
uniform float u_time;
uniform vec2 u_tex_size;

void main() {
    frag_color = texture(u_tex, tex_coord);
    if (frag_color.a < 0.5) {
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
}

void Entity::initEntity() {
    shader->use();
    vao.bind();
    init();
    vao.unbind();
}

void Entity::init() { // default initialization
    shared_vbo_vertex = shader->setAttribute<true>({"a_vert", "a_tex_coord"}, entity_vertices);
}

void Entity::update() {
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void Entity::updateEntity() {
    texture->bind();
    shader->use();
    glm::mat4 mvp = camera->getMatrix() * getMatrix();
    shader->uniform("u_MVP", mvp);
    
    vao.bind();
    update();
}

void Entity::destroy() {
    current_scene->destroyEntity(index);
}
