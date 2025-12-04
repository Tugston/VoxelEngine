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
