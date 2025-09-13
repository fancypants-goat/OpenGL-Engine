//
// Created by eding on 12/09/2025.
//

#ifndef ENGINE_MATH_H
#define ENGINE_MATH_H

#include "vec3.h"
#include "vec2.h"

namespace engine::math
{
    static float distance(const vec3& a, const vec3& b);
    static float angle(const vec3& a, const vec3& b);
    static float dot(const vec3& a, const vec3& b);
    static vec3 cross(const vec3& a, const vec3& b);
    static vec3 max(const vec3& a, const vec3& b);
    static vec3 min(const vec3& a, const vec3& b);
}

#endif //ENGINE_MATH_H