/*
* File: RenderObjects.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-11-26 (yyyy/mm/dd)
*
* Description: Reference storage solely utilized by the renderer in order to process specifically related data and to abstract away from the ECS.
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

//VNDR
#include <glm/glm.hpp>

//ENGN
#include "SharedResources/GenericResources/Mesh.h"
#include "SharedResources/GenericResources/Material.h"

//STND
#include <memory>

namespace Engine::Renderer
{
	class Renderer;

	struct RenderObject {
		RenderObject(unsigned int layer) : layer(layer) {};
		RenderObject(glm::mat4 transform, unsigned int layer): transform(transform), layer(layer) {};
		glm::mat4 transform{};
		const unsigned int layer;

	private:
		virtual void SubmitToRender(Renderer* renderer) const = 0;
		virtual void Render() const = 0;

		friend class Renderer;
	};

	struct MeshObject : public RenderObject
	{
		MeshObject(unsigned int layer) : RenderObject(layer) {};
		MeshObject(glm::mat4 transform, const Utility::Mesh* mesh, const Utility::Material* material, unsigned int layer) :
		RenderObject(transform, layer), mesh(mesh), material(material) {};
		const Utility::Mesh* mesh;
		const Utility::Material* material;
		
	private:
		virtual void SubmitToRender(Renderer* renderer) const override;
		virtual void Render() const override;

		friend class Renderer;
	};

	struct InstanceMeshObject : public RenderObject
	{
		InstanceMeshObject() : RenderObject(0) {};

		//each instance should only have a single actual mesh
		//the instancedMesh stores the 
		static const Utility::InstancedMesh* mesh;

		const Utility::Material* material;

	private:
		virtual void SubmitToRender(Renderer* renderer) const override;
		virtual void Render() const override;

		friend class Renderer;
	};
}
