#pragma once
#include <gl/texture.hpp>
#include <gl/vbo.hpp>

struct Text {
    Texture* texture;
    std::shared_ptr<VBO> shared_vbo;
    std::string text;
    Text(Texture* texture, std::string_view text);
    Text(std::string_view text);

    void create(void);
    void render(void);
};
