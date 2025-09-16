#ifndef VERTEX_H
#define VERTEX_H

#include "math/math.h"


namespace engine
{
    struct Vertex {
        math::vec3 position;
        math::vec3 normal;
        math::vec2 texCoord;
    };
}

#endif
