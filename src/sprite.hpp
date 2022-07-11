#include <gl/texture.hpp>

struct Sprite {
    Texture texture;

    Sprite(const char* name) : texture(name) {

    }
};