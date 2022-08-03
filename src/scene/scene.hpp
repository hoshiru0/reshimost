#pragma once
#include <memory>
#include <util/smartvector.hpp>
#include <util/constexpr_for.hpp>
#include <util/tuple_utils.hpp>
#include <util/pretty.hpp>
#include <object/camera.hpp>
#include <object/entity.hpp>

struct SceneBase;
extern double delta_time;
extern double current_time;
extern SceneBase* current_scene;

struct SceneBase {
    Camera camera;

    SceneBase(void);

    template<typename T>
    T& cast() {
        return static_cast<T&>(*this);
    }

    //void destroyObject(GameObject& object);
    virtual void updateScene(void) {}
    virtual void update(void) {}
    
    void run(void);
    virtual ~SceneBase() = default;
};

template<typename... Ts>
struct Scene : SceneBase {
    std::tuple<typename Ts::Props...> entity_props {
        ((typename Ts::Props*) 0, *this)...
    };

    template<FixedString s, typename T>
    struct FixedString_T {
        static constexpr FixedString str { s };
        T value;
    };

    using Textures = norepeated_tuple_t<std::tuple<FixedString_T<Ts::Props::texture_name, Texture>...>>;
    Textures textures;

    Scene() {
        constexpr_for(int i=0, i<std::tuple_size_v<Textures>, i+1, 
            auto& x = std::get<i>(textures); 
            x.value.bindImage(std::remove_reference_t<decltype(x)>::str);
        );
    }

    ~Scene() {
    }


    template<FixedString str>
    Texture& getTexture() {
        return std::get<FixedString_T<str, Texture>>(textures).value;
    }

    void updateScene() {
        camera.update();
        update();
        constexpr_for(int i=0, i<sizeof...(Ts), i+1, 
            using iT = std::tuple_element_t<i AND std::tuple<Ts...>>;
            auto& props = std::get<i>(entity_props);
            props.update();
        );
    }

    template<typename T>
    void destroyObject(T& obj) {
    }

    template<typename T>
    std::shared_ptr<T> createEntity() {
        auto& props = std::get<typename T::Props>(entity_props);
        auto e = std::make_shared<T>();
        props.entities.emplace_back(e);
        e->index = props.entities.size();
        return e;
        //return .emplace_back();
    }
};

template<typename T>
void loadScene() {
    static std::unique_ptr<SceneBase> scene;
    scene = std::make_unique<T>();
    scene->run();
}

