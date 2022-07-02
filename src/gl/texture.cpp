#include <glad/glad.hpp>
#include <gl/texture.hpp>
#include <iostream>
#include <utility/terminate.hpp>
#include <png.h>

std::string imagepath = "img/";
Texture::Texture() {
    create();
}

Texture::Texture(uint32_t texture) : id(texture) {}

void Texture::create() {
    glGenTextures(1, &id);
    std::cout << "create texture " << id << "\n";
}

void Texture::bind() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::bindImage(std::string_view imagestr) {
    FILE *fp = fopen((imagepath + imagestr.data() + ".png").data(), "rb");
    if (!fp) {
        terminate("ERROR: Image not found", imagestr);
    }
    static auto onErr = [] (png_structp pngPtr, png_const_charp msg) {
        terminate("ERROR:", msg);
    };
    static auto onWarn = [] (png_structp pngPtr, png_const_charp msg) {
        terminate("WARN:", msg);
    };

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, onErr, onWarn);
    if (!png) {
        terminate("ERROR: creating png struct", __FILE__);
    }
    
    png_infop info = png_create_info_struct(png);
    png_init_io(png, fp);
    png_read_info(png, info);

    width = png_get_image_width(png, info);
    height = png_get_image_height(png, info);
    png_byte color_type = png_get_color_type(png, info);
    png_byte bit_depth = png_get_bit_depth(png, info);
    
    uint32_t row_size = png_get_rowbytes(png, info);
    data = std::make_unique<uint8_t[]>(height * row_size * sizeof(png_byte));
    png_bytepp row_pointers = (png_bytepp)malloc(height * sizeof(png_bytep));

    for (int i = 0; i < height; i++) {
        row_pointers[i] = data.get() + (i * row_size);
    }

    png_read_image(png, row_pointers);

    fclose(fp);
    free(row_pointers);
    png_destroy_read_struct(&png, &info, NULL);

    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.get());
    glGenerateMipmap(GL_TEXTURE_2D);
    
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.width, texture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture.data);

}

void Texture::destroy() {
    if (id) {
        std::cout << "destroy texture " << id << "\n";
        glDeleteTextures(1, &id);
        id = 0;
    }
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
    destroy();
}