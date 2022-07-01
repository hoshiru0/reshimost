#include <glad/glad.hpp>
#include <gl/texture.hpp>
#include <iostream>
#include <utility/terminate.hpp>
#include <png.h>

std::string imagepath = "img/";
Texture::Texture() {
    create();
}

Texture::Texture(uint32_t texture) : texture(texture) {}

void Texture::create() {
    glGenTextures(1, &texture);
    std::cout << "create texture " << texture << "\n";
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::bindImage(std::string_view imagestr) {
    FILE *fp = fopen((imagepath + imagestr.data() + ".png").data(), "rb");

    static auto onErr = [] (png_structp pngPtr, png_const_charp msg) {
        terminate("ERROR:", msg);
    };
    static auto onWarn = [] (png_structp pngPtr, png_const_charp msg) {
        terminate("WARN:", msg);
    };

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, onErr, onWarn);
    
    png_infop info = png_create_info_struct(png);

    if (!fp) {
        terminate("ERROR: Image not found", imagestr);
    }
    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.width, texture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture.data);

    png_destroy_read_struct(&png, &info, NULL);
}

void Texture::destroy() {
    if (texture) {
        std::cout << "destroy texture " << texture << "\n";
        glDeleteTextures(1, &texture);
        texture = 0;
    }
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
    destroy();
}