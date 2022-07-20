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
    gl_Position = u_MVP * vec4(a_vert, 0.f, 1.f);
})",
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
}

void Entity::setSpriteAnim(SpriteAnim& anim) {
    sprites = &anim;
    sprites->timeline = 0;
}

void Entity::initEntity() {
    shader->use();
    vao.use();
    initRender();
    vao.unbind();
}

void Entity::initRender() { // default initialization
    shared_vbo_vertex = shader->setAttribute<true>({"a_vert", "a_tex_coord"}, entity_vertices);
    //shader.uniform("u_tex_size", glm::vec2(1.f, 1.f));
    //shader->uniform("u_tex_size", glm::vec2((1.f/ texture->width) * 5000.f, (1.f/ texture->height) * 500.f));
    //shader->uniform("u_tex_offset", glm::vec2((1.f / texture->width), 0.0f));
}

void Entity::update() {
    
}
void Entity::updateRender() {
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void Entity::updateEntity() {
    shader->use();
    if (sprites) {
        sprites->use();
    }
    
    glm::mat4 mvp = camera->getMatrix() * getMatrix();
    shader->uniform("u_MVP", mvp);
    
    vao.use();
    updateRender();
}

void Entity::destroy() {
    current_scene->destroyEntity(index);
}

