#pragma once
#include <initializer_list>
#include <iostream>

#include "entity.hpp"

#include <scene/scene1.hpp>
#include <control/input.hpp>

struct Pacman : Entity {
    SpriteAnim forward;

    Pacman(Scene* scene) : forward(
        &scene->cast<Scene1>().atlas1,
        {15, 15},
        offsets<{4, 0}, {20, 0}, {36, 0}>,
        1./10
    ) {
        setSpriteAnim(forward);
    }
    void move() {
        float velocity = 5.0f;

        if (input.getKey(KEY_A)) {
            position.x -= delta_time * velocity;
            rotation = 0;
            scale.x = abs(scale.x) * -1;
        }
        if (input.getKey(KEY_D)) {
            position.x += delta_time * velocity;
            rotation = 0;
            scale.x = abs(scale.x);
        }
        if (input.getKey(KEY_W)) {
            position.y += delta_time * velocity;
            scale.x = abs(scale.x);
            rotation = 90;
        }
        if (input.getKey(KEY_S)) {
            position.y -= delta_time * velocity;
            scale.x = abs(scale.x);
            rotation = -90;
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
    }
};
