#include "multirender.hpp"
#include <glad/glad.h>


InstancedModelRender::InstancedRender(Shader& shader, Attributes&& attributes, uint32_t draw_type) 
  : shader(&shader), 
    attributes(attributes),
    draw_type(draw_type) {

}

void InstancedModelRender::init() {
    shader->compile();
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLint pos = shader->getAttrib("model");
    glVertexAttribPointer(pos,  4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)0);
    glVertexAttribPointer(pos + 1, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (const void*) (4 * 4));
    glVertexAttribPointer(pos + 2, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (const void*) (4 * 8));
    glVertexAttribPointer(pos + 3, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (const void*) (4 * 12));

    glVertexAttribDivisor(pos, 1);
    glVertexAttribDivisor(pos + 1, 1);
    glVertexAttribDivisor(pos + 2, 1);
    glVertexAttribDivisor(pos + 3, 1);

    glEnableVertexAttribArray(pos);
    glEnableVertexAttribArray(pos + 1);
    glEnableVertexAttribArray(pos + 2);
    glEnableVertexAttribArray(pos + 3);

    //glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 2, example, GL_DYNAMIC_DRAW); // instances
    glEnableVertexAttribArray(pos);
    glVertexAttribDivisor(pos, 1);

    for (auto& attr : attributes) {
        uint32_t& vbo = VBOs[VBOs.size()];

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glBufferData(GL_ARRAY_BUFFER, attr.size, attr.data, attr.dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
        auto& attrib_info = shader->getAttribInfo(attr.name);
        glVertexAttribPointer(attrib_info.location, attrib_info.size, GL_FLOAT, GL_FALSE, attr.size, (void*)0);

        glEnableVertexAttribArray(attrib_info.location);

        auto loc = attrib_info.location;

        switch (attrib_info.type) {
          case GL_FLOAT_MAT4:
            glVertexAttribPointer(loc    , 4, attr.primitive, false, 16 * sizeof(float), 0);
            glVertexAttribPointer(loc + 1, 4, attr.primitive, false, 16 * sizeof(float), (const void*) (4 * 4));
            glVertexAttribPointer(loc + 2, 4, attr.primitive, false, 16 * sizeof(float), (const void*) (4 * 8));
            glVertexAttribPointer(loc + 3, 4, attr.primitive, false, 16 * sizeof(float), (const void*) (4 * 12));

            glEnableVertexAttribArray(loc + 1);
            glEnableVertexAttribArray(loc + 2);
            glEnableVertexAttribArray(loc + 3);
            break;

          case GL_FLOAT_VEC2:
            glVertexAttribPointer(loc, 2, attr.primitive, false, 0, 0);
            break;

          case GL_FLOAT_VEC3:
            glVertexAttribPointer(loc, 3, attr.primitive, false, 0, 0);
            break;

          case GL_FLOAT:
            glVertexAttribPointer(loc, 1, attr.primitive, false, 0, 0);
            break;
        }

        glEnableVertexAttribArray(loc);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind
    glBindVertexArray(0);
}


void InstancedRender::render() {
    glBindBuffer(GL_ARRAY_BUFFER, transform_VBO);
    //glBufferData(GL_ARRAY_BUFFER, transform_buffer.size()*sizeof(glm::vec2), transform_buffer.data(), GL_DYNAMIC_DRAW);
    shader->use();
    glBindVertexArray(VAO);

    //Transform2D::buffer.bind();
    //glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * instances.size(), instances.data(), GL_DYNAMIC_DRAW); // instances

    //glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * instances.size(), nullptr, GL_DYNAMIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * instances.size(), instances.data(), GL_DYNAMIC_DRAW);
    //glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec2) * instances.size(), instances.data());
    //std::cout << instances[0].x << std::endl;
    glDrawArraysInstanced(draw_type, 0, vert.size()/2, transform_buffer.size());
}
