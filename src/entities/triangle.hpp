#pragma once

#include <initializer_list>
#include <iostream>

#include <entity.hpp>
#include <scene.hpp>

struct Triangle : Entity {
    Triangle(Scene*);
    void move(void);
    void update(void);
    SpriteAnim forward;
    SpriteAnim back;
    SpriteAnim left;
    SpriteAnim right;
};
