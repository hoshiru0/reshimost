#pragma once
#include <cstdint>

struct TextureData {
    uint32_t width;
    uint32_t height;
    const char* data;
};