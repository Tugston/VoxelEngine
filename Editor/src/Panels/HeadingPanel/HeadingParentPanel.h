/*
* File: HeadingParentPanel.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2026-01-17 (yyyy/mm/dd)
*
* Description: The information and status bar at the top of editor
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

//STND
#include <string_view>

//EDTR
#include "../../EditorCore.h"

namespace Editor
{
	class HeadingParentPanel
	{
	public:
		HeadingParentPanel(std::string_view appName);
		~HeadingParentPanel();

	private:

	};
}
