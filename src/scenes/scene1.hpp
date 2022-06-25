#pragma once
#include <memory>
#include "../scene.hpp"
#include "../entities/triangle.hpp"
#include "../input.hpp"

struct Scene1 : Scene {
    std::shared_ptr<Triangle> current;
    Scene1() {
        //createEntity<Triangle>();
        current = createEntity<Triangle>();
    }

    void update() {
        if (input.getMouseLeft()) {
            auto pos = current->position;
            auto rot = current->rotation;
            current = createEntity<Triangle>();
            current->position = pos;
            current->rotation = rot;
        } 
        if (input.getMouseRight()) {
            if (current_scene->entities.size()) {
                current_scene->entities.pop_back();
            }
        }

        current->move();
        
    }
};