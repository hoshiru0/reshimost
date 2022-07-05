#include <entities/triangle.hpp>
#include <input.hpp>
#include <gl/texture.hpp>

#include <gl/shader.hpp>
#include <glad/glad.hpp>

Triangle::Triangle() {
    Entity::texture = &textures<"gentoo">;
}

void Triangle::update() {
    //glLineWidth(5.f);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void Triangle::move() {
    float velocity = 5.0f;
    static uint32_t current_distro {};
    static std::initializer_list<Texture*>  avaliable_distros {
        &textures<"gentoo">,
        &textures<"arch">,
        &textures<"debian">
    };
    if (input.getKey(KEY_A)) {
        position.x -= delta_time * velocity;
    }
    if (input.getKey(KEY_D)) {
        position.x += delta_time * velocity;
    }
    if (input.getKey(KEY_W)) {
        position.y += delta_time * velocity;
    }
    if (input.getKey(KEY_S)) {
        position.y -= delta_time * velocity;
    }
    if (input.getKey(KEY_LEFT)) {
        scale.x += delta_time * velocity;
    }
    if (input.getKey(KEY_RIGHT)) {
        scale.x -= delta_time * velocity;
    }
    if (input.getKey(KEY_UP)) {
        scale.y += delta_time * velocity;
    }
    if (input.getKey(KEY_DOWN)) {
        scale.y -= delta_time * velocity;
    }
    if (input.getKeyDown(KEY_DELETE)) {
        destroy();
        return;
    }
    if (input.getKeyDown(KEY_C)) {
        current_distro = (++current_distro % avaliable_distros.size());
        Entity::texture = *(avaliable_distros.begin()+current_distro);
    }
    //rotation += delta_time * 500.f;
}
