#include <png.h>
#include <cstdlib>
#include <iostream>


int main(int argc, char ** argv) {

    if (argc <= 1) {
        return 1;
    }
    const char* fname = argv[1];
    FILE *fp = fopen(fname, "rb");
    if (!fp) {
        std::cout << "image " << fname << " not found\n";
    }

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info = png_create_info_struct(png);
    png_init_io(png, fp);
    png_read_info(png, info);

    uint32_t width = png_get_image_width(png, info);
    uint32_t height = png_get_image_height(png, info);
    png_byte color_type = png_get_color_type(png, info);
    png_byte bit_depth = png_get_bit_depth(png, info);


    std::cout << width << std::endl;
    std::cout << height << std::endl;


    uint32_t row_size = png_get_rowbytes(png, info);
    png_bytepp row_pointers = (png_bytepp)malloc(height * sizeof(png_bytep));
    png_bytep data = (png_bytep) malloc(height * row_size * sizeof(png_byte));

    for (int i = 0; i < height; i++) {
        row_pointers[i] = data + (i * row_size);
    }

    png_read_image(png, row_pointers);

    fclose(fp);

    png_destroy_read_struct(&png, &info, NULL);

}
