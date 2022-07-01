#pragma once
#include <memory>

#include <utility/smartvector.hpp>
#include <entity.hpp>
#include <camera.hpp>
#include <textureloader.hpp>

extern double delta_time;
extern double current_time;

struct Scene {
    SmartVector<std::shared_ptr<Entity>, true> entities;
    template<typename T>
    std::shared_ptr<T> createEntity() {
        auto e = std::make_shared<T>();
        entities.emplace_back(e);
        e->index = entities.size()-1;
        e->initEntity();
        return e;
    }

    void destroyEntity(uint32_t index);
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

