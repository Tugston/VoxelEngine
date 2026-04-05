/*
* File: RenderSystems.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-12-04 (yyyy/mm/dd)
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#include "egpch.h"
#include "RenderSystems.h"

//ENGN
#include "Scene/Scene.h"
#include "Scene/ECS/Registry.h"
#include "Renderer/Core/Renderer.h";

#include "Core/Maths/InternalMath.h"

#include "Scene/ECS/Components/Renders/SpriteComponent.h"
#include "Scene/ECS/Components/Renders/MeshComponent.h"
#include "Scene/ECS/Components/Renders/InstancedMeshComponent.h"
#include "Scene/ECS/Components/Data/TransformComponent.h"

#include "Core/Application.h"

namespace Engine::Scene::ECS::Systems
{

	void SysRenderOpaqueMesh(Scene* scene, Renderer::Renderer* renderer)
	{
		if (!scene)
		{
			LOG_FATAL("<RenderSystems.cpp> (SysRenderOpaqueMesh) Scene is invalid for unknown reason!");
			return;
		}

		const std::vector<EntityID> opaqueObjects = scene->CollectRenderData(Renderer::RenderPasses::Opaque);
		ECS::Registry& reg = scene->GetRegistry();
	
		//not worrying about 2d just yet
		for (size_t i = 0; i < opaqueObjects.size(); i++)
		{	
			auto [mesh, sprite] = reg.GetComponents<Components::MeshComponent, Components::SpriteComponent>(opaqueObjects[i]);
			const Components::TransformComponent3D* transform = reg.GetComponent<Components::TransformComponent3D>(opaqueObjects.at(i));

			if (transform == nullptr)
			{
				LOG_ERROR("<RenderSystems> (SysRenderOpaqueMesh) Transform Component invalid!");
				continue;
			}

			if (sprite)
			{
				sprite->material.shader->Use();
				sprite->material.shader->SetUniformMat4("uProjection", Application::GetCamera()->GetProjectionMatrix());
				sprite->material.shader->SetUniformMat4("uView", Application::GetCamera()->GetViewMatrix());


				glm::mat4 modelMatrix = Maths::Transform3DToModelMatrix(transform->location, transform->rotation, transform->scale);
				Renderer::MeshObject so{ modelMatrix, sprite->planeMesh.get(), &sprite->material }; //sprite object
				renderer->SubmitObject(so);
			}
			
			if (mesh)
			{
				mesh->material.shader->Use();
				mesh->material.shader->SetUniformMat4("uProjection", Application::GetCamera()->GetProjectionMatrix());
				mesh->material.shader->SetUniformMat4("uView", Application::GetCamera()->GetViewMatrix());

				glm::mat4 modelMatrix = Maths::Transform3DToModelMatrix(transform->location, transform->rotation, transform->scale);
				Renderer::MeshObject mo{ modelMatrix, mesh->mesh.get(), &mesh->material }; //mesh object
				renderer->SubmitObject(mo);
			}


		}
		
	}
}

