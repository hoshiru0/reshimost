#pragma once
#include "../scene.hpp"
#include "../entities/triangle.hpp"


struct Scene1 : Scene {
    Scene1() {
        createEntity<Triangle>();
        createEntity<Triangle>();
    }

    void update() {
    }
};