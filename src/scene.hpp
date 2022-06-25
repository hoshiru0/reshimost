#pragma once
#include <memory>
#include <vector>
#include "entity.hpp"
#include "camera.hpp"

extern double delta_time;

struct Scene {
    std::vector<std::shared_ptr<Entity>> entities;

    template<typename T>
    std::shared_ptr<T> createEntity() {
        auto e = std::make_shared<T>();
        entities.emplace_back(e);
        return e;
    }

    void updateScene(void);
    virtual void update(void) {}
    void run(void);
    virtual ~Scene() = default;
};

extern std::unique_ptr<Scene> current_scene;

template<typename T>
void loadScene() {
    current_scene = std::make_unique<T>();
    current_scene->run();
}

