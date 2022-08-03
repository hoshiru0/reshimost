#include "entity.hpp"
#include <scene/scene.hpp>


Entity::Entity() {

}

void Entity::update() {
    render();
}

void Entity::render() {
    glm::mat4 mvp = current_scene->camera.getMatrix() * transform.getMatrix();
    current_shader->uniform("u_MVP", mvp);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

Entity::~Entity() {

}





    //shared_vbo_vertex = shader->setAttribute<true>({"a_vert", "a_tex_coord"}, entity_vertices);
/*
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
    //sprite->use();
    
}

void Entity::updateMVP() {
    glm::mat4 mvp = current_scene->camera.getMatrix() * transform.getMatrix();
    //shader->uniform("u_MVP", mvp);
}

Entity::~Entity() {
    
}
**/
