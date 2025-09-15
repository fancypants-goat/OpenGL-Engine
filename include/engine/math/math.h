//
// Created by michiel on 9/14/25.
//

#ifndef ENGINE_MATH_H
#define ENGINE_MATH_H

#include "vec3.h"

namespace engine::math {
	inline float radians(const float degrees)
	{
		static constexpr float d_r_const = M_PI / 180.f;
		return d_r_const * degrees;
	}
	inline float degrees(const float radians)
	{
		static constexpr float r_d_const = 180.f / M_PI;
		return r_d_const * radians;
	}

	inline double radians(const double degrees)
	{
		static constexpr double d_r_const = M_PI / 180;
		return d_r_const * degrees;
	}
	inline double degrees(const double radians)
	{
		static constexpr double r_d_const = 180 / M_PI;
		return r_d_const * radians;
	}


	inline float dot(const vec3& a, const vec3& b)
	{
		return a.dot(b);
	}

	inline vec3 cross(const vec3& a, const vec3& b)
	{
		return a.cross(b);
	}

	inline float angle(const vec3& a, const vec3& b)
	{
		return a.angle(b);
	}

	inline float distance(const vec3& a, const vec3& b)
	{
		return a.distance(b);
	}


}

#endif //ENGINE_MATH_H