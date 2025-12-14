/*
* File: Mesh.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-03-26 (yyyy/mm/dd)
*
* Description: Container for array objects, buffers, and special functionalities and data storage for various mesh types
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
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
		Mesh() = default;
		Mesh(const Mesh&) = delete;
		Mesh& operator=(const Mesh&) = delete;

		Mesh(Mesh&& other) noexcept :
			vao(std::move(other.vao)), vbo(std::move(other.vbo)), ebo(std::move(other.ebo)), indexCount(std::move(other.indexCount)),
			primitiveMode(std::move(other.primitiveMode))
		{
		}

		Mesh& operator=(Mesh&& other) noexcept
		{
			vao = std::move(other.vao);
			vbo = std::move(other.vbo);
			ebo = std::move(other.ebo);
			return *this;
		}

		void Create()
		{
			vao.Create();
			vbo.Create();
			ebo.Create();
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
	/*	InstancedMesh(const InstancedMesh& other)
		{
			vao = other.vao;
			vbo = other.vbo;
			ebo = other.ebo;
			indexCount = other.indexCount;
			primitiveMode = other.primitiveMode;
			instanceVBO = other.instanceVBO;
			instances = other.instances;
		} */

		Renderer::IndexBuffer instanceVBO;
		std::vector<glm::mat4> instances;
	};
}
