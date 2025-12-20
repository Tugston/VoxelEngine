/*
* File: Mesh.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-12-04 (yyyy/mm/dd)
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
	struct MeshComponent
	{
		std::shared_ptr<Utility::Mesh> mesh;
		Utility::Material material;
	};
}
