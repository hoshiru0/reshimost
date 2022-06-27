#pragma once
#include <cstdint>
#include <initializer_list>

struct VBO {
    uint32_t vbo {};
    VBO();
    VBO(uint32_t vbo);
    VBO(VBO&& vbo_);
    VBO& operator=(VBO&& vbo_);
    void create(void);
    void destroy(void);
    void bind(void);
    void unbind(void);
    ~VBO();

    void bufferDataStatic(std::initializer_list<float>);
    void bufferDataDynamic(std::initializer_list<float>);
};
