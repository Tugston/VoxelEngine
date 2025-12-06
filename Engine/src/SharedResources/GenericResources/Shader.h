/*
* File: Shader.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-03-26 (yyyy/mm/dd)
*
* Description: Wrapper class around opengl shader creation, compilation, and id
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

//ENGINE
#include "Core/Core.h"

//STND
#include <string>

//VENDOR
#include <glm/glm.hpp>

namespace Engine::Utility
{
	//if no file path is provided for the shader, the generic engine shader will be used!
	class Shader
	{
	public:
		Shader();
		Shader(const std::string& fileName);
		~Shader();

		void Create();
		
		void Use() const;

		//if uniform isnt valid function just returns
		void SetUniformFloat(const std::string& name, const float value) const;
		void SetUniformInt(const std::string& name, const int value) const;
		void SetUniformVec2(const std::string& name, const glm::vec2& value) const;
		void SetUniformVec3(const std::string& name, const glm::vec3& value) const;
		void SetUniformVec4(const std::string& name, const glm::vec4& value) const;
		void SetUniformMat2(const std::string& name, const glm::mat2& value, bool transpose = false) const;
		void SetUniformMat3(const std::string& name, const glm::mat3& value, bool transpose = false) const;
		void SetUniformMat4(const std::string& name, const glm::mat4& value, bool transpose = false) const;

	private:
		enum class ShaderType: UINT8
		{
			Fragment = 0,
			Vertex
		};

	private:
		std::string ReadSrcFromFile(ShaderType type);
		unsigned int CreateShader(ShaderType type, const char* src);
		void CreateProgram(unsigned int& vertShader, unsigned int& fragShader);

	private:
		unsigned int m_Program = 0;
		std::string m_FilePath = "";
	};
}
