/*
* File: IntSlot.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-11-22 (yyyy/mm/dd)
*
* Description: Generic imgui wrapper for displaying and modifying integer values.
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
	class IntSlot : public BaseSlot
	{
	public:
		IntSlot(std::string_view label, float* ref): BaseSlot(label, ref) {};
		~IntSlot() {};

		virtual void Draw() const override {
			float elementWidth = ELEMENT_WIDTH(1.f);
			ImGui::PushItemWidth(elementWidth);
			ImGui::DragInt(m_Label.data(), static_cast<int*>(m_ValRef), DRAG_SPEED, std::numeric_limits<int>::lowest(), std::numeric_limits<int>::max());
			ImGui::PopItemWidth();
		};
	};
}
