#pragma once
#include <cstdint>


struct Texture {
    uint32_t texture;
    Texture();
    Texture(uint32_t texture);

    void texImage();

    void bind();
    void unbind();
    ~Texture();

};