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

//scene should always be valid in each system

namespace Engine::Scene::ECS::Systems
{

	void SysRenderOpaqueMesh(const std::shared_ptr<Engine::Scene::Scene>& scene, Renderer::Renderer* renderer)
	{
		const std::vector<EntityID> opaqueObjects = scene->CollectRenderData(Renderer::RenderPasses::Opaque);

		//not worrying about 2d just yet
		for (size_t i = 0; i < opaqueObjects.size(); i++)
		{
			//there is def a better way to do this, but just doing it like this for now
			//its important to note that an entity could have multiple different types of rendering objects
			//const Components::MeshComponent* sprite = scene->GetObjectComponent<Components::MeshComponent>(opaqueObjects.at(i));
			//const Components::MeshComponent* mesh = scene->GetObjectComponent<Components::MeshComponent>(opaqueObjects.at(i));
			
			auto [mesh, sprite] = scene->GetObjectComponents<Components::MeshComponent, Components::SpriteComponent>(opaqueObjects.at(i));

			const Components::TransformComponent3D* transform = scene->GetObjectComponent<Components::TransformComponent3D>(opaqueObjects.at(i));

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

