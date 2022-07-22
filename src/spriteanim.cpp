#include "spriteanim.hpp"

extern double delta_time;

SpriteAnim::SpriteAnim(Texture* texture, glm::uvec2 size, Offsets offsets, double speed) : sprite(texture, size, {}), offsets(offsets), speed(speed) {

}

void SpriteAnim::use() {
    if (!sprite.texture) {
        return;
    }

    sprite.use();
    uint32_t frame = static_cast<uint32_t>(timeline / speed) % offsets.size();
    sprite.offset = *(offsets.begin() + frame);
    timeline += delta_time;
}