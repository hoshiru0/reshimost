#pragma once
#include <memory>
#include "../scene.hpp"
#include "../entities/triangle.hpp"
#include "../input.hpp"
#include "../entities/test.hpp"

struct Scene1 : Scene {
    std::weak_ptr<Triangle> current;
    Scene1() {
        createEntity<Test>();
        //createEntity<Triangle>();
        current = createEntity<Triangle>();
    }

    void update() {
        if (input.getMouseLeft()) {
            glm::vec3 position;
            float rotation;
            if (auto c = current.lock()) {
                position = c->position;
                rotation = c->rotation;
            }
            auto ptr = createEntity<Triangle>();
            ptr->position = position;
            ptr->rotation = rotation;
            current = ptr;
        } 
        if (input.getMouseRight()) {
            if (current_scene->entities.size() > 1) {
                current_scene->entities.pop_back();
                current = std::static_pointer_cast<Triangle>(current_scene->entities.back());
            }
        }

        if (auto c = current.lock()) {
            c->move();
        }
    }
};