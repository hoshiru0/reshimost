#pragma once
#include <gl/shader.hpp>
#include <utility/fixedstring.hpp>
#include <utility/fromtemplate.hpp>
#include <utility/filtertuple.hpp>

template<FixedString... Fs>
struct Uniforms {

};

template<typename... Ts>
struct SimpleShader {
    using UNIF = filter1_tuple_t<std::tuple<Ts...>, [] <typename T> () {
        return is_from_ts_template_v<T, Uniforms>;
    }>;

    Shader shader {

    };
};

template<FixedString vs, FixedString fs>
Shader createSimpleShader() {
    return 
{R"(#version 300 es
precision mediump float;
in vec2 a_vert;
in vec2 a_tex_coord;
out vec2 tex_coord;
uniform mat4 u_MVP;
void main() {
    tex_coord = a_tex_coord;
    gl_Position = u_MVP * vec4(a_vert, 0.f, 1.f);
})",
R"(#version 300 es
precision mediump float;
in vec2 tex_coord;
out vec4 frag_color;

uniform sampler2D u_tex;
uniform float u_time;
uniform vec2 u_tex_size;
uniform vec2 u_tex_offset;

void main() {
    frag_color = texture(u_tex, tex_coord * u_tex_size + u_tex_offset);
    if (frag_color.a < 0.5f) {
        discard;
    }
})"
}
};