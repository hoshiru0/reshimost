#pragma once

#include <initializer_list>
#include <iostream>

#include <entity.hpp>
#include <scene.hpp>

struct Triangle : Entity {
    Triangle();
    void move(void);
    void update(void);
};
