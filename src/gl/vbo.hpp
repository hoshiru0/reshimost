#pragma once
#include <cstdint>
#include <initializer_list>

struct VBO {
    uint32_t id {};
    VBO();
    VBO(uint32_t vbo);
    VBO(VBO&& other);
    VBO& operator=(VBO&& other);
    
    VBO(const VBO &other) = delete;
	VBO& operator=(const VBO &other) = delete;

    void create(void);
    void destroy(void);
    void use(void);
    void unbind(void);
    ~VBO();

    template<typename T>
    void bufferData(std::initializer_list<T>, uint32_t draw_type = 0x88E4);
};
