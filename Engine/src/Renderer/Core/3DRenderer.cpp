#include "egpch.h"
#include "3DRenderer.h"

//ENGINE
#include "Renderer/Core/RenderCore.h"

//just testing opengl for now, and will slowly abstract everything

namespace Engine::Renderer
{
	//temporary shaders
	const char* vertexShaderSrc =
		"#version 410 core\n"
		"layout (location=0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const char* fragmentShaderSrc =
		"#version 410 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.f, 1.f, 1.f, 1.f);\n"
		"}\0";


	Renderer3D::Renderer3D()
	{
	

	}

	Renderer3D::~Renderer3D()
	{
		GL_CHECK(glDeleteVertexArrays(1, &m_Vao));
		GL_CHECK(glDeleteBuffers(1, &m_Vbo));
		GL_CHECK(glDeleteBuffers(1, &m_Ebo));
	}

	void Renderer3D::Setup()
	{
		if (glewInit() != GLEW_OK)
		{
			Logger::LogMessage(Logger::LogType::Critical, "<3DRenderer.h> Glew Did Not Initialize");
			EG_ASSERT(false);
		}

		//setting up shaders

		m_VertShader = glCreateShader(GL_VERTEX_SHADER);
		GL_CHECK(glShaderSource(m_VertShader, 1, &vertexShaderSrc, NULL));
		GL_CHECK(glCompileShader(m_VertShader));

		m_FragShader = glCreateShader(GL_FRAGMENT_SHADER);
		GL_CHECK(glShaderSource(m_FragShader, 1, &fragmentShaderSrc, NULL));
		GL_CHECK(glCompileShader(m_FragShader));

		m_ShaderProgram = glCreateProgram();
		GL_CHECK(glAttachShader(m_ShaderProgram, m_VertShader));
		GL_CHECK(glAttachShader(m_ShaderProgram, m_FragShader));
		GL_CHECK(glLinkProgram(m_ShaderProgram));

		GL_CHECK(glDeleteShader(m_VertShader));
		GL_CHECK(glDeleteShader(m_FragShader));


		//setting up buffers

		GL_CHECK(glGenVertexArrays(1, &m_Vao));

		GL_CHECK(glGenBuffers(1, &m_Vbo));
		GL_CHECK(glGenBuffers(1, &m_Ebo));

		GL_CHECK(glBindVertexArray(m_Vao));

		GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_Vbo));
		GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(m_VertData), m_VertData, GL_STATIC_DRAW));

		GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ebo));
		GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_IndexData), m_IndexData, GL_STATIC_DRAW));

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		//unneccessary to unbind, but just emphasizing it anyways just for a structured setup for organizing all the classes
	//	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
	//	GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	//	GL_CHECK(glBindVertexArray(0));
	}

	void Renderer3D::Render()
	{
		GL_CHECK(glUseProgram(m_ShaderProgram));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}
