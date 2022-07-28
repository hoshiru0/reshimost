#include "sprite.hpp"

extern double delta_time;

Sprite::Sprite(Texture& texture, glm::uvec2 size, Offsets offsets, uint16_t speed, uint16_t loops)
 : texture(&texture), size(size), offsets(offsets), speed(speed), loops(loops) {

}

Sprite::Sprite(glm::uvec2 size, Offsets offsets, uint16_t speed, uint16_t loops) 
: texture(current_texture), size(size), offsets(offsets), speed(speed), loops(loops) {

}

void Sprite::use() {
    uint32_t current_frame = static_cast<uint32_t>(timeline / (1.f / speed)); 
    auto& offset = *(offsets.begin() + current_frame);

    current_shader->uniform(
        "u_tex_offset", 
        glm::vec2(offset.x/(float)texture->width, offset.y/(float)texture->height)
    );

    current_shader->uniform(
        "u_tex_size", 
        glm::vec2(size.x/(float)texture->width, size.y/(float)texture->height)
    );

    
    if (loops) {
        double next_timeline = std::fmod(timeline + delta_time, 1.f / speed * offsets.size());
        
        if (loops > 0 && next_timeline < timeline) {
            loops--;
        }

        timeline = next_timeline;
    }
}
