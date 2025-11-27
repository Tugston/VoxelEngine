#pragma once

//internal math IS NOT exposed to engine api, only internal util
//this is mainly responsible for type conversions between engine math and glm

//VENDOR
#include<glm/glm.hpp>

//ENGN
#include "Math.h"

namespace Engine::Maths
{
	template<typename t>
	glm::vec2 ConvertVec2ToGLM(const Vector2<t>& conversion)
	{
		return glm::vec2<t>(conversion.x, conversion.y);
	}

	template<typename t>
	Vector2<t> ConvertVec2ToMaths(const glm::vec2& conversion)
	{
		return Vector2<t>(static_cast<t>(conversion.x), static_cast<t>(conversion.y));
	}

	template<typename t>
	glm::vec3 ConvertVec3ToGLM(const Vector3<t>& conversion)
	{
		return glm::vec3<t>(conversion.x, conversion.y, conversion.z);
	}

	template<typename t>
	Vector3<t> ConvertVec3ToMaths(const glm::vec3& conversion)
	{
		return Vector3<t>(static_cast<t>(conversion.x), static_cast<t>(conversion.y));
	}
}
