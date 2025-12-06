/*
* File: FloatSlot.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-11-22 (yyyy/mm/dd)
*
* Description: Generic imgui wrapper for displaying and modifying float values.
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
	class FloatSlot : public BaseSlot
	{
	public:
		FloatSlot(std::string_view label, float* ref): BaseSlot(label, ref) {};
		~FloatSlot() {};

		virtual void Draw() const override {
			float elementWidth = ELEMENT_WIDTH(1.f);
			ImGui::PushItemWidth(elementWidth);
			ImGui::DragFloat(m_Label.data(), static_cast<float*>(m_ValRef), DRAG_SPEED, std::numeric_limits<float>::lowest(), std::numeric_limits<float>::max());
			ImGui::PopItemWidth();
		};
	};
}
