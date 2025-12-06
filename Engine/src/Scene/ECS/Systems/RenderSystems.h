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

namespace Engine::Renderer
{
	class Renderer;
}

namespace Engine::Scene
{
	class Scene;
}

namespace Engine::Scene::ECS::Systems
{
	void SysRenderOpaqueMesh(std::shared_ptr<Scene> scene, Renderer::Renderer* renderer);
}

