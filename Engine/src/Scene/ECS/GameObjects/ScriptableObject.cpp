/*
* File: ScriptableObject.cpp
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-12-23 (yyyy/mm/dd)
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#include "egpch.h"
#include "ScriptableObject.h"

#define ADD_SCRIPT()\
AddComponent<Components::ScriptComponent>(std::move(script), this);\
Components::ScriptComponent* scriptComponent = GetComponent<Components::ScriptComponent>();\

namespace Engine::Scene::ECS
{
	ScriptableObject2D::ScriptableObject2D(ECS::Registry& registry, std::unique_ptr<ScriptModule> script):
		GameObject2D(registry)
	{
		ADD_SCRIPT();
	}

	ScriptableObject2D::ScriptableObject2D(ECS::Registry& registry, std::unique_ptr<ScriptModule> script, Components::TransformComponent2D transform):
		GameObject2D(registry, transform)
	{
		ADD_SCRIPT();
	}

	ScriptableObject3D::ScriptableObject3D(ECS::Registry& registry, std::unique_ptr<ScriptModule> script):
		GameObject3D(registry)
	{
		ADD_SCRIPT();
	}

	ScriptableObject3D::ScriptableObject3D(ECS::Registry& registry, std::unique_ptr<ScriptModule> script, Components::TransformComponent3D transform):
		GameObject3D(registry, transform)
	{
		ADD_SCRIPT();
	}


	ScriptableSpriteObject2D::ScriptableSpriteObject2D(ECS::Registry& registry, std::unique_ptr<ScriptModule> script, SpriteType type):
		SpriteObject2D(registry, type)
	{
		ADD_SCRIPT();

		AddComponent<Components::Renderable>(LayerID::GameWorld, true);
	}

	ScriptableSpriteObject2D::ScriptableSpriteObject2D(ECS::Registry& registry, std::unique_ptr<ScriptModule> script, Components::TransformComponent2D transform, SpriteType type):
		SpriteObject2D(registry, transform, type)
	{
		ADD_SCRIPT();

		AddComponent<Components::Renderable>(LayerID::GameWorld, true);
	}

	ScriptableSpriteObject3D::ScriptableSpriteObject3D(ECS::Registry& registry, std::unique_ptr<ScriptModule> script, SpriteType type):
		SpriteObject3D(registry, type)
	{
		ADD_SCRIPT();

		AddComponent<Components::Renderable>(LayerID::GameWorld, true);
	}

	ScriptableSpriteObject3D::ScriptableSpriteObject3D(ECS::Registry& registry, std::unique_ptr<ScriptModule> script, Components::TransformComponent3D transform, SpriteType type):
		SpriteObject3D(registry, transform, type)
	{
		ADD_SCRIPT();

		AddComponent<Components::Renderable>(LayerID::GameWorld, true);
	}

	ScriptableMeshObject::ScriptableMeshObject(ECS::Registry& registry, std::unique_ptr<ScriptModule> script, MeshType type, std::optional<UINT16> sideCount):
		MeshObject(registry, type, sideCount)
	{
		ADD_SCRIPT();

		AddComponent<Components::Renderable>(LayerID::GameWorld, true);
	}

	ScriptableMeshObject::ScriptableMeshObject(ECS::Registry& registry, std::unique_ptr<ScriptModule> script, std::string_view fileName):
		MeshObject(registry, fileName)
	{
		ADD_SCRIPT();

		AddComponent<Components::Renderable>(LayerID::GameWorld, true);
	}

	ScriptableMeshObject::ScriptableMeshObject(ECS::Registry& registry, std::unique_ptr<ScriptModule> script, Components::TransformComponent3D transform, MeshType type, std::optional<UINT16> sideCount):
		MeshObject(registry, transform, type, sideCount)
	{
		ADD_SCRIPT();

		AddComponent<Components::Renderable>(LayerID::GameWorld, true);
	}

	ScriptableMeshObject::ScriptableMeshObject(ECS::Registry& registry, std::unique_ptr<ScriptModule> script, Components::TransformComponent3D transform, std::string_view fileName):
		MeshObject(registry, transform, fileName)
	{
		ADD_SCRIPT();

		AddComponent<Components::Renderable>(LayerID::GameWorld, true);
	}
}

