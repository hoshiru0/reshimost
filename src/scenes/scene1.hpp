#pragma once
#include <memory>

#include <scene.hpp>
#include <entities/triangle.hpp>
#include <input.hpp>
#include <entities/test.hpp>
//#include <textureloader.hpp>
#include <spritesheet.hpp>
#include <sprite.hpp>

struct Scene1 : Scene {
    Texture atlas1 {"gentoo"};
    
    //Sprite gentoo {"gentoo"};
    std::weak_ptr<Triangle> current;
    Scene1() {
        //createEntity<Test>();
        //createEntity<Triangle>();
        current = createEntity<Triangle>();
    }

    void update() {
        if (input.getKeyDown(MOUSE_LEFT)) {
            auto ptr = createEntity<Triangle>();
            if (auto c = current.lock()) {
                ptr->position = c->position;
                ptr->rotation = c->rotation;
                ptr->scale = c->scale;
                ptr->sprites = c->sprites;
            }
            current = ptr;
        } 
        if (input.getKey(MOUSE_RIGHT)) {
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
