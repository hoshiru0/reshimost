#include "ebo.hpp"
#include <glad/glad.hpp>

EBO::EBO() {
    glGenBuffers(1, &vbo);
}

EBO::~EBO() {
    glDeleteBuffers(1, &vbo);
}

void EBO::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
}

void EBO::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , 0);
}

void EBO::bufferDataStatic(std::initializer_list<uint32_t> l) {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, l.size() * sizeof(uint32_t), l.begin(), GL_STATIC_DRAW);
}
void EBO::bufferDataDynamic(std::initializer_list<uint32_t> l) {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, l.size() * sizeof(uint32_t), l.begin(), GL_DYNAMIC_DRAW);
}
