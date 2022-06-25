#pragma once
#include "../entity.hpp"
#include <initializer_list>
#include <iostream>
#include <glad/glad.h>
#include "../scene.hpp"

struct Triangle : Entity {
    Triangle();
    void update(void) override;
    void move(void);
};
