#pragma once
#include <cstdint>
#include <initializer_list>

struct VBO {
    uint32_t vbo {};
    bool auto_destroy;
    VBO();
    VBO(uint32_t vbo);
    void create(void);
    void destroy(void);
    void bind(void);
    void unbind(void);
    ~VBO();

    void bufferDataStatic(std::initializer_list<float>);
    void bufferDataDynamic(std::initializer_list<float>);
};
