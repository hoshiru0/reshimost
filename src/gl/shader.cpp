#include "shader.hpp"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const char* vSource_, const char* fSource_) : vSource(vSource_), fSource(fSource_) {
    list.push_back(this);
}

void Shader::compileAll() {
    std::cout << "compiling shaders... " << std::endl;
    for (auto& s : list) {
        s->compile();
    }
    std::cout << "done" << std::endl;
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
    for (int i {}; i < count; i++) {
        char name[16];
        GLenum type;
        glGetActiveAttrib(program, (GLuint)i, sizeof(name), NULL, NULL, &type, name);
        attribs[name].location = glGetAttribLocation(program, name);
        attribs[name].index = i;
    }
}

void Shader::use() {
    glUseProgram(program);
}

uint32_t Shader::setAttribute(const char* name, std::initializer_list<float> buffer, int n, bool dynamic, uint32_t type) {
    uint32_t vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(float), buffer.begin(), dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
    
    uint32_t index = attribs[name].index;
    glVertexAttribPointer(index, n, type, GL_FALSE, n * sizeof(float), 0);
    glEnableVertexAttribArray(index);    
    
    return vbo;
}

std::shared_ptr<VBO> Shader::setSharedAttribute(const char* name, std::initializer_list<float> buffer, int n, bool dynamic, uint32_t type) {
    AttribInfo& info = attribs[name];
    uint32_t index = attribs[name].index;

    auto vbo = info.vbo.lock();
    if (!vbo) { 
        vbo = std::make_shared<VBO>();
        if (dynamic) {
            vbo->bufferDataDynamic(buffer);
        } else {
            vbo->bufferDataStatic(buffer);
        }
    } else { // Reuse vbo
        vbo->bind();
    }

    glVertexAttribPointer(index, n, type, GL_FALSE, n * sizeof(float), 0);
    glEnableVertexAttribArray(index);

    return vbo;
}

void Shader::uniformMat4f(const char* name, glm::mat4 &m) {
    glUniformMatrix4fv(attribs[name].location, 1, GL_FALSE, glm::value_ptr(m));
}

uint32_t Shader::getProgram() const {
    return program;
}

uint32_t Shader::getAttrib(const char* name) const {
    return glGetAttribLocation(program, name);
}

const Shader::AttribInfo& Shader::getAttribInfo(const char* name) const {
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
