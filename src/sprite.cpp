#include "sprite.hpp"

void Sprite::use() {
    texture->use();
    current_shader->uniform(
        "u_tex_offset", 
        glm::vec2(offset.x/(float)texture->width, offset.y/(float)texture->height)
    );

    current_shader->uniform(
        "u_tex_size", 
        glm::vec2(size.x/(float)texture->width, size.y/(float)texture->height)
    );
}