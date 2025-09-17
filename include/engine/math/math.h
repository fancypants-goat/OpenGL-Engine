//
// Created by michiel on 9/14/25.
//

#ifndef ENGINE_MATH_H
#define ENGINE_MATH_H

#include "vec2.h"
#include "vec3.h"

#include <numbers>

namespace engine::math {
//	----- UNIT MATH HELPERS -----
	template <typename T>
	constexpr T radians(T degrees) noexcept {
		return degrees * (std::numbers::pi_v<T> / static_cast<T>(180));
	}

	template <typename T>
	constexpr T degrees(T radians) noexcept {
		return radians * (static_cast<T>(180) / std::numbers::pi_v<T>);
	}


//	----- VECTOR MATH HELPERS -----
	constexpr float dot(const vec3& a, const vec3& b) noexcept
	{
		return a.dot(b);
	}

	constexpr vec3 cross(const vec3& a, const vec3& b) noexcept
	{
		return a.cross(b);
	}

	constexpr float angle(const vec3& a, const vec3& b) noexcept
	{
		return a.angle(b);
	}

	constexpr float distance(const vec3& a, const vec3& b) noexcept
	{
		return a.distance(b);
	}

	constexpr vec3 abs(const vec3& v) noexcept
	{
		return v.abs();
	}


//	----- CONVERTER HELPERS -----
	inline std::string str(const vec2& v) noexcept
	{
		std::ostringstream os;
		os << v;
		return os.str();
	}
	inline std::string str(const vec3& v) noexcept
	{
		std::ostringstream os;
		os << v;
		return os.str();
	}

	inline vec2 strv2(const std::string& s) noexcept
	{
		return vec2::str(s);
	}
	inline vec3 strv3(const std::string& s) noexcept
	{
		return vec3::str(s);
	}

}

#endif //ENGINE_MATH_H