/*
* File: EditorMode.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2026-01-31 (yyyy/mm/dd)
*
* Description: Enum responsible for the state of the current input mode across the editor
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once


//ENGN
#include "Engine.h"

namespace Editor
{
	enum class EditorMode : UINT8
	{
		PanelFocus = 0,
		ViewportFocus,
		PanelEdit
	};
}
