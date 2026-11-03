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
#ifndef APP_DEBUG | APP_DIST

/**
* @file InternalMath.h
* @brief Viper's math translation utility functions.
* 
* @details These functions are responsible for converting all available engine math types to glm values. This translation layer is needed for different rendering libraries. Some libs use their coordinate systems differently, and having this translation layer allows the game math to all remain the same. When a different renderer is being used, these functions will adapt properly. As of version 0.0.2 the engine only utilizes OpenGL, but Vulcan may be supported eventually.
* @note This header is not exposed to the engine API whatsoever.
* 
* @author Vincent Pierce
* @date December 12, 2025
*/

//VENDOR
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//ENGN
#include "Core/Core.h"
#include "Math.h"

namespace Viper::Maths
{

	/**
	* @brief Convert a Viper Vector2 to the corresponding glm vec2.
	* @param[in] conversion The Viper Vector2 to be converted.
	* @return A glm vec2 consisting of the conversion's values.
	*/
	template<typename t>
	glm::vec2 ConvertVec2ToGLM(const Vector2<t>& conversion)
	{
		return glm::vec2(conversion.x, conversion.y);
	}

	/**
	* @brief Convert a glm vec2 to the corresponding Viper Vector2.
	* @param[in] conversion The glm vec2 to be converted.
	* @return A Vector2 consisting of the conversion's values.
	*/
	template<typename t>
	Vector2<t> ConvertVec2ToMaths(const glm::vec2& conversion)
	{
		return Vector2<t>(static_cast<t>(conversion.x), static_cast<t>(conversion.y));
	}

	/**
	* @brief Convert a Viper Vector3 to the corresponding glm vec3.
	* @param[in] conversion The Viper Vector3 to be converted.
	* @return A glm vec3 consisting of the conversion's values.
	*/
	template<typename t>
	glm::vec3 ConvertVec3ToGLM(const Vector3<t>& conversion)
	{
		return glm::vec3(conversion.x, conversion.y, conversion.z);
	}

	/**
	* @brief Convert a glm vec3 to a Viper Vector3.
	* @param[in] a glm vec3 to be converted.
	* @return A Vector3 consisting of the conversion's values.
	*/
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

	/**
	* @brief Create a model matrix from a Viper transform.
	* @details Assigns a default glm mat4 model matrix. Translate the model matrix by converting the provided location to glm. Set the rotation by assigning glm rotate on each of the rotation parameter's values. Lastly set the scale value to the model matrix by converting the Vector3 scale to glm vec3, and finalize the full model matrix.
	* 
	* @param[in] location The position of the model matrix to be calculated.
	* @param[in] rotation The rotation of the model matrix to be calculated.
	* @param[in] scale The scale of the model matrix to be calculated.
	* 
	* @return The final matrix which is placed in the world space.
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

#endif
