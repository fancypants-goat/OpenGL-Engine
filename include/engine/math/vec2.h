//
// Created by michiel on 9/16/25.
//

#ifndef ENGINE_VEC2_H
#define ENGINE_VEC2_H
#include <cmath>

#include "vec3.h"

namespace engine::math {
	struct vec2
	{
		float x, y;

		const float& width = x, height = y;


		constexpr vec2() : x(0), y(0) {}
		constexpr vec2(float x, float y) : x(x), y(y) {}
		explicit constexpr vec2(float scalar) : x(scalar), y(scalar) {}

//		----- VECTOR MODIFIERS / MEMBERS -----
		[[nodiscard]] constexpr float magnitude() const noexcept
		{
			return std::sqrt(x * x + y * y);
		}

		constexpr vec2& normalize() noexcept
		{
			*this = normalized();
			return *this;
		}

		[[nodiscard]] constexpr vec2 normalized() const noexcept
		{
			return *this / magnitude();
		}

		[[nodiscard]] vec2 abs() const noexcept
		{
			return {std::fabs(x), std::fabs(y)};
		}

//		----- MATH HELPER METHODS -----
		[[nodiscard]] constexpr float dot(const vec2& other) const noexcept
		{
			return x * other.x + y * other.y;
		}

		[[nodiscard]] constexpr float cross(const vec2& other) const noexcept
		{
			return x * other.y - y * other.x;
		}

		[[nodiscard]] constexpr float angle(const vec2& other) const noexcept
		{
			return std::acos(dot(other) / (magnitude() * other.magnitude()));
		}

		[[nodiscard]] constexpr float distance(const vec2& other) const noexcept
		{
			float dx = x - other.x;
			float dy = y - other.y;
			return std::sqrt(dx * dx + dy * dy);
		}

//		----- STATIC MATH HELPERS -----
		static constexpr float dot(const vec2& a, const vec2& b) noexcept {	return a.dot(b); }
		static constexpr float cross(const vec2& a, const vec2& b) noexcept { return a.cross(b); }
		static constexpr float angle(const vec2& a, const vec2& b) noexcept { return a.angle(b); }
		static constexpr float distance(const vec2& a, const vec2& b) noexcept { return a.distance(b); }




//		----- ARITHMETIC OPERATORS -----
		vec2 operator+() const { return {x, y}; }
		vec2 operator-() const { return {-x, -y}; }
		vec2 operator+(const vec2& rhs) const { return {x + rhs.x, y + rhs.y}; }
		vec2 operator-(const vec2& rhs) const { return {x - rhs.x, y - rhs.y}; }
		vec2 operator*(const vec2& rhs) const { return {x * rhs.x, y * rhs.y}; }
		vec2 operator/(const vec2& rhs) const { return {x / rhs.x, y / rhs.y}; }

		vec2 operator+(float rhs) const { return {x + rhs, y + rhs}; }
		vec2 operator-(float rhs) const { return {x - rhs, y - rhs}; }
		vec2 operator*(float rhs) const { return {x * rhs, y * rhs}; }
		vec2 operator/(float rhs) const { return {x / rhs, y / rhs}; }

		friend vec2 operator*(float lhs, const vec2& rhs) { return rhs * lhs; }

//		----- COMPOUND ASSIGNMENT -----
		vec2& operator+=(const vec2& rhs) { x += rhs.x; y += rhs.y; return *this; }
		vec2& operator-=(const vec2& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
		vec2& operator*=(const vec2& rhs) { x *= rhs.x; y *= rhs.y; return *this; }
		vec2& operator/=(const vec2& rhs) { x /= rhs.x; y /= rhs.y; return *this; }

		vec2& operator+=(float rhs) { x += rhs; y += rhs; return *this; }
		vec2& operator-=(float rhs) { x -= rhs; y -= rhs; return *this; }
		vec2& operator*=(float rhs) { x *= rhs; y *= rhs; return *this; }
		vec2& operator/=(float rhs) { x /= rhs; y /= rhs; return *this; }

//		----- INCREMENT / DECREMENT -----
		vec2& operator++() { x++; y++; return *this; }
		vec2 operator++(int) { return {x++, y++}; }
		vec2& operator--() { x--; y--; return *this; }
		vec2 operator--(int) { return {x--, y--}; }

//		----- COMPARISON OPERATORS -----
		bool operator==(const vec2& rhs) const { return x == rhs.x && y == rhs.y; }
		bool operator!=(const vec2& rhs) const { return !operator==(rhs); }
		bool operator<(const vec2& rhs) const { return magnitude() < rhs.magnitude(); }
		bool operator>(const vec2& rhs) const { return magnitude() > rhs.magnitude(); }
		bool operator<=(const vec2& rhs) const { return magnitude() <= rhs.magnitude(); }
		bool operator>=(const vec2& rhs) const { return magnitude() >= rhs.magnitude(); }

//		----- SPECIAL STREAM OPERATORS -----
		friend std::ostream& operator<<(std::ostream& stream, const vec2& vec)
		{
			return stream << '<' << vec.x << ',' << vec.y << '>';
		}
		friend std::istream& operator>>(std::istream& stream, vec2& vec)
		{
			stream >> std::ws;

			char c = stream.peek();
			if (c == '<')
			{
				char bin;
				stream >> bin >> vec.x >> bin >> vec.y >> bin;
			}
			else if (std::isdigit(c) || c == '.' || c == '-' || c == '+')
			{
				float scalar;
				stream >> scalar;
				vec = vec2(scalar);
			}
			else
				stream.setstate(std::ios_base::failbit);

			return stream;
		}

//		----- OTHER OPERATORS -----
		bool operator!() const { return magnitude() == 0; }
		vec2& operator=(vec2 rhs) { x = rhs.x; y = rhs.y; return *this; }
		[[nodiscard]] constexpr glm::vec2 toGLM() const noexcept { return {x, y}; }
		[[nodiscard]] static constexpr vec2 fromGLM(glm::vec2 v) noexcept { return {v.x, v.y}; }

		static std::string str(const vec2 v) noexcept
		{
			std::ostringstream os;
			os << v;
			return os.str();
		}

		static vec2 str(const std::string& s) noexcept
		{
			std::istringstream is(s);
			vec2 v;
			is >> v;
			return v;
		}
	};

	struct vec2const
	{
		static constexpr vec2 up {0,1};
		static constexpr vec2 right {1,0};
		static constexpr vec2 zero {0,0};
		static constexpr vec2 one {1,1};
		static constexpr vec2 identity {1,1};
	};
}

#endif //ENGINE_VEC2_H