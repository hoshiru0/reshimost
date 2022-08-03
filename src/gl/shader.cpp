#include <gl/shader.hpp>
#include <glad/glad.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <util/terminate.hpp>

Shader* current_shader;

Shader::Shader(const char* vSource_, const char* fSource_) : vSource(vSource_), fSource(fSource_) {
    list.push_back(this);
    compile();
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

    auto setsize = [] (GLenum type, uint32_t& size) {
        switch (type) {
        case GL_FLOAT_VEC3:
            size = 3;
            break;
        case GL_FLOAT_MAT4:
            size = 4;
            break;
        case GL_FLOAT_VEC2:
            size = 2;
            break;
        case GL_SAMPLER_2D:
        case GL_FLOAT:
            size = 1;
            break;
        default:
            std::cerr << "udentified shader type: " << type << std::endl;
            break;
        }
    };

    GLint count;
    glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &count);
    for (int i {}; i < count; i++) {
        char name[16];
        GLenum type;
        int size;
        glGetActiveAttrib(program, (GLuint)i, sizeof(name), NULL, &size, &type, name);
        attribs[name].location = glGetAttribLocation(program, name);
        attribs[name].index = i;
        setsize(type, attribs[name].size);
        attribs[name].size *= size;
    }

    glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &count);
    for (int i{}; i < count; i++) {
        char name[16];
        GLenum type;
        glGetActiveUniform(program, (GLuint) i, sizeof(name), NULL, NULL, &type, name);
        uniforms[name].location = glGetUniformLocation(program, name);
        uniforms[name].index = i;
        uniforms[name].type = type;
        setsize(type, uniforms[name].size);
    }
}

void Shader::use() {
    glUseProgram(program);
    current_shader = this;
}

template<typename T>
void Shader::setAttribPointer(std::initializer_list<const char*> arr) {
    uint32_t size_row {};
    for (auto name : arr) {
        size_row += attribs[name].size;
    }
    uint32_t type {};
    if constexpr (std::is_same_v<T, float>) {
        type = GL_FLOAT;
    }

    uint32_t c {};
    for (auto name : arr) {
        uint32_t size = attribs[name].size;
        AttribInfo& info = attribs[name];
        glVertexAttribPointer(
            info.index, 
            size, 
            type, 
            GL_FALSE, 
            size_row * sizeof(T), 
            (void*)(c * sizeof(T))
        );
        glEnableVertexAttribArray(info.index);
        c += size;
    }
}

template<bool shared, typename T>
std::conditional_t<shared, std::shared_ptr<VBO>, VBO> Shader::setAttribute(std::initializer_list<const char*> arr, std::initializer_list<T> buffer, uint32_t draw_type) {
    std::conditional_t<shared, std::shared_ptr<VBO>, VBO> vbo;
    if constexpr (shared) {
        auto& weakptr = Shader::shared_vbo_table[(void*)buffer.begin()];
        vbo = weakptr.lock();
        if (!vbo) {
            vbo = std::make_shared<VBO>();
            weakptr = vbo;
            vbo->bufferData(buffer, draw_type);
        } else {
            vbo->use();
        }
    } else {
        vbo.bufferData(buffer, draw_type);
    }

    setAttribPointer<T>(arr);
    return vbo;
}

void Shader::uniform(const char* name, const glm::mat4& v) {
    glUniformMatrix4fv(uniforms[name].location, 1, GL_FALSE, glm::value_ptr(v));
}

void Shader::uniform(const char* name, const int v) {
    glUniform1i(uniforms[name].location, v);
}

void Shader::uniform(const char* name, const glm::vec2& v) {
    glUniform2fv(uniforms[name].location, 1, glm::value_ptr(v));
}

void Shader::uniform(const char* name, const float v) {
    glUniform1f(uniforms[name].location, v);
}

void Shader::uniform(const char* name, const glm::uvec2& v) {
    glUniform2uiv(uniforms[name].location, 1, glm::value_ptr(v));
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

template VBO Shader::setAttribute<false>(std::initializer_list<const char*>, std::initializer_list<float>, uint32_t);
template std::shared_ptr<VBO> Shader::setAttribute<true>(std::initializer_list<const char*>, std::initializer_list<float>, uint32_t);
