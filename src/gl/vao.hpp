#pragma once
#include <cstdint>

struct VAO {
    uint32_t vao;
    VAO();
    void use(void);
    void unbind(void);
    ~VAO();
};