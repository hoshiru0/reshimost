#pragma once
#include <cstdint>

#include "camera.hpp"
#include "game_object.hpp"
#include "util/fixedstring.hpp"

#include <sprite/sprite.hpp>
#include <gl/shader.hpp>
#include <gl/vao.hpp>
#include <gl/vbo.hpp>
#include <gl/texture.hpp>
#include <glad/glad.hpp>
#include <scene/scene.hpp>

extern double delta_time;
extern double delta_time;

template<FixedString str>
struct TextureName {
    static constexpr FixedString value { str };
};

inline static std::initializer_list<float> entity_vertices {
    -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f,   1.0f, 1.0f,
    0.5f, 0.5f,    1.0f, 0.0f,
    -0.5f, 0.5f,   0.0f, 0.0f
};

inline static const char* entity_vs {
R"(#version 300 es
precision mediump float;
in vec2 a_vert;
in vec2 a_tex_coord;
out vec2 tex_coord;
uniform mat4 u_MVP;
void main() {
    tex_coord = a_tex_coord;
    gl_Position = u_MVP * vec4(a_vert, 0.f, 1.f);
}
)"
};

inline static const char* entity_fs {
R"(#version 300 es
precision mediump float;
in vec2 tex_coord;
out vec4 frag_color;

uniform sampler2D u_tex;
uniform float u_time;
uniform vec2 u_tex_size;
uniform vec2 u_tex_offset;

void main() {
    frag_color = texture(u_tex, tex_coord * u_tex_size + u_tex_offset);
    if (frag_color.a < 0.5f) {
        discard;
    }
})"
};

struct Entity : GameObject {
    Sprite* sprite;

    Entity(void);
    ~Entity();

    template<typename T, typename tn>
    struct DefineEntity {
        SmartVector<std::shared_ptr<T>, true> entities;
        static constexpr FixedString texture_name { tn::value };
        Shader shader { entity_vs, entity_fs };
        Texture* texture;
        VAO vao;
        VBO vbo {
            shader.setAttribute({"a_vert", "a_tex_coord"}, entity_vertices)
        };

        DefineEntity(auto& s) {
            pretty(s);
            texture = &s.template getTexture<texture_name>();
        }

        void update() {
            shader.use();
            vao.use();
            texture->use();
            shader.uniform("u_tex_size", glm::vec2(1, 1));
            // Update entities
            for (auto& e : entities) {
                e->update();
            }
        }
    };

    //using Props = DefineEntity<TextureName<"">>;

    //void setSprite(Sprite&);
    void update(void);
    void render(void);
};
