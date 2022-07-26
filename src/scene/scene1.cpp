#include "scene1.hpp"
#include <object/pacman.hpp>
#include <control/input.hpp>

Scene1::Scene1() {
    current = createEntity<Pacman>();
}

void Scene1::update() {
    if (input.getKey(MOUSE_LEFT)) {
        auto ptr = createEntity<Pacman>();
        if (auto c = current.lock()) {
            ptr->transform = c->transform;
        }
        current = ptr;
    }
    if (input.getKey(MOUSE_RIGHT)) {
        if (current_scene->entities.size() > 1) {
            current_scene->entities.pop_back();
            current = std::static_pointer_cast<Pacman>(current_scene->entities.back());
        }
    }

    if (auto c = current.lock()) {
        c->move();
    }
}
