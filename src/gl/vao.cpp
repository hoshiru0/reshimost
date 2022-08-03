#include <gl/vao.hpp>
#include <glad/glad.hpp>

VAO::VAO() {
    create();
    use();
}

VAO::VAO(uint32_t id) : id(id) {
}

void VAO::create() {
    glGenVertexArrays(1, &id);
}

void VAO::destroy() {
    if (id) {
        glDeleteVertexArrays(1, &id);
        id = 0;
    }
}

void VAO::use() {
    glBindVertexArray(id);
}

void VAO::unbind() {
    glBindVertexArray(0);
}

VAO::~VAO() {
    destroy();
}
