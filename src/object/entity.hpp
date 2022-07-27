#pragma once
#include <cstdint>

#include "camera.hpp"
#include "transform.hpp"

#include <sprite/sprite.hpp>
#include <gl/shader.hpp>
#include <gl/vao.hpp>
#include <gl/vbo.hpp>
#include <gl/texture.hpp>


struct Entity {
    Transform transform;
    inline static uint32_t entity_count {};
    uint32_t index;
    Sprite* sprites {};
    Shader* shader;
    VAO vao;
    std::shared_ptr<VBO> shared_vbo_vertex;

    Entity();

    void initEntity(void);
    virtual void initRender(void);
    void setSpriteAnim(Sprite&);

    ~Entity() {}

    void updateEntity(void);
    virtual void updateRender(void);
    virtual void update(void);

    void destroy(void);
};

