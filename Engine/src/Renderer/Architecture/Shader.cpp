#include "egpch.h"
#include "Shader.h"

//STND
#include <fstream>
#include <filesystem>

//ENGINE
#include "Renderer/Core/RenderCore.h"
#include "Core/Logger.h"

//VENDOR
#include "glm/ext.hpp"


namespace Engine::Renderer
{
	Shader::Shader(const std::string& fileName)
	{
		std::string filePath = "./Shaders/" + fileName + ".txt";
		m_FilePath = filePath.c_str();
	}

	Shader::~Shader()
	{
		GL_CHECK(glDeleteProgram(m_Program));
	}

	void Shader::Create()
	{
		std::string vertSrc = ReadSrcFromFile(ShaderType::Vertex);
		std::string fragSrc = ReadSrcFromFile(ShaderType::Fragment);
		//add other shaders later

		unsigned int fragShader = CreateShader(ShaderType::Fragment, fragSrc.c_str());
		unsigned int vertShader = CreateShader(ShaderType::Vertex, vertSrc.c_str());

		CreateProgram(vertShader, fragShader);
	}

	void Shader::Use()
	{
		GL_CHECK(glUseProgram(m_Program));
	}

	void Shader::SetUniformFloat(const std::string& name, const float value)
	{
		Use();
		int location = glGetUniformLocation(m_Program, name.c_str());

		if (location < 0)
		{
			LOG_ERR("<Shader.cpp> Float uniform does not have valid location!");
			return;
		}

		GL_CHECK(glUniform1f(location, value));
	}

	void Shader::SetUniformInt(const std::string& name, const int value)
	{
		Use();
		int location = glGetUniformLocation(m_Program, name.c_str());

		if (location < 0)
		{
			LOG_ERR("<Shader.cpp> Int uniform does not have valid location!");
			return;
		}

		GL_CHECK(glUniform1i(location, value));
	}

	void Shader::SetUniformVec2(const std::string& name, const glm::vec2& value)
	{
		Use();
		int location = glGetUniformLocation(m_Program, name.c_str());

		if (location < 0)
		{
			LOG_ERR("<Shader.cpp> Vec2 uniform does not have valid location!");
			return;
		}

		GL_CHECK(glUniform2fv(location, 1, glm::value_ptr(value)));
	}

	void Shader::SetUniformVec3(const std::string& name, const glm::vec3& value)
	{
		Use();
		int location = glGetUniformLocation(m_Program, name.c_str());

		if (location < 0)
		{
			LOG_ERR("<Shader.cpp> Vec3 uniform does not have valid location!");
			return;
		}

		GL_CHECK(glUniform3fv(location, 1, glm::value_ptr(value)));
	}

	void Shader::SetUniformVec4(const std::string& name, const glm::vec4& value)
	{
		Use();
		int location = glGetUniformLocation(m_Program, name.c_str());

		if (location < 0)
		{
			LOG_ERR("<Shader.cpp> Vec4 uniform does not have valid location!");
			return;
		}

		GL_CHECK(glUniform4fv(location, 1, glm::value_ptr(value)));
	}

	void Shader::SetUniformMat2(const std::string& name, const glm::mat2& value, bool transpose)
	{
		Use();
		int location = glGetUniformLocation(m_Program, name.c_str());

		if (location < 0)
		{
			LOG_ERR("<Shader.cpp> Mat2 uniform does not have valid location!");
			return;
		}

		GL_CHECK(glUniformMatrix4fv(location, 1, transpose, glm::value_ptr(value)));
	}

	void Shader::SetUniformMat3(const std::string& name, const glm::mat3& value, bool transpose)
	{
		Use();
		int location = glGetUniformLocation(m_Program, name.c_str());

		if (location < 0)
		{
			LOG_ERR("<Shader.cpp> Mat3 uniform does not have valid location!");
			return;
		}

		GL_CHECK(glUniformMatrix3fv(location, 1, transpose, glm::value_ptr(value)));
	}

	void Shader::SetUniformMat4(const std::string& name, const glm::mat4& value, bool transpose)
	{
		Use();
		int location = glGetUniformLocation(m_Program, name.c_str());

		if (location < 0)
		{
			LOG_ERR("<Shader.cpp> Mat4 uniform does not have valid location!");
			return;
		}

		glUniformMatrix4fv(location, 1, transpose, glm::value_ptr(value));
	}

	std::string Shader::ReadSrcFromFile(ShaderType type)
	{
		std::fstream fin;
		fin.open(m_FilePath.c_str());

		if (!fin.is_open())
		{
			std::cout << std::filesystem::current_path() << std::endl;
			std::cout << std::filesystem::current_path() << m_FilePath << std::endl;
			LOG_ERR("<Shader.cpp> Shader file could not be opened!");
			return "";
		}

		//find the starting position in the file based on the type
		static std::unordered_map<ShaderType, std::string> tagMap = { {ShaderType::Vertex, "VERT"}, {ShaderType::Fragment, "FRAG"} };

		std::string src = "";
		std::string line = "";
		bool readSection = false;
		while (!fin.eof())
		{
			std::getline(fin, line);
			line += "\n"; //add the newline

			if (readSection)
			{
				//end of the section
				if (line == "###\n")
				{
					fin.close();
					return src;
				}
				
				src += line;
			}

			//put this here so it naturally skips the tag line
			if (line == tagMap.at(type) + "\n")
			{
				readSection = true;
			}
		}
		fin.close();
		return src;
	}

	unsigned int Shader::CreateShader(ShaderType type, const char* src)
	{
		if (!src)
		{
			LOG_ERR("<Shader.cpp> Shader src not valid!");
			return 0;
		}
		
		unsigned int shader = 0;

		//create the appropriate type of shader
		switch (type)
		{
		case Shader::ShaderType::Fragment:
			shader = glCreateShader(GL_FRAGMENT_SHADER);
			break;
		case Shader::ShaderType::Vertex:
			shader = glCreateShader(GL_VERTEX_SHADER);
			break;
		default:
			break;
		}
		
		GL_CHECK(glShaderSource(shader, 1, &src, NULL));
		GL_CHECK(glCompileShader(shader));

		return shader;
	}

	void Shader::CreateProgram(unsigned int& vertProgram, unsigned int& fragProgram)
	{
		m_Program = glCreateProgram();
		GL_CHECK(glAttachShader(m_Program, vertProgram));
		GL_CHECK(glAttachShader(m_Program, fragProgram));
		GL_CHECK(glLinkProgram(m_Program));

		glDeleteShader(vertProgram);
		glDeleteShader(fragProgram);
	}
}
