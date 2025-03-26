#include "egpch.h"
#include "SceneRenderer.h"

//ENGINE
#include "Renderer/Core/RenderCore.h"

//just testing opengl for now, and will slowly abstract everything

namespace Engine::Renderer
{
	SceneRenderer::SceneRenderer() : Renderer()
	{
		//m_TestShader = new Shader("TestShader.txt");
	}

	SceneRenderer::~SceneRenderer()
	{
		//delete m_TestShader;
	}

	void SceneRenderer::Setup()
	{
			
		//m_TestShader->Create();
	

		//setting up buffers
		m_ArrayObject.Bind();
		m_VertexBuffer.BufferData(m_VertData, GL_STATIC_DRAW);
		m_IndexBuffer.BufferData(m_IndexData, GL_STATIC_DRAW);

		m_ArrayObject.AddVertBuffer(std::make_shared<VertexBuffer>(m_VertexBuffer));
		m_ArrayObject.SetIndexBuffer(std::make_shared<IndexBuffer>(m_IndexBuffer));
		m_ArrayObject.SetAttribData(AttribData(ShaderDataType::Float3, GL_FALSE));
	}

	void SceneRenderer::Render()
	{
		//m_TestShader->Use();
		m_ArrayObject.Bind();
		m_VertexBuffer.Bind();
		m_IndexBuffer.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}
