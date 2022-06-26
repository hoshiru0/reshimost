#pragma once
#include <cstdint>

#include "../texturedata.hpp"

struct Texture {
    uint32_t texture;
    Texture();
    Texture(uint32_t texture);

    void texImage(TextureData&);

    void bind();
    void unbind();
    ~Texture();

};