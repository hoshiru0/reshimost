#pragma once

#include <utility>
#include <vector>
#include <memory>
#include <array>
#include <glad/glad.h>

#include "smartvector.hpp"
#include "transform.hpp"
#include "shader.hpp"
#include "utility.hpp"
#include "multirender.hpp"



struct Entity {
    inline static Shader shader {
        R"(#version 300 es
        precision mediump float;
        in vec2 vert;
        in mat4 transform;

        void main() {
            gl_Position = transform * vec4(0.0, 0.0, 0.0, 1.0);
        })",
        R"(#version 300 es
        precision mediump float;
        out vec4 FragColor;
        void main() {
            FragColor = vec4(1.0f, 0.0f, 1.0f, 1.0f);
        })"
    };

    template<typename T>
    inline static MultiRender multi_render { T::shader };

    inline static std::initializer_list<std::pair<const char*, std::initializer_list<float>>> attributes {
        {"vert", {1.f,2.f,3.f}},
        {"hla2", {2,3,4,5,6,7}}
    };

    

    inline static std::initializer_list<float> vert {
        -0.5f, -0.5f,
        -0.5f,  0.5f,
        0.5f,  0.5f,
        0.5f, -0.5f
    };

    template<typename T>
    inline static SmartVector<glm::mat4> transform_buffer;

    template<typename T>
    inline static bool static_initialized {};

    template<typename T>
    static void staticInit() {
    }

    template<typename T>
    static void staticUpdate() {
        multi_render<T>.render();
    }

    virtual void update() {

    }
};

