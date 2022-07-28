#pragma once
#include <memory>
#include <util/smartvector.hpp>
#include <object/entity.hpp>
#include <object/camera.hpp>

extern double delta_time;
extern double current_time;

struct Scene {
    //Textures textures;
    Camera camera;
    SmartVector<std::shared_ptr<Entity>, true> entities;
    template<typename T>
    std::shared_ptr<T> createEntity() {
        auto e = std::make_shared<T>(this);
        entities.emplace_back(e);
        e->index = entities.size()-1;
        return e;
    }

    template<typename T>
    T& cast() {
        return static_cast<T&>(*this);
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

