#pragma once
#include <memory>
#include <gui/text.hpp>

#include "scene.hpp"

struct Pacman;

struct Scene1 : Scene {
    Texture atlas1 {"sprites"};
    Texture font {"font"};
    Text hola {"hola mi gratuito"};
    
    std::weak_ptr<Pacman> current;
    Scene1();
    void update();
};
