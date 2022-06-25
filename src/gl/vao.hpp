#include <cstdint>


struct VAO {
    uint32_t vao;
    VAO();
    void bind(void);
    void unbind(void);
    ~VAO();
};