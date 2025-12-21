/*
* File: Sprite.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-11-26 (yyyy/mm/dd)
*
* Description: Sprite component to be utilized in the game
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

//ENGN
#include "SharedResources/GenericResources/Mesh.h"
#include "SharedResources/GenericResources/Material.h"


namespace Engine::Scene::ECS::Components
{
	struct SpriteComponent
	{
		SpriteComponent() = default;
		SpriteComponent(std::shared_ptr<Utility::Mesh> mesh, Utility::Material mat): planeMesh(mesh), material(mat) {}

		std::shared_ptr<Utility::Mesh> planeMesh;
		Utility::Material material;
	};
}
