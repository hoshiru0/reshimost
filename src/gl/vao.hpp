#pragma once
#include <cstdint>

struct VAO {
    uint32_t id;
    VAO();
    VAO(uint32_t id);

    void create(void);
    void destroy(void);
    void use(void);
    void unbind(void);
    ~VAO();
};
