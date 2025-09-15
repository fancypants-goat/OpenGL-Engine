//
// Created by michiel on 9/14/25.
//

#ifndef ENGINE_VEC3_H
#define ENGINE_VEC3_H

#include <bits/stdc++.h>
#include <glm/glm.hpp>

namespace engine::math {
	struct vec3
	{
		float x, y, z;

		constexpr vec3() : x(0), y(0), z(0) {}
		constexpr vec3(float x, float y, float z) : x(x), y(y), z(z) {}
		explicit constexpr vec3(float scalar) : x(scalar), y(scalar), z(scalar) {}

//		----- DIRECTIONS / CONSTANTS -----
		struct c;

//		----- MATH HELPER METHODS -----
		[[nodiscard]] float magnitude() const
		{
			return std::sqrt(x * x + y * y + z * z);
		}

		void normalize()
		{
			float mag = magnitude();
			*this /= mag;
		}

		[[nodiscard]] vec3 normalized() const
		{
			return *this / magnitude();
		}

		[[nodiscard]] float dot(const vec3& other) const
		{
			return x * other.x + y * other.y + z * other.z;
		}

		[[nodiscard]] vec3 cross(const vec3& other) const
		{
			return vec3(y*other.z- z*other.y, z*other.x - x*other.z, x*other.y - y*other.x);
		}

		[[nodiscard]] float angle(const vec3& other) const
		{
			return std::acos(dot(other) / (magnitude() * other.magnitude()));
		}

		[[nodiscard]] float distance(const vec3& other) const
		{
			float dx = x - other.x;
			float dy = y - other.y;
			float dz = z - other.z;
			return std::sqrt(dx*dx + dy*dy + dz*dz);
		}

		[[nodiscard]] glm::vec3 toGLM() const
		{
			return {x, y, z};
		}

		static float dot(const vec3& a, const vec3& b) { return a.dot(b); }
		static vec3 cross(const vec3& a, const vec3& b) { return a.cross(b); }
		static float angle(const vec3& a, const vec3& b) { return a.angle(b); }
		static float distance(const vec3& a, const vec3& b) { return a.distance(b); }


//		----- ARITHMETIC OPERATORS -----
		vec3 operator+() const { return {x, y, z}; }
		vec3 operator-() const { return {x, -y, z}; }
		vec3 operator+(const vec3 &rhs) const { return {x + rhs.x, y + rhs.y, z + rhs.z}; }
		vec3 operator-(const vec3& rhs) const { return {x - rhs.x, y - rhs.y, z - rhs.z}; }
		vec3 operator*(const vec3& rhs) const { return {x * rhs.x, y * rhs.y, z * rhs.z}; }
		vec3 operator/(const vec3& rhs) const { return {x / rhs.x, y / rhs.y, z / rhs.z}; }

		vec3 operator+(float rhs) const { return {x + rhs, y + rhs, z + rhs}; }
		vec3 operator-(float rhs) const { return {x - rhs, y - rhs, z - rhs}; }
		vec3 operator*(float rhs) const { return {x * rhs, y * rhs, z * rhs}; }
		vec3 operator/(float rhs) const { return {x / rhs, y / rhs, z / rhs}; }

		friend vec3 operator*(float lhs, const vec3& rhs) { return rhs * lhs; }

//		----- COMPOUND ASSIGNMENT -----
		vec3& operator+=(const vec3& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
		vec3& operator-=(const vec3& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }
		vec3& operator*=(const vec3& rhs) {	x *= rhs.x; y *= rhs.y; z *= rhs.z; return *this; }
		vec3& operator/=(const vec3& rhs) { x /= rhs.x; y /= rhs.y; z /= rhs.z; return *this; }

		vec3& operator+=(float rhs) { x += rhs; y += rhs; z += rhs; return *this; }
		vec3& operator-=(float rhs) { x -= rhs; y -= rhs; z -= rhs; return *this; }
		vec3& operator*=(float rhs) { x *= rhs; y *= rhs; z *= rhs; return *this; }
		vec3& operator/=(float rhs) { x /= rhs; y /= rhs; z /= rhs; return *this; }

//		----- INCREMENT / DECREMENT -----
		vec3& operator++() { x++; y++; z++; return *this; } // prefix
		vec3 operator++(int) { return {x++, y++, z++}; } // postfix
		vec3& operator--() { x--; y--; z--; return *this; } // prefix
		vec3 operator--(int) { return {x--, y--, z--}; } // postfix

//		----- COMPARISON OPERATORS -----
		bool operator==(const vec3& rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z; }
		bool operator!=(const vec3& rhs) const { return !operator==(rhs); }
		bool operator<(const vec3& rhs) const { return magnitude() < rhs.magnitude(); }
		bool operator>(const vec3& rhs) const { return magnitude() > rhs.magnitude(); }
		bool operator<=(const vec3& rhs) const { return magnitude() <= rhs.magnitude(); }
		bool operator>=(const vec3& rhs) const { return magnitude() >= rhs.magnitude(); }

//		----- SPECIAL STREAM OPERATORS -----
		friend std::ostream& operator<<(std::ostream& stream, const vec3& vec)
		{
			return stream << '<' << vec.x << ',' << vec.y << ',' << vec.z << '>';
		};
		friend std::istream& operator>>(std::istream& stream, vec3& vec)
		{
			char c = stream.peek();
			if (c == '<')
			{
				char bin;
				stream >> bin >> vec.x >> bin >> vec.y >> bin >> vec.z >> bin;
			}
			else if (std::isdigit(c) || c == '.' || c == '-' || c == '+')
			{
				float scalar;
				stream >> scalar;
				vec = vec3(scalar);
			}
			else
				stream.setstate(std::ios_base::failbit);

			return stream;
		}

//		----- OTHER OPERATORS -----
		bool operator!() const { return magnitude() == 0; }
		explicit operator std::string() const { std::ostringstream os; os << '<' << x << ',' << y << ',' << z << '>'; return os.str(); }
		vec3& operator=(vec3 rhs) { x = rhs.x; y = rhs.y; z = rhs.z; return *this; }
		vec3& operator=(std::string rhs) { std::istringstream is(rhs); is >> *this; return *this; }
	};

	struct vec3::c
	{
		inline static constexpr vec3 up {0,1,0};
		inline static constexpr vec3 down {0,-1,0};
		inline static constexpr vec3 left {-1,0,0};
		inline static constexpr vec3 right {1,0,0};
		inline static constexpr vec3 forward {0,0,1};
		inline static constexpr vec3 backward {0,0,-1};
		inline static constexpr vec3 zero {0,0,0};
		inline static constexpr vec3 one {1,1,1};
		inline static constexpr vec3 identity {1,1,1};
	};
}

#endif //ENGINE_VEC3_H
