//
// Created by michiel on 9/14/25.
//

#ifndef ENGINE_MATH_H
#define ENGINE_MATH_H

#include "vec2.h"
#include "vec3.h"

namespace engine::math {
//	----- UNIT MATH HELPERS -----
	constexpr float radians(const float degrees)
	{
		constexpr float d_r_const = M_PI / 180.f;
		return d_r_const * degrees;
	}
	constexpr float degrees(const float radians)
	{
		constexpr float r_d_const = 180.f / M_PI;
		return r_d_const * radians;
	}

	constexpr double radians(const double degrees)
	{
		constexpr double d_r_const = M_PI / 180;
		return d_r_const * degrees;
	}
	constexpr double degrees(const double radians)
	{
		constexpr double r_d_const = 180 / M_PI;
		return r_d_const * radians;
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