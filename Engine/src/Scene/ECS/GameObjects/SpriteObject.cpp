/*
* File: SpriteObject.cpp
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-12-20 (yyyy/mm/dd)
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#include "egpch.h"
#include "SpriteObject.h"

namespace Engine::Scene::ECS
{
	SpriteObject::SpriteObject(std::shared_ptr<Scene> scene): GameObject3D(scene)
	{
		AddComponent<Components::SpriteComponent>();
	}

	SpriteObject::SpriteObject(std::shared_ptr<Scene> scene, Components::SpriteComponent sprite): GameObject3D(scene)
	{
	}

	SpriteObject::SpriteObject(std::shared_ptr<Scene> scene, Components::SpriteComponent sprite, Components::TransformComponent3D transform): GameObject3D(scene, transform)
	{
	}

	SpriteObject::~SpriteObject()
	{
	}
}