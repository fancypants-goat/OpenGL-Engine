#ifndef VERTEX_H
#define VERTEX_H

#include "math/vec3.h"


namespace engine
{
    struct Vertex {
        math::vec3 position;
        math::vec3 normal;
        glm::vec2 texCoord;
    };
}

#endif
