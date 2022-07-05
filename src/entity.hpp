#pragma once
#include <cstdint>

#include <camera.hpp>
#include <transform.hpp>
#include <gl/shader.hpp>
#include <gl/vao.hpp>
#include <gl/vbo.hpp>
#include <gl/texture.hpp>

struct Entity : Transform {
    inline static uint32_t entity_count {};
    uint32_t index;
    Shader* shader;
    Texture* texture;
    VAO vao;
    std::shared_ptr<VBO> shared_vbo_vertex;

    Entity();

    void initEntity(void);
    virtual void init();

    ~Entity() {}

    void updateEntity(void);
    virtual void update(void);

    void destroy(void);
};

