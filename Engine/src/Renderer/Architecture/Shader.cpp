#include "egpch.h"
#include "Shader.h"

//STND
#include <fstream>
#include <filesystem>

//ENGINE
#include "Renderer/Core/RenderCore.h"

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

	void Shader::SetUniformVec3(const std::string& name, const glm::vec3& value)
	{
		Use();
		int location = glGetUniformLocation(m_Program, name.c_str());

		if (location < 0)
		{
			Logger::LogMessage(Logger::LogType::Warning, "<Shader.cpp> (line 52) Shader does not have a valid location");
		}

		GL_CHECK(glUniform3fv(location, 1, glm::value_ptr(value)));
	}

	std::string Shader::ReadSrcFromFile(ShaderType type)
	{
		std::fstream fin;
		fin.open(m_FilePath.c_str());

		if (!fin.is_open())
		{
			std::cout << std::filesystem::current_path() << std::endl;
			std::cout << std::filesystem::current_path() << m_FilePath << std::endl;
			Logger::LogMessage(Logger::LogType::Error, "Shader File Could Not Be Opened!");
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
			Logger::LogMessage(Logger::LogType::Error, "Shader Src Not Valid!");
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
