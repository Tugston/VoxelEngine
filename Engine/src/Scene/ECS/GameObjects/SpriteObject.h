/*
* File: SpriteObject.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-12-20 (yyyy/mm/dd)
*
* Description: Entity that automatically sets up a sprite component on it
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

//ENGN
#include "GameObject.h"
#include "../Components/Renders/SpriteComponent.h"

namespace Engine::Scene::ECS
{
	enum class SpriteType: UINT8
	{
		QUAD_MESH = 0,
		TRIANGLE_MESH
	};

	class SpriteObject2D : public GameObject2D
	{
	public:
		SpriteObject2D(std::shared_ptr<Scene> scene, SpriteType type = SpriteType::QUAD_MESH);
		SpriteObject2D(std::shared_ptr<Scene> scene, Components::TransformComponent2D transform, SpriteType type = SpriteType::QUAD_MESH);
	};

	class SpriteObject3D : public GameObject3D
	{
	public:
		SpriteObject3D(std::shared_ptr<Scene> scene, SpriteType type = SpriteType::QUAD_MESH);
		SpriteObject3D(std::shared_ptr<Scene> scene, Components::TransformComponent3D transform, SpriteType type = SpriteType::QUAD_MESH);
	};
}
