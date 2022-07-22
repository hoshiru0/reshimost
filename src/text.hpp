#pragma once
#include <gl/texture.hpp>

struct Text {
    Texture* texture;
    std::string text;
    Text(Texture* texture, std::string_view text);
};
