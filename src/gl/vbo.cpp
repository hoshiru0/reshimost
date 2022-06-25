#include "vbo.hpp"
#include <glad/glad.h>
#include <iostream>

VBO::VBO() {
    create();
}
VBO::VBO(uint32_t vbo) : vbo(vbo) {}

void VBO::create() {
    glGenBuffers(1, &vbo);
}

void VBO::destroy() {
    glDeleteBuffers(1, &vbo);
}

VBO::~VBO() {
    destroy();
}

void VBO::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void VBO::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER , 0);
}

void VBO::bufferDataStatic(std::initializer_list<float> l) {
    bind();
    glBufferData(GL_ARRAY_BUFFER, l.size() * sizeof(float), l.begin(), GL_STATIC_DRAW);
}
void VBO::bufferDataDynamic(std::initializer_list<float> l) {
    bind();
    glBufferData(GL_ARRAY_BUFFER, l.size() * sizeof(float), l.begin(), GL_DYNAMIC_DRAW);
}
