#pragma once

//ENGINE
#include <Core/Core.h>

//STND
#include <string_view>
#include <string>

//VENDOR
#include <glm/glm.hpp>

namespace Engine::Renderer
{
	class Shader
	{
	public:
		Shader(const std::string& fileName);
		~Shader();

		void Create();
		
		void Use();

		//if uniform isnt valid function just returns
		void SetUniformFloat(const std::string& name, const float value);
		void SetUniformInt(const std::string& name, const int value);
		void SetUniformVec2(const std::string& name, const glm::vec2& value);
		void SetUniformVec3(const std::string& name, const glm::vec3& value);
		void SetUniformVec4(const std::string& name, const glm::vec4& value);
		void SetUniformMat2(const std::string& name, const glm::mat2& value, bool transpose = false);
		void SetUniformMat3(const std::string& name, const glm::mat3& value, bool transpose = false);
		void SetUniformMat4(const std::string& name, const glm::mat4& value, bool transpose = false);

	private:
		enum class ShaderType
		{
			Fragment = 0,
			Vertex
		};

	private:
		std::string ReadSrcFromFile(ShaderType type);
		unsigned int CreateShader(ShaderType type, const char* src);
		void CreateProgram(unsigned int& vertShader, unsigned int& fragShader);

		void LogError(const std::string& lineData);
	private:
		unsigned int m_Program = 0;
		std::string m_FilePath = "";
	};
}
