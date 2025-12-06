/*
* File: RenderObjects.cpp
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
#include "RenderObjects.h"

//ENGN
#include "Renderer.h"

namespace Engine::Renderer
{
	//***********
	//MESH OBJECT
	//***********

	void MeshObject::SubmitToRender(Renderer* renderer) const
	{
		renderer->RegisterOpaqueObject(*this);
	}

	void MeshObject::Render() const
	{
		material->shader->Use();
		material->shader->SetUniformMat4("uModel", transform);

		mesh->vao.Bind();
		mesh->vbo.Bind();
		mesh->ebo.Bind();

		glDrawElements(mesh->primitiveMode, mesh->indexCount, GL_UNSIGNED_INT, 0);
	}
	
	//***********
	//MESH OBJECT
	//***********


	//********************
	//Instance Mesh Object
	//********************

	void InstanceMeshObject::SubmitToRender(Renderer* renderer) const
	{
		renderer->RegisterOpaqueObject(*this);
	}

	void InstanceMeshObject::Render() const
	{

	}
	//********************
	//Instance Mesh Object
	//********************

}
