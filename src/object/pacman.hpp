#pragma once
#include <initializer_list>
#include <iostream>

#include "entity.hpp"

#include <control/input.hpp>

struct Pacman : Entity {
    Sprite sprite {
        {15, 15},
        offsets<{4,0},{20,0},{36,0}>,
        8
    };

    Pacman() {
    }

    using Props = DefineEntity<
        Pacman,
        TextureName<"sprites">
    >;

    void update() {
        sprite.use();
        render();
    }

    void move() {
        float velocity = 5.0f;
        if (input.getKey(KEY_A)) {
            transform.position.x -= delta_time * velocity;
            transform.rotation = 0;
            transform.scale.x = std::abs(transform.scale.x) * -1;
        }
        if (input.getKey(KEY_D)) {
            transform.position.x += delta_time * velocity;
            transform.rotation = 0;
            transform.scale.x = std::abs(transform.scale.x);
        }
        if (input.getKey(KEY_W)) {
            transform.position.y += delta_time * velocity;
            transform.scale.x = std::abs(transform.scale.x);
            transform.rotation = 90;
        }
        if (input.getKey(KEY_S)) {
            transform.position.y -= delta_time * velocity;
            transform.scale.x = std::abs(transform.scale.x);
            transform.rotation = -90;
        }
        if (input.getKey(KEY_LEFT)) {
            transform.scale.x += delta_time * velocity;
        }
        if (input.getKey(KEY_RIGHT)) {
            transform.scale.x -= delta_time * velocity;
        }
        if (input.getKey(KEY_UP)) {
            transform.scale.y += delta_time * velocity;
        }
        if (input.getKey(KEY_DOWN)) {
            transform.scale.y -= delta_time * velocity;
        }
        if (input.getKeyDown(KEY_DELETE)) {
            destroy();
            return;
        }
    }
};
