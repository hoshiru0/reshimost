#pragma once
#include "../entity.hpp"
#include <initializer_list>
#include <iostream>
#include "../scene.hpp"

struct Triangle : Entity {
    Triangle();
    void init(void);
    void move(void);
    void update(void);
};
