/*
* File: ScriptSystem.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-12-20 (yyyy/mm/dd)
*
* Description: System for handling all of the entities that have scripts
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

//ENGN
#include "Scene/ECS/Registry.h"

namespace Engine::Scene::ECS::Systems
{
	void SysOnScriptConstruct(ECS::Registry& registry);
	void SysOnScriptStart(ECS::Registry& registry);
	void SysOnScriptTick(ECS::Registry& registry, float deltaTime);
}
