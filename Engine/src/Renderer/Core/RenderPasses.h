/*
* File: Renderer.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2026-03-26 (yyyy/mm/dd)
*
* Description: Pipline that handles every single vertex, render pass, lighting calculation, or whatever required to draw the scene
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

#include <Core/Core.h>

//the scene needs a render type as well,
//there may even be more in the future so providing a common type
namespace Engine::Renderer
{
	enum class RenderPasses: UINT8
	{
		Opaque,
		Translucent
	};
}
