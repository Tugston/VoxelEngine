/*
* File: ScriptSystem.cpp
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
#include "ScriptSystem.h"

//STND
#include <vector>

//ENGN
#include "Scene/ECS/GameObjects/ScriptableObject.h";

namespace Engine::Scene::ECS::Systems
{

	void SysOnScriptConstruct(ECS::Registry& registry)
	{
		const std::vector<EntityID>* scriptEntities = registry.GetAllEntitiesWithComponent<Components::ScriptComponent>();

		for (EntityID ent : *scriptEntities)
		{
			Components::ScriptComponent* scriptComp = registry.GetComponent<Components::ScriptComponent>(ent);

			if (scriptComp)
			{
				for (size_t i = 0; i < scriptComp->scripts.size(); i++)
				{
					ScriptModule* script = scriptComp->scripts.at(i).get();

					if(script)
						script->Construct();
				}
			}
		}
	}

	void SysOnScriptStart(ECS::Registry& registry)
	{
		const std::vector<EntityID>* scriptEntities = registry.GetAllEntitiesWithComponent<Components::ScriptComponent>();

		for (EntityID ent : *scriptEntities)
		{
			Components::ScriptComponent* scriptComp = registry.GetComponent<Components::ScriptComponent>(ent);

			if (scriptComp)
			{
				for (size_t i = 0; i < scriptComp->scripts.size(); i++)
				{
					ScriptModule* script = scriptComp->scripts.at(i).get();

					if (script)
						script->Start();
				}
			}
		}
	}

	void SysOnScriptTick(ECS::Registry& registry, float deltaTime)
	{
		const std::vector<EntityID>* scriptEntities = registry.GetAllEntitiesWithComponent<Components::ScriptComponent>();

		for (EntityID ent : *scriptEntities)
		{
			Components::ScriptComponent* scriptComp = registry.GetComponent<Components::ScriptComponent>(ent);

			if (scriptComp && scriptComp->tickEnabled)
			{
				for (size_t i = 0; i < scriptComp->scripts.size(); i++)
				{
					ScriptModule* script = scriptComp->scripts.at(i).get();

					if (script)
						script->Tick(deltaTime);
				}
			}
		}
	}
}

