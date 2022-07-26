#include "sprite.hpp"

Sprite::Sprite(Texture* texture, glm::uvec2 size, glm::vec2 offset) : texture(texture), size(size), offset(offset) {

}

Sprite::Sprite(glm::uvec2 size, glm::vec2 offset) : texture(current_texture), size(size), offset(offset) {

}

void Sprite::use() {
    current_shader->uniform(
        "u_tex_offset", 
        glm::vec2(offset.x/(float)texture->width, offset.y/(float)texture->height)
    );

    current_shader->uniform(
        "u_tex_size", 
        glm::vec2(size.x/(float)texture->width, size.y/(float)texture->height)
    );
}