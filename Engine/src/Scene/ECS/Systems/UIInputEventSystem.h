/*
* File: UIInputEventSystem.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2026-03-24 (yyyy/mm/dd)
*
* Description: System for handling and consuming all of the input for UI components
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

namespace Engine::Scene
{
	class Scene;
}

namespace Engine::Scene::ECS::Systems
{
	void SysUIInputEvent(const std::shared_ptr<Scene>& scene);
}
