/*
* File: GameLayers.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-03-08 (yyyy/mm/dd)
*
* Description: All implementations of layers the final game build will actually interact with
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

/* ************** NOTICE ********************* */
/* THIS IS THE GAME LAYER, DO NOT GET CONFUSED */
/* ************** NOTICE ********************* */

#include "Core/Layers/LayerStack.h"

namespace Engine
{
	class WorldLayer : public Layer
	{
	public:
		WorldLayer();
		~WorldLayer();

		virtual void Attach();
		virtual void Detach();
		virtual void GetDrawData();
		virtual void InputEvent();
	};


	class UILayer : public Layer
	{
	public:
		UILayer();
		~UILayer();

		virtual void Attach();
		virtual void Detach();
		virtual void GetDrawData();
		virtual void InputEvent();
	};
}
