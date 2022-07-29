#pragma once
#include <initializer_list>
#include <iostream>

#include "entity.hpp"

#include <scene/scene1.hpp>
#include <control/input.hpp>

struct Ghost : Entity {
    Sprite s;

    Ghost(Scene* scene) : s(
        scene->cast<Scene1>().atlas1,
        {14, 14},
        offsets<glm::uvec2{4, 65}>,
        0
    ) {
        setSprite(s);
    }
};
