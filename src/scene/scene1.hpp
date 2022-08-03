#pragma once
#include <memory>
#include <gui/text.hpp>
#include <object/pacman.hpp>

#include "scene.hpp"

struct Scene1 : Scene<Pacman> {
    std::shared_ptr<Pacman> current { createEntity<Pacman>() };
    Scene1();
    void update();
};
