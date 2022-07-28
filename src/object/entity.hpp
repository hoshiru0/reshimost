#pragma once
#include <cstdint>

#include "camera.hpp"
#include "game_object.hpp"

#include <sprite/sprite.hpp>
#include <gl/shader.hpp>
#include <gl/vao.hpp>
#include <gl/vbo.hpp>
#include <gl/texture.hpp>


struct Entity : GameObject {
    inline static uint32_t entity_count {};
    uint32_t index;
    Sprite* sprites {};
    Shader* shader;
    VAO vao;
    std::shared_ptr<VBO> shared_vbo_vertex;

    Entity();

    void setSpriteAnim(Sprite&);

    virtual ~Entity();

    void updateEntity(void);
    virtual void update(void);
    virtual void render(void);
    void destroy(void);
};

