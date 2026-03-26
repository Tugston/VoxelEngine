/*
* File: LandscapeComponent.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2026-02-15 (yyyy/mm/dd)
*
* Description: Mesh component to be utilized in the game
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
	struct LandscapeComponent
	{
	public:
		LandscapeComponent() {};
		LandscapeComponent(std::shared_ptr<Utility::Mesh> mesh, Utility::Material material, Utility::Texture2D heightMap) {};

		LandscapeComponent(const LandscapeComponent&) = delete;
		LandscapeComponent& operator=(const LandscapeComponent&) = delete;

		LandscapeComponent(LandscapeComponent&&) noexcept = default;
		LandscapeComponent& operator=(LandscapeComponent&&) noexcept = default;

		std::unique_ptr<Utility::Mesh> mesh;
		Utility::Material material;
		Utility::Texture2D heightMap;

	};
}
