#pragma once
#include <cstdint>
#include <utility/fixedstring.hpp>
#include <memory>
#include <string>

struct Texture {
    uint32_t texture;
    uint32_t width;
    uint32_t height;
    std::unique_ptr<uint8_t> data;

    Texture();
    Texture(uint32_t texture);

    void create(void);
    void bindImage(std::string_view);
    void destroy(void);

    void bind(void);
    void unbind(void);
    ~Texture();
};

extern std::string imagepath;

template<FixedString str>
inline Texture textures { 0 };