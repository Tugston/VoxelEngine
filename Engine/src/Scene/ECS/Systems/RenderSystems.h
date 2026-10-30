/*
* File: RenderSystems.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-12-04 (yyyy/mm/dd)
*
* Description: Systems for handling all the render pass setups in preparation for the render call 
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

namespace Viper::Renderer
{
	class Renderer;
}

namespace Viper::Scene
{
	class Scene;
}

namespace Viper::Scene::ECS::Systems
{
	//utilizes scene to retrieve the render data
	void SysRenderOpaqueMesh(Scene* scene, Renderer::Renderer* renderer);
}

