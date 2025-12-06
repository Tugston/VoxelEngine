/*
* File: InternalMath.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-12-12 (yyyy/mm/dd)
*
* Description: NOT EXPOSED TO ENGINE API, handles type conversions between Maths and GLM
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

//VENDOR
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//ENGN
#include "Core/Core.h"
#include "Math.h"

namespace Engine::Maths
{
	template<typename t>
	glm::vec2 ConvertVec2ToGLM(const Vector2<t>& conversion)
	{
		return glm::vec2(conversion.x, conversion.y);
	}

	template<typename t>
	Vector2<t> ConvertVec2ToMaths(const glm::vec2& conversion)
	{
		return Vector2<t>(static_cast<t>(conversion.x), static_cast<t>(conversion.y));
	}

	template<typename t>
	glm::vec3 ConvertVec3ToGLM(const Vector3<t>& conversion)
	{
		return glm::vec3(conversion.x, conversion.y, conversion.z);
	}

	template<typename t>
	Vector3<t> ConvertVec3ToMaths(const glm::vec3& conversion)
	{
		return Vector3<t>(static_cast<t>(conversion.x), static_cast<t>(conversion.y));
	}

	/*
	m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(0.f, 0.f, -3.f));
			m_ModelMatrix = glm::rotate(m_ModelMatrix, (0 * (EG_PI_FLOAT / 180)), glm::vec3(0.f, 1.f, 0.f));
			m_ModelMatrix = glm::scale(m_ModelMatrix, glm::vec3(1.f, 1.f, 1.f));
	*/

	template<typename t>
	glm::mat4 Transform3DToModelMatrix(const Vector3<t>& location, const Vector3<t>& rotation, const Vector3<t>& scale)
	{
		glm::mat4 modelMatrix = glm::mat4(1.f);
	//	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.f, 0.f, -3.f));
	//	modelMatrix = glm::rotate(modelMatrix, (0 * (EG_PI_FLOAT / 180)), glm::vec3(0.f, 1.f, 0.f));
	//	modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f, 1.f, 1.f));
		modelMatrix = glm::translate(modelMatrix, ConvertVec3ToGLM<t>(location));
		modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3{1.f, 0.f, 0.f});
		modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3{0.f, 1.f, 0.f});
		modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3{0.f, 0.f, 1.f});
		modelMatrix = glm::scale(modelMatrix, ConvertVec3ToGLM<t>(scale));
		return modelMatrix;
	}
}
