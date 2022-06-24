#include "../shader.hpp"

static Shader tshader {
R"(#version 300 es
precision mediump float;
in vec2 vert;
in vec2 pos;

void main() {
    vec2 poss = (vert+pos) * 0.1f;
    gl_Position = vec4(poss, 0.0, 1.0);
})",
R"(#version 300 es
precision mediump float;
out vec4 FragColor;
void main() {
    FragColor = vec4(1.0f, 0.0f, 1.0f, 1.0f);
})"
};

