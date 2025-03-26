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

		void SetUniformVec3(const std::string& name, const glm::vec3& value);

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

	private:
		unsigned int m_Program = 0;
		std::string m_FilePath = "";
	};
}
