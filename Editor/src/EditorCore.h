/*
* File: EditorCore.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-11-22 (yyyy/mm/dd)
*
* Description: Core utility that is useful throughout the entire editor. Not required to include in every file.
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

//STND
#include<algorithm>

//VENDOR
#include "../VENDOR/imgui/imgui.h"

#define DRAG_SPEED 0.75f
#define LABEL_WIDTH 75.f

#define ELEMENT_WIDTH(n) std::clamp((ImGui::GetContentRegionAvail().x - ImGui::GetStyle().ItemSpacing.x * 2.f) / n, -1.f, 70.f)

#define PANEL_BACKGROUND_COLOR	ImVec4{ 60.f / 255.f, 120.f / 255.f, 18.f / 255.f, 1.f }
#define PANEL_SEPERATOR_COLOR	ImVec4{0.f, 0.f, 0.f, 1.f}

namespace Editor
{
	extern ImGuiViewport* imguiViewport;
}
