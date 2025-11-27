#pragma once

//ENGINE
#include "Core/Core.h"
#include "Renderer/Architecture/Buffer.h"
#include "Renderer/Architecture/ArrayObject.h"

//VNDR
#include <glm/glm.hpp>

namespace Engine::Utility
{
	struct Mesh
	{
		Mesh() {};
		Mesh(const Mesh& other)
		{
			vao = other.vao;
			vbo = other.vbo;
			ebo = other.ebo;
			indexCount = other.indexCount;
			primitiveMode = other.primitiveMode;
		}

		Renderer::ArrayObject vao;
		Renderer::VertexBuffer vbo;
		Renderer::IndexBuffer ebo;

		UINT32 indexCount = 0; //amount of total indexes
		UINT32 primitiveMode = 0x0004; //GL_TRIANGLES
	};

	struct InstancedMesh : public Mesh
	{
		InstancedMesh() {};
		InstancedMesh(const InstancedMesh& other)
		{
			vao = other.vao;
			vbo = other.vbo;
			ebo = other.ebo;
			indexCount = other.indexCount;
			primitiveMode = other.primitiveMode;
			instanceVBO = other.instanceVBO;
			instances = other.instances;
		}

		Renderer::IndexBuffer instanceVBO;
		std::vector<glm::mat4> instances;
	};
}
