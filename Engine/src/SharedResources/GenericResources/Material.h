/*
* File: Material.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-03-14 (yyyy/mm/dd)
*
* Description: Container for shader and parameter adjustment values that may be present in shader
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

//STND
#include <unordered_map>
#include <string>

//ENGINE
#include "Core/Core.h"
#include "Shader.h"
#include "Texture.h"

namespace Engine::Utility
{
	struct Material
	{
		enum class BlendMode : UINT8 {
			Opaque = 0,
			Masked,
			Transparent
		};

		Shader* shader;
		std::unordered_map<std::string, float> floatParams;
		std::unordered_map<std::string, glm::vec4> colorParams;
		std::unordered_map<std::string, Texture*> textureParams;
		BlendMode blendMode = BlendMode::Opaque;
	};
}
