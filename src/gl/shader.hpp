#pragma once
#include <string_view>
#include <array>
#include <string>
#include <unordered_map>
#include <glm/mat4x4.hpp>

#include "../smartvector.hpp"
#include "../utility.hpp"
#include "vbo.hpp"

class Shader {
    struct AttribInfo {
        uint32_t index;
        uint32_t location;
        uint32_t type;
        uint32_t size;
        uint32_t unique_vbo {};
    };
    std::unordered_map<std::string, AttribInfo> attribs;

    inline static SmartVector<Shader*, true> list {};
    uint32_t compiled_shader_index;
    uint32_t vs;
    uint32_t fs;
    uint32_t program {};
    bool compiled {};
    const char* vSource;
    const char* fSource;
public:
    Shader(const char* vSource_, const char* fSource_);

    static void compileAll(void);
    void compile(void);
    void use(void);
    uint32_t setAttribute(const char* name, std::initializer_list<float> buffer, int n, bool dynamic = false, uint32_t type = 0x1406);
    uint32_t setAttributeOnce(const char* name, std::initializer_list<float> buffer, int n, bool dynamic = false, uint32_t type = 0x1406);

    void uniformMat4f(const char* name, glm::mat4& m);

    const AttribInfo& getAttribInfo(const char*) const;
    uint32_t getProgram(void) const;
    uint32_t getAttrib(const char*) const;
    void destroy(void);
    ~Shader();
};
