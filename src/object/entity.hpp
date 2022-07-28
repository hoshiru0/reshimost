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
    Sprite* sprites {};
    Shader* shader;
    VAO vao;
    std::shared_ptr<VBO> shared_vbo_vertex;

    Entity();
    ~Entity();

    void setSprite(Sprite&);
    void update(void);
    void render(void);
    void updateMVP(void);
};

