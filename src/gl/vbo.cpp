#include <iostream>

#include <gl/vbo.hpp>
#include <glad/glad.hpp>

VBO::VBO() {
    create();
}

VBO::VBO(uint32_t otherid) : id(otherid) {
}

VBO::VBO(VBO&& other) : id(other.id) {
    other.id = 0;
}

VBO& VBO::operator=(VBO&& other) {
    destroy();
    id = other.id;
    other.id = 0;
    return *this;
}

void VBO::create() {
    glGenBuffers(1, &id);
    std::cout << "create vbo: " << id << std::endl;
}

void VBO::destroy() {
    if (id) {
        std::cout << "destroy vbo: " << id << std::endl;
        glDeleteBuffers(1, &id);
        id = 0;
    }
}

VBO::~VBO() {
    destroy();
}

void VBO::use() {
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VBO::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER , 0);
}

template<typename T>
void VBO::bufferData(std::initializer_list<T> l, uint32_t draw_type) {
    use();
    glBufferData(GL_ARRAY_BUFFER, l.size() * sizeof(T), l.begin(), draw_type);
}

template void VBO::bufferData(std::initializer_list<float>, uint32_t);
template void VBO::bufferData(std::initializer_list<int>, uint32_t);