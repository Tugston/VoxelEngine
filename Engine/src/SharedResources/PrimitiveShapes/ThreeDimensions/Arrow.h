/*
* File: Arrow.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2026-04-04 (yyyy/mm/dd)
*
* Description: helper function to create an arrow mesh as an engine base primitive
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

//ENGN
#include "SharedResources/GenericResources/Mesh.h"

namespace Engine::Utility
{
	//this is just a container exposed since the arrow has quite a few adjustments
	struct ArrowConstruct {
		int sideCount = 6;
		float baseRadius = 0.5f;
		float coneHeight = 0.8f;
		float stemHeight = 0.5f;
	};

	Mesh CreateArrow(ArrowConstruct construct = {});
}
