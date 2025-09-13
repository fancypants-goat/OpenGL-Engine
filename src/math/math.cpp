//
// Created by eding on 12/09/2025.
//

#include <engine/math/math.h>

namespace engine::math
{
    float distance(const vec3& a, const vec3& b)
    {
        return vec3::distance(a, b);
    }

    float angle(const vec3& a, const vec3& b)
    {
        return vec3::angle(a, b);
    }

    float dot(const vec3& a, const vec3& b)
    {
        return vec3::dot(a, b);
    }

    vec3 cross(const vec3& a, const vec3& b)
    {
        return vec3::cross(a, b);
    }

    vec3 max(const vec3& a, const vec3& b)
    {
        return vec3::max(a, b);
    }

    vec3 min(const vec3& a, const vec3& b)
    {
        return vec3::min(a, b);
    }
}