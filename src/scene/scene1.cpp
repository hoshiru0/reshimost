#include "scene1.hpp"
#include <object/pacman.hpp>
#include <control/input.hpp>
//#include <object/ghost.hpp>

Scene1::Scene1() {

    //current = createObject<Pacman>();
}

void Scene1::update() {
    current->move();
    if (input.getKey(MOUSE_LEFT)) {
        auto ptr = createEntity<Pacman>();
        ptr->transform = current->transform;
        current = ptr;
    }
    /*
    if (input.getKey(MOUSE_RIGHT)) {
        if (current_scene->objects.size() > 1) {
            current_scene->objects.pop_back();
            current = std::static_pointer_cast<Pacman>(current_scene->objects.back());
        }
    }

    if (auto c = current.lock()) {
        c->move();
    }*/
}
