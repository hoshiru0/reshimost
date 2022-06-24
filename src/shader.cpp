#include "shader.hpp"
#include <glad/glad.h>

Shader::Shader(const char* vSource_, const char* fSource_) : vSource(vSource_), fSource(fSource_) {
}

void Shader::compile() {
    vs = glCreateShader(GL_VERTEX_SHADER);
    fs = glCreateShader(GL_FRAGMENT_SHADER);
    program = glCreateProgram();
    glShaderSource(vs, 1, &vSource, NULL);
    glShaderSource(fs, 1, &fSource, NULL);
    glCompileShader(vs);
    glCompileShader(fs);

    // Check errors
    int success;
    char infoLog[512];
    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vs, 512, NULL, infoLog);
        terminate("ERROR: Compiling vertex shader ", infoLog);
    }

    glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vs, 512, NULL, infoLog);
        terminate("ERROR: Compiling fragment shader ", infoLog);
    }

    // Link shaders
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    GLint count;
    glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &count);
    for (uint32_t i {}; i < count; i++) {
        char name[16];
        GLenum type;
        glGetActiveAttrib(program, (GLuint)i, sizeof(name), NULL, NULL, &type, name);
        attribs[name].location = glGetAttribLocation(program, name);
        attribs[name].index = i;

        uint32_t size {};
        switch (type) {
            case GL_FLOAT_VEC2:
                size = 2;
                break;
            case GL_FLOAT_VEC3:
                size = 3;
                break;
            case GL_FLOAT_VEC4:
                size = 4;
                break;
            case GL_FLOAT_MAT4:
                size = 4;
                break;
        }
        attribs[name].size = size;
    }
}

void Shader::use() {
    glUseProgram(program);
}

uint32_t Shader::getProgram() const {
    return program;
}

uint32_t Shader::getAttrib(std::string_view name) const {
    return glGetAttribLocation(program, name.data());
}

const Shader::AttribInfo& Shader::getAttribInfo(std::string name) const {
    return attribs.at(name);
}

void Shader::destroy() {
    glDeleteProgram(program);
}

Shader::~Shader() {
    if (compiled) {
        destroy();
    }
}
