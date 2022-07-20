#pragma once
#include <cstdint>
#include <utility/fixedstring.hpp>
#include <memory>
#include <string>

struct Texture {
    uint32_t id;
    uint32_t width;
    uint32_t height;

    Texture();
    Texture(std::string_view image);
    Texture(uint32_t texture);

    Texture& operator=(Texture& other);
    Texture& operator=(const char* name);

    void create(void);
    void bindImage(std::string_view);
    void destroy(void);

    void use(void);
    void unbind(void);
    ~Texture();
};

extern std::string imagepath;
