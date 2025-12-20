/*
* File: HierarchyComponent.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-12-17 (yyyy/mm/dd)
*
* Description: Hierarchy component that every entity has by default. This component is meant to store 
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

//ENGN
#include"Core/Core.h"

//STND
#include<limits>

namespace Engine::Scene::ECS::Components
{

	constexpr UINT32 INVALID_ENTITY = (std::numeric_limits<UINT32>::max)(); //Entity ID

	struct HierarchyComponent
	{
		UINT32 parentEntity		 = INVALID_ENTITY;
		UINT32 firstChildEntity	 = INVALID_ENTITY;
		UINT32 nextSiblingEntity = INVALID_ENTITY;
	};


}
