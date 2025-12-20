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
	class SpriteObject : public GameObject3D
	{
	public:
		SpriteObject(std::shared_ptr<Scene> scene);
		SpriteObject(std::shared_ptr<Scene> scene, Components::SpriteComponent sprite);
		SpriteObject(std::shared_ptr<Scene> scene, Components::SpriteComponent sprite, Components::TransformComponent3D transform);
		~SpriteObject();
	};
}
