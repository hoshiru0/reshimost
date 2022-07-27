#include "sprite.hpp"

extern double delta_time;

Sprite::Sprite(Texture* texture, glm::uvec2 size, Offsets offsets, uint32_t speed) : texture(texture), size(size), offsets(offsets), speed(speed) {

}

Sprite::Sprite(glm::uvec2 size, Offsets offsets) : texture(current_texture), size(size), offsets(offsets) {

}

void Sprite::use() {
    uint32_t frame = static_cast<uint32_t>(timeline / (1.f / speed)) % offsets.size();
    auto offset = *(offsets.begin() + frame);

    current_shader->uniform(
        "u_tex_offset", 
        glm::vec2(offset.x/(float)texture->width, offset.y/(float)texture->height)
    );

    current_shader->uniform(
        "u_tex_size", 
        glm::vec2(size.x/(float)texture->width, size.y/(float)texture->height)
    );


    timeline += delta_time;
}
