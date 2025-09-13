//
// Created by michiel on 8/31/25.
//

#ifndef ENGINE_VEC3_H
#define ENGINE_VEC3_H

#include <glm/glm.hpp>

namespace engine::math
{
    struct vec3
    {
    public:
        vec3() = default;
        vec3(float x, float y, float z);
        explicit vec3(float scalar);

        float x = 0;
        float y = 0;
        float z = 0;

        const float& r = x;
        const float& g = y;
        const float& b = z;

        static const vec3 up;
        static const vec3 down;
        static const vec3 right;
        static const vec3 left;
        static const vec3 forwards;
        static const vec3 backwards;
        static const vec3 identity;
        static const vec3 zero;
        static const vec3 one;

        void normalize();
        vec3 normalized() const;
        float magnitude() const;

        float dot(const vec3& other) const;
        vec3 cross(const vec3& other) const;
        float angle(const vec3& other) const;

        glm::vec3 toGLM() const;

        static float angle(const vec3& a, const vec3& b);
        static float distance(const vec3& a, const vec3& b);
        static float dot(const vec3& a, const vec3& b);
        static vec3 cross(const vec3& a, const vec3& b);
        static vec3 max(const vec3& a, const vec3& b);
        static vec3 min(const vec3& a, const vec3& b);

        bool operator==(const vec3& rhs) const;
        bool operator!=(const vec3& rhs) const;
        bool operator<(const vec3& rhs) const;
        bool operator>(const vec3& rhs) const;
        bool operator<=(const vec3& rhs) const;
        bool operator>=(const vec3& rhs) const;

        bool operator==(const float& rhs) const;
        bool operator!=(const float& rhs) const;
        bool operator<(const float& rhs) const;
        bool operator>(const float& rhs) const;
        bool operator<=(const float& rhs) const;
        bool operator>=(const float& rhs) const;

        bool operator==(const int& rhs) const;
        bool operator!=(const int& rhs) const;
        bool operator<(const int& rhs) const;
        bool operator>(const int& rhs) const;
        bool operator<=(const int& rhs) const;
        bool operator>=(const int& rhs) const;

        vec3& operator=(const vec3& rhs);
        vec3 operator+(const vec3& rhs) const;
        vec3 operator-(const vec3& rhs) const;
        vec3 operator*(const vec3& rhs) const;
        vec3 operator/(const vec3& rhs) const;
        vec3& operator+=(const vec3& rhs);
        vec3& operator-=(const vec3& rhs);
        vec3& operator*=(const vec3& rhs);
        vec3& operator/=(const vec3& rhs);

        vec3 operator+(float rhs) const;
        vec3 operator-(float rhs) const;
        vec3 operator*(float rhs) const;
        vec3 operator/(float rhs) const;
        vec3& operator+=(float rhs);
        vec3& operator-=(float rhs);
        vec3& operator*=(float rhs);
        vec3& operator/=(float rhs);

        vec3 operator+(int rhs) const;
        vec3 operator-(int rhs) const;
        vec3 operator*(int rhs) const;
        vec3 operator/(int rhs) const;
        vec3& operator+=(int rhs);
        vec3& operator-=(int rhs);
        vec3& operator*=(int rhs);
        vec3& operator/=(int rhs);
    };
}


#endif //ENGINE_VEC3_H
