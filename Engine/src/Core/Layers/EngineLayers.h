/*
* File: EngineLayers.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-03-08 (yyyy/mm/dd)
*
* Description: Debug drawing layers for line traces, stat overlays, etc
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once


/* ************** NOTICE ****************************** */
/* THIS IS THE ENGINE LAYERS, DO NOT GET CONFUSED */
/* THESE ARE USED FOR DEBUGGING AND NOT RLY IN THE DIST */
/* ************** NOTICE ****************************** */

//ENGINE
#include "Core/Layers/Layer.h"

namespace Engine
{
	class EngineWorldLayer : public Layer
	{
	public:
		EngineWorldLayer();
		~EngineWorldLayer();

		virtual void Attach();
		virtual void Detach();

		virtual void GetDrawData();
		virtual void InputEvent();
	
	};

	class EngineUILayer : public Layer
	{
	public:
		EngineUILayer();
		~EngineUILayer();

		virtual void Attach();
		virtual void Detach();

		virtual void GetDrawData();
		virtual void InputEvent();

	private:
		bool m_ShowAllData = false;
		int m_TestInt = 0;
		float m_TestFloat = 0;
	};

}
