#pragma once
#include <memory>

#include <scene.hpp>
#include <input.hpp>
#include <spritesheet.hpp>
#include <sprite.hpp>

class Pacman;

struct Scene1 : Scene {
    Texture atlas1 {"sprites"};
    
    std::weak_ptr<Pacman> current;
    Scene1();
    void update();
};
