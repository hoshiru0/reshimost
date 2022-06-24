#pragma once
#include <memory>
#include <vector>
#include "entity.hpp"

struct Scene {
    std::vector<std::unique_ptr<Entity>> entities;
    
    template<typename T>
    void createEntity() {
        static int l = [] () { 
            if (!Entity::static_initialized<T>) {
                Entity::staticInit<T>();
            }
        }();
        entities.push_back(std::make_unique<T>());
    }

    void updateScene(void);
    virtual void update(void) {}
    void run(void);
};

extern std::unique_ptr<Scene> current_scene;

template<typename T>
void loadScene() {
    current_scene = std::make_unique<T>();
    current_scene->run();
}

