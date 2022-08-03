#include "text.hpp"
#include <gl/texture.hpp>
#include <gl/shader.hpp>

/*static Shader text_shader {
R"(#version 300 es
precision mediump float;
in vec2 a_vert;
in vec2 a_tex_coord;
out vec2 tex_coord;
uniform vec2 pos;
void main() {
    tex_coord = a_tex_coord;
    gl_Position = vec4(a_vert + pos, 0.f, 1.f);
}
)",
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
};
*/

Text::Text(Texture* texture, std::string_view text) : texture(texture), text(text) {
    create();
}

Text::Text(std::string_view text) : texture(current_texture), text(text) {
    create();
}

void Text::create() {
    //shared_vbo = text_shader.setAttribute({""}, std::initializer_list<T> buffer)
}

void Text::render() {
    texture->use();
   // text_shader.use();

    for (uint8_t c : text) {

    }
}
