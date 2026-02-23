/*
* File: BasePanel.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-01-18 (yyyy/mm/dd)
*
* Description: Base class for all imgui panels
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

//VENDOR
#include "../../VENDOR/imgui/imgui.h"

//STND
#include <string_view>

//EDTR
#include "../EditorCore.h"
#include "../EditorMode.h"

namespace Editor
{
	class BasePanel
	{
	public:
		BasePanel(std::string_view panelName) : m_Name(panelName) {};
		~BasePanel() {};

		virtual void Draw(EditorMode currentMode) const = 0;

		//void AddSection();

	protected:
		std::string_view m_Name;
	};
}
