/*
* File: ScriptableObject.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-12-22 (yyyy/mm/dd)
*
* Description: Entities that automatically sets up scriptable objects on it
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

//ENGN
#include "MeshObject.h"
#include "SpriteObject.h"
#include "Scene/ECS/Components/Data/ScriptComponent.h"

namespace Engine::Scene::ECS
{
	class ScriptableObject2D : public GameObject2D
	{
	public:
		ScriptableObject2D(std::shared_ptr<Scene> scene, std::shared_ptr<ScriptModule> script);
		ScriptableObject2D(std::shared_ptr<Scene> scene, std::shared_ptr<ScriptModule> script, Components::TransformComponent2D transform);
	};

	class ScriptableObject3D : public GameObject3D
	{
	public:
		ScriptableObject3D(std::shared_ptr<Scene> scene, std::shared_ptr<ScriptModule> script);
		ScriptableObject3D(std::shared_ptr<Scene> scene, std::shared_ptr<ScriptModule> script, Components::TransformComponent3D transform);
	};

	class ScriptableSpriteObject2D : public SpriteObject2D
	{
	public:
		ScriptableSpriteObject2D(std::shared_ptr<Scene> scene, std::shared_ptr<ScriptModule> script, SpriteType type = SpriteType::QUAD_MESH);
		ScriptableSpriteObject2D(std::shared_ptr<Scene> scene, std::shared_ptr<ScriptModule> script, Components::TransformComponent2D transform, SpriteType type = SpriteType::QUAD_MESH);
	};

	class ScriptableSpriteObject3D : public SpriteObject3D
	{
	public:
		ScriptableSpriteObject3D(std::shared_ptr<Scene> scene, std::shared_ptr<ScriptModule> script, SpriteType type = SpriteType::QUAD_MESH);
		ScriptableSpriteObject3D(std::shared_ptr<Scene> scene, std::shared_ptr<ScriptModule> script, Components::TransformComponent3D transform,
			SpriteType type = SpriteType::QUAD_MESH);
	};

	class ScriptableMeshObject : public MeshObject
	{
	public:
		ScriptableMeshObject(std::shared_ptr<Scene> scene, std::shared_ptr<ScriptModule> script, MeshType type = MeshType::CUBE_MESH, std::optional<UINT16> sideCount = std::nullopt);
		ScriptableMeshObject(std::shared_ptr<Scene> scene, std::shared_ptr<ScriptModule> script, std::string_view fileName);

		ScriptableMeshObject(std::shared_ptr<Scene> scene, std::shared_ptr<ScriptModule> script, Components::TransformComponent3D transform, MeshType type = MeshType::CUBE_MESH, std::optional<UINT16> sideCount = std::nullopt);
		ScriptableMeshObject(std::shared_ptr<Scene> scene, std::shared_ptr<ScriptModule> script, Components::TransformComponent3D transform, std::string_view fileName);
	};
}
