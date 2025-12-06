/*
* File: DoubleSlot.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-11-22 (yyyy/mm/dd)
*
* Description: Generic imgui wrapper for displaying and modifying double values.
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

//EDTR
#include "BaseSlot.h"


namespace Editor
{
	class DoubleSlot : public BaseSlot
	{
	public:
		DoubleSlot(std::string_view label, double* ref) : BaseSlot(label, ref) {};
		~DoubleSlot() {};

		virtual void Draw() const override {
			float elementWidth = ELEMENT_WIDTH(1.f);
			ImGui::PushItemWidth(elementWidth);
			ImGui::DragScalar(m_Label.data(), ImGuiDataType_Double, static_cast<double*>(m_ValRef), DRAG_SPEED, std::numeric_limits<double*>::lowest(), std::numeric_limits<double*>::max());
			ImGui::PopItemWidth();
		};
	};
}
