/*
#pragma once
#include <utility/fixedstring.hpp>
#include <gl/texture.hpp>

template<FixedString... S>
struct TextureLoader {
    TextureLoader() {
        //(textures<S>.operator=(std::make_unique<Texture>(S)), ...);
        (textures<S>.create(), ...);
        (textures<S>.bindImage(S), ...);
    }
    ~TextureLoader() {
        (textures<S>.destroy(), ...);
    }
};

*/