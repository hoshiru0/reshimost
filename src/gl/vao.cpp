#include <gl/vao.hpp>
#include <glad/glad.hpp>

VAO::VAO() {
    glGenVertexArrays(1, &vao);
}

void VAO::use() {
    glBindVertexArray(vao);
}

void VAO::unbind() {
    glBindVertexArray(0);
}

VAO::~VAO() {
    glDeleteVertexArrays(1, &vao);
}