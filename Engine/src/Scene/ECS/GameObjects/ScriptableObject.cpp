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
AddComponent<Components::ScriptComponent>(script, this);\
Components::ScriptComponent* scriptComponent = GetComponent<Components::ScriptComponent>();\

namespace Engine::Scene::ECS
{
	ScriptableObject2D::ScriptableObject2D(std::shared_ptr<Scene> scene, std::shared_ptr<ScriptModule> script):
		GameObject2D(scene)
	{
		ADD_SCRIPT();
	}

	ScriptableObject2D::ScriptableObject2D(std::shared_ptr<Scene> scene, std::shared_ptr<ScriptModule> script, Components::TransformComponent2D transform):
		GameObject2D(scene, transform)
	{
		ADD_SCRIPT();
	}

	ScriptableObject3D::ScriptableObject3D(std::shared_ptr<Scene> scene, std::shared_ptr<ScriptModule> script):
		GameObject3D(scene)
	{
		ADD_SCRIPT();
	}

	ScriptableObject3D::ScriptableObject3D(std::shared_ptr<Scene> scene, std::shared_ptr<ScriptModule> script, Components::TransformComponent3D transform):
		GameObject3D(scene, transform)
	{
		ADD_SCRIPT();
	}


	ScriptableSpriteObject2D::ScriptableSpriteObject2D(std::shared_ptr<Scene> scene, std::shared_ptr<ScriptModule> script, SpriteType type):
		SpriteObject2D(scene, type)
	{
		ADD_SCRIPT();
	}

	ScriptableSpriteObject2D::ScriptableSpriteObject2D(std::shared_ptr<Scene> scene, std::shared_ptr<ScriptModule> script, Components::TransformComponent2D transform, SpriteType type):
		SpriteObject2D(scene, transform, type)
	{
		ADD_SCRIPT();
	}

	ScriptableSpriteObject3D::ScriptableSpriteObject3D(std::shared_ptr<Scene> scene, std::shared_ptr<ScriptModule> script, SpriteType type):
		SpriteObject3D(scene, type)
	{
		ADD_SCRIPT();
	}

	ScriptableSpriteObject3D::ScriptableSpriteObject3D(std::shared_ptr<Scene> scene, std::shared_ptr<ScriptModule> script, Components::TransformComponent3D transform, SpriteType type):
		SpriteObject3D(scene, transform, type)
	{
		ADD_SCRIPT();
	}

	ScriptableMeshObject::ScriptableMeshObject(std::shared_ptr<Scene> scene, std::shared_ptr<ScriptModule> script, MeshType type, std::optional<UINT16> sideCount):
		MeshObject(scene, type, sideCount)
	{
		ADD_SCRIPT();
	}

	ScriptableMeshObject::ScriptableMeshObject(std::shared_ptr<Scene> scene, std::shared_ptr<ScriptModule> script, std::string_view fileName):
		MeshObject(scene, fileName)
	{
		ADD_SCRIPT();
	}

	ScriptableMeshObject::ScriptableMeshObject(std::shared_ptr<Scene> scene, std::shared_ptr<ScriptModule> script, Components::TransformComponent3D transform, MeshType type, std::optional<UINT16> sideCount):
		MeshObject(scene, transform, type, sideCount)
	{
		ADD_SCRIPT();
	}

	ScriptableMeshObject::ScriptableMeshObject(std::shared_ptr<Scene> scene, std::shared_ptr<ScriptModule> script, Components::TransformComponent3D transform, std::string_view fileName):
		MeshObject(scene, transform, fileName)
	{
		ADD_SCRIPT();
	}
}

