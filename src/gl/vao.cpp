#include "vao.hpp"
#include <glad/glad.h>

VAO::VAO() {
    glGenVertexArrays(1, &vao);
    bind();
}

void VAO::bind() {
    glBindVertexArray(vao);
}

void VAO::unbind() {
    glBindVertexArray(0);
}

VAO::~VAO() {
    glDeleteVertexArrays(1, &vao);
}