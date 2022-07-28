#pragma once
#include "transform.hpp"

struct GameObject {
    Transform transform;
    uint32_t index;

    virtual void update(void) = 0;
    virtual void render(void) = 0;

    void destroy(void);
};

