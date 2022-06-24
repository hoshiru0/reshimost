#include "shader.hpp"
#include <glm/ext/matrix_float4x4.hpp>
#include <string>
#include <array>
#include <tuple>

#include "smartvector.hpp"

struct Attribute {
    std::string name;
    uint32_t size;
    void* data;
    uint32_t primitive { 0x1406 };
    bool dynamic {false};
};

using Attributes = std::initializer_list<Attribute>;

struct InstancedModelRender {
    uint32_t VAO;
    uint32_t transform_VBO;
    SmartVector<uint32_t, false> VBOs;
    SmartVector<glm::mat4, false> a;
    
    Shader* shader;
    Attributes attributes;
    uint32_t draw_type;

    InstancedModelRender(Shader& shader, Attributes&&, uint32_t draw_type = 4);
    void init(void);
    void render(void);
};
