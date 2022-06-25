#pragma once

#include <utility>
#include <vector>
#include <memory>
#include <array>
#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <glm/gtx/string_cast.hpp>

#include "camera.hpp"
#include "smartvector.hpp"
#include "transform.hpp"
#include "gl/shader.hpp"
#include "utility.hpp"
#include "gl/vao.hpp"
#include "gl/vbo.hpp"

extern Shader entity_shader;

struct EntityParams {
    Shader* shader {&entity_shader};
    std::initializer_list<float> vertices {
        -0.5f, -0.5f,
        -0.5f,  0.5f,
        0.5f,  0.5f,
        0.5f, -0.5f
    };
};


struct Entity : Transform {
    inline static uint32_t entity_count {};
    VAO vao;
    VBO vbo;
    EntityParams params;

    Entity(EntityParams&& params = EntityParams{});

    ~Entity() {}

    void updateEntity(void);
    virtual void update() {
        
    }
};

