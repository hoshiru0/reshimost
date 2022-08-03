#include "sprite.hpp"

extern double delta_time;

Sprite::Sprite(glm::uvec2 size, Offsets offsets, uint16_t speed, uint16_t loops) 
: size(size), offsets(offsets), speed(speed), loops(loops) {

}

void Sprite::use() {
    uint32_t current_frame = static_cast<uint32_t>(timeline / (1.f / speed)); 
    auto& offset = *(offsets.begin() + current_frame);

    current_shader->uniform(
        "u_tex_offset", 
        glm::vec2(offset.x/(float)current_texture->width, offset.y/(float)current_texture->height)
    );

    current_shader->uniform(
        "u_tex_size", 
        glm::vec2(size.x/(float)current_texture->width, size.y/(float)current_texture->height)
    );

    if (loops) {
        double next_timeline = std::fmod(timeline + delta_time, 1.f / speed * offsets.size());
        
        if (loops > 0 && next_timeline < timeline) {
            loops--;
        }

        timeline = next_timeline;
    }
}
