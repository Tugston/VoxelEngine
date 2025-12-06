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

#include "Scene/ECS/Components/Renders/Sprite.h"
#include "Scene/ECS/Components/Renders/Mesh.h"
#include "Scene/ECS/Components/Renders/InstancedMesh.h"

//scene should always be valid in each system

namespace Engine::Scene::ECS::Systems
{
	void SysRenderOpaqueMesh(const std::shared_ptr<Engine::Scene::Scene> scene, Renderer::Renderer* renderer)
	{
		const std::vector<EntityID>* spriteEntities = scene->GetAllEntitiesWithComponent<Components::SpriteComponent>();

		//not worrying about 2d just yet
		for (size_t i = 0; i < spriteEntities->size(); i++)
		{
			const Components::SpriteComponent* sprite = scene->GetObjectComponent<Components::SpriteComponent>(spriteEntities->at(i));
			const Components::TransformComponent3D* transform = scene->GetObjectComponent<Components::TransformComponent3D>(spriteEntities->at(i));

			if (sprite == nullptr || transform == nullptr)
			{
				LOG_ERROR("<RenderSystems> (SysRenderOpaqueMesh) Sprite or Transform Component invalid!");
				continue;
			}

			glm::mat4 modelMatrix = Maths::Transform3DToModelMatrix(transform->location, transform->rotation, transform->scale);
			
			Renderer::MeshObject mo { modelMatrix, sprite->planeMesh.get(), &sprite->material, 0};
			renderer->SubmitObject(mo);
		}

	}
}

