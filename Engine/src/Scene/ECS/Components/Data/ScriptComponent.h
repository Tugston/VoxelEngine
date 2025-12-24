/*
* File: ScriptComponent.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-12-21 (yyyy/mm/dd)
*
* Description: Component that allows the application to add custom scripts to entities
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

//STND
#include <vector>
#include <memory>

//ENGN
#include "Core/ScriptModule.h"

namespace Engine::Scene::ECS::Components
{

	struct ScriptComponent
	{
		std::vector<std::shared_ptr<ScriptModule>> scripts;
		bool tickEnabled = true;

		//store the owner here as well, so that the component can setup the scripts automatically
		GameObject* owner = nullptr;

		ScriptComponent(std::shared_ptr<ScriptModule> script, GameObject* owner):
			owner(owner)
		{
			AddScript(script);
		}

		//breaking Component architecture here, but its just extrapolating the vector
		void AddScript(std::shared_ptr<ScriptModule> script)
		{
			script.get()->SetOwner(owner);
			scripts.push_back(script);
		}

	};
}
