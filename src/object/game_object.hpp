#pragma once
#include "transform.hpp"

struct GameObject {
    Transform transform;
    uint32_t index;
    GameObject();
    virtual void render(void);

    void destroy(void); 
    ~GameObject();
};

