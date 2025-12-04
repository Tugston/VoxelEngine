#include "egpch.h"
#include "Quad.h"

//ENGN
#include "Renderer/Core/RenderCore.h"

namespace Engine::Utility
{
	Mesh CreateQuad()
	{
		Mesh quadMesh;

		std::vector<float> vertexData = {
			 0.5f,  0.5f, 0.f,
			 0.5f, -0.5f, 0.f,
			-0.5f, -0.5f, 0.f,
			-0.5f,  0.5f, 0.f
		};

		std::vector<unsigned int> indexData = {
			0, 1, 3,
			1, 2, 3
		};

		quadMesh.Create();

		quadMesh.vao.Bind();
		quadMesh.vbo.Bind();
		quadMesh.ebo.Bind();

		quadMesh.vbo.BufferData(vertexData, GL_STATIC_DRAW);
		quadMesh.ebo.BufferData(indexData, GL_STATIC_DRAW);

		Renderer::AttribData attribData = { Renderer::ShaderDataType::Float3 };
		quadMesh.vao.SetAttribData(0, attribData, quadMesh.vbo, quadMesh.ebo);

		quadMesh.vao.UnBind();
		quadMesh.vbo.UnBind();
		quadMesh.ebo.UnBind();

		return quadMesh;
	}
}

