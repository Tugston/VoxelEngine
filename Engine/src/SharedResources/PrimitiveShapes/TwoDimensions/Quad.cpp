/*
* File: Quad.cpp
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-11-26 (yyyy/mm/dd)
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
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
		quadMesh.vbo.BufferData(vertexData, GL_STATIC_DRAW);

		quadMesh.ebo.Bind();
		quadMesh.ebo.BufferData(indexData, GL_STATIC_DRAW);

		Renderer::AttribData attribData = { Renderer::ShaderDataType::Float3 };
		quadMesh.vao.SetAttribData(0, attribData, quadMesh.vbo, quadMesh.ebo);

		quadMesh.vao.UnBind();
		quadMesh.vbo.UnBind();
		quadMesh.ebo.UnBind();

		quadMesh.indexCount = 6;

		return quadMesh;
	}
}

