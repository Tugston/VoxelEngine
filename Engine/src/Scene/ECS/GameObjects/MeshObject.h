/*
* File: MeshObject.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-12-20 (yyyy/mm/dd)
*
* Description: Entity that automatically sets up a mesh component on it
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

//ENGN
#include "GameObject.h"
#include "../Components/Renders/MeshComponent.h"

namespace Engine::Scene::ECS
{
	enum class MeshType: UINT8
	{
		CUBE_MESH = 0,
		CONE_MESH,
		CYLINDER_MESH,
		SPHERE_MESH,
	};

	class MeshObject : public GameObject3D
	{
	public:
		MeshObject(std::shared_ptr<Scene> scene, MeshType type = MeshType::CUBE_MESH, std::optional<UINT16> sideCount = std::nullopt);
		MeshObject(std::shared_ptr<Scene> scene, std::string_view fileName);

		MeshObject(std::shared_ptr<Scene> scene, Components::TransformComponent3D transform, MeshType type = MeshType::CONE_MESH, std::optional<UINT16> sideCount = std::nullopt);
		MeshObject(std::shared_ptr<Scene> scene, Components::TransformComponent3D transform, std::string_view fileName);
	};
}
