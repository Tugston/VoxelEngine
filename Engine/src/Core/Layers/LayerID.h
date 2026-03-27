/*
* File: LayerID.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2026-03-26 (yyyy/mm/dd)
*
* Description: Global type for the layer id's since it is required in components
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

#include "Core/Core.h"

namespace Engine
{
	enum class LayerID: UINT8 {
		Unknown		= 0,	//error state (although, I don't really have an implementation for it, just used for initialization)
		EngineWorld = 1,
		EngineUI	= 2,
		GameWorld	= 3,
		GameUI		= 4
	};
}
