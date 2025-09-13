//
// Created by michiel on 8/31/25.
//

#include <engine/math/vec3.h>

namespace engine::math
{
    const vec3 vec3::right = vec3(1.0f, 0.0f, 0.0f);
    const vec3 vec3::left = vec3(-1.0f, 0.0f, 0.0f);
    const vec3 vec3::up = vec3(0.0f, 1.0f, 0.0f);
    const vec3 vec3::down = vec3(0.0f, -1.0f, 0.0f);
    const vec3 vec3::forwards = vec3(0.0f, 0.0f, 1.0f);
    const vec3 vec3::backwards = vec3(0.0f, 1.0f, -1.0f);
    const vec3 vec3::identity = vec3(1);
    const vec3 vec3::zero = vec3(0);
    const vec3 vec3::one = vec3(1);

    vec3::vec3(const float x, const float y, const float z)
        : x(x), y(y), z(z)
    {
    }

    vec3::vec3(const float scalar)
        : x(scalar), y(scalar), z(scalar)
    {
    }

    void vec3::normalize()
    {
        x *=  magnitude();
        y *= magnitude();
        z *= magnitude();
    }

    vec3 vec3::normalized() const
    {
        return { x * magnitude(), y * magnitude(), z * magnitude() };
    }

    float vec3::magnitude() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    float vec3::dot(const vec3& other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    vec3 vec3::cross(const vec3& other) const
    {
        // a × b = ⟨(a₂b₃ - a₃b₂), (a₃b₁ - a₁b₃), (a₁b₂ - a₂b₁)⟩
        return { y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x };
    }

    float vec3::angle(const vec3& other) const
    {
        // angle == acos(a.b / amag * bmag)
        const float angle = dot(other) / (magnitude() * other.magnitude());
        return std::acos(angle);
    }

    glm::vec3 vec3::toGLM() const
    {
        return {x, y, z};
    }

    float vec3::distance(const vec3& a, const vec3& b)
    {
        return (a - b).magnitude();
    }

    float vec3::angle(const vec3& a, const vec3& b)
    {
        return a.angle(b);
    }

    float vec3::dot(const vec3& a, const vec3& b)
    {
        return a.dot(b);
    }

    vec3 vec3::cross(const vec3& a, const vec3& b)
    {
        return a.cross(b);
    }

    vec3 vec3::max(const vec3& a, const vec3& b)
    {
        if (a.magnitude() > b.magnitude())
            return a;

        return b;
    }

    vec3 vec3::min(const vec3& a, const vec3& b)
    {
        if (a.magnitude() < b.magnitude())
            return a;

        return b;
    }


    bool vec3::operator==(const vec3& rhs) const
    {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }

    bool vec3::operator!=(const vec3& rhs) const
    {
        return x != rhs.x || y != rhs.y || z != rhs.z;
    }

    bool vec3::operator<(const vec3& rhs) const
    {
        return magnitude() < rhs.magnitude();
    }

    bool vec3::operator>(const vec3& rhs) const
    {
        return magnitude() > rhs.magnitude();
    }

    bool vec3::operator<=(const vec3& rhs) const
    {
        return magnitude() <= rhs.magnitude();
    }

    bool vec3::operator>=(const vec3& rhs) const
    {
        return magnitude() >= rhs.magnitude();
    }

    bool vec3::operator==(const float& rhs) const
    {
        return magnitude() == rhs;
    }

    bool vec3::operator!=(const float& rhs) const
    {
        return magnitude() != rhs;
    }

    bool vec3::operator<(const float& rhs) const
    {
        return magnitude() < rhs;
    }

    bool vec3::operator>(const float& rhs) const
    {
        return magnitude() > rhs;
    }

    bool vec3::operator<=(const float& rhs) const
    {
        return magnitude() <= rhs;
    }

    bool vec3::operator>=(const float& rhs) const
    {
        return magnitude() >= rhs;
    }

    bool vec3::operator==(const int& rhs) const
    {
        return magnitude() == rhs;
    }

    bool vec3::operator!=(const int& rhs) const
    {
        return magnitude() != rhs;
    }

    bool vec3::operator<(const int& rhs) const
    {
        return magnitude() < rhs;
    }

    bool vec3::operator>(const int& rhs) const
    {
        return magnitude() > rhs;
    }

    bool vec3::operator<=(const int& rhs) const
    {
        return magnitude() <= rhs;
    }

    bool vec3::operator>=(const int& rhs) const
    {
        return magnitude() >= rhs;
    }

    vec3& vec3::operator=(const vec3& rhs)
    {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        return *this;
    }

    vec3 vec3::operator+(const vec3& rhs) const
    {
        return vec3(x + rhs.x, y + rhs.y, z + rhs.z);
    }

    vec3 vec3::operator-(const vec3& rhs) const
    {
        return vec3(x - rhs.x, y - rhs.y, z - rhs.z);
    }

    vec3 vec3::operator*(const vec3& rhs) const
    {
        return vec3(x * rhs.x, y * rhs.y, z * rhs.z);
    }

    vec3 vec3::operator/(const vec3& rhs) const
    {
        return vec3(x / rhs.x, y / rhs.y, z / rhs.z);
    }

    vec3& vec3::operator+=(const vec3& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    vec3& vec3::operator-=(const vec3& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    vec3& vec3::operator*=(const vec3& rhs)
    {
        x *= rhs.x;
        y *= rhs.y;
        z *= rhs.z;
        return *this;
    }

    vec3& vec3::operator/=(const vec3& rhs)
    {
        x /= rhs.x;
        y /= rhs.y;
        z /= rhs.z;
        return *this;
    }

    vec3 vec3::operator+(float rhs) const
    {
        return vec3(x + rhs, y + rhs, z + rhs);
    }

    vec3 vec3::operator-(float rhs) const
    {
        return vec3(x - rhs, y - rhs, z - rhs);
    }

    vec3 vec3::operator*(float rhs) const
    {
        return vec3(x * rhs, y * rhs, z * rhs);
    }

    vec3 vec3::operator/(float rhs) const
    {
        return vec3(x / rhs, y / rhs, z / rhs);
    }

    vec3& vec3::operator+=(float rhs)
    {
        x += rhs;
        y += rhs;
        z += rhs;
        return *this;
    }

    vec3& vec3::operator-=(float rhs)
    {
        x -= rhs;
        y -= rhs;
        z -= rhs;
        return *this;
    }

    vec3& vec3::operator*=(float rhs)
    {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        return *this;
    }

    vec3& vec3::operator/=(float rhs)
    {
        x /= rhs;
        y /= rhs;
        z /= rhs;
        return *this;
    }

    vec3 vec3::operator+(int rhs) const
    {
        return vec3(x+rhs, y+rhs, z+rhs);
    }

    vec3 vec3::operator-(int rhs) const
    {
        return vec3(x - rhs, y - rhs, z - rhs);
    }

    vec3 vec3::operator*(int rhs) const
    {
        return vec3(x * rhs, y * rhs, z * rhs);
    }

    vec3 vec3::operator/(int rhs) const
    {
        return vec3(x / rhs, y / rhs, z / rhs);
    }

    vec3& vec3::operator+=(int rhs)
    {
        x += rhs;
        y += rhs;
        z += rhs;
        return *this;
    }

    vec3& vec3::operator-=(int rhs)
    {
        x -= rhs;
        y -= rhs;
        z -= rhs;
        return *this;
    }

    vec3& vec3::operator*=(int rhs)
    {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        return *this;
    }

    vec3& vec3::operator/=(int rhs)
    {
        x /= rhs;
        y /= rhs;
        z /= rhs;
        return *this;
    }
}
