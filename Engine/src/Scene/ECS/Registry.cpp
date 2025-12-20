/*
* File: Registry.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-11-12 (yyyy/mm/dd)
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#include "egpch.h"
#include "Registry.h"

namespace Engine::Scene::ECS
{
	Registry::Registry()
	{

	}

	Registry::~Registry()
	{

	}

	std::vector<Registry::ComponentView> Registry::GetAllEntityComponents(EntityID entity)
	{
		std::vector<ComponentView> list;

		for (auto& [key, pool] : m_Components)
		{
			if (pool->HasComponent(entity))
				list.push_back(ComponentView{key.hash_code(), pool->GetRaw(entity)});
		}

		return list;
	}
}