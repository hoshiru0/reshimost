#include "game_object.hpp"
#include <scene/scene.hpp>


void GameObject::destroy() {
    current_scene->destroyObject(*this);
}