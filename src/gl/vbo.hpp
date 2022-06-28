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

    template<typename T>
    void bufferData(std::initializer_list<T>, uint32_t draw_type = 0x88E4);
};
