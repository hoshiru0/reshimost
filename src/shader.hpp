#pragma once
#include <string_view>
#include <array>
#include <string>
#include <unordered_map>

#include "smartvector.hpp"
#include "utility.hpp"

class Shader {
    struct AttribInfo {
        uint32_t index;
        uint32_t location;
        uint32_t type;
        uint32_t size;
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

    void compile(void);
    void use(void);

    const AttribInfo& getAttribInfo(std::string) const;
    uint32_t getProgram(void) const;
    uint32_t getAttrib(std::string_view name) const;
    void destroy(void);
    ~Shader();
};
