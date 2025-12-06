/*
* File: Vector2Slot.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-11-22 (yyyy/mm/dd)
*
* Description: Generic imgui wrapper for displaying and modifying different vector 2 value types.
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
	class Vector2FSlot : public BaseSlot
	{
	public:
		Vector2FSlot(std::string_view label, float* xRef, float* yRef): BaseSlot(label, xRef), m_YRef(yRef) {};
		~Vector2FSlot() {};

		virtual void Draw() const override {
			ImGui::Text(m_Label.data());
			ImGui::SameLine();

			float elementWidth = ELEMENT_WIDTH(2.f);

			ImGui::PushItemWidth(elementWidth);
			ImGui::DragFloat("##x", static_cast<float*>(m_ValRef), DRAG_SPEED, std::numeric_limits<float>::lowest(), std::numeric_limits<float>::max());
			ImGui::SameLine();
			ImGui::PushItemWidth(elementWidth);
			ImGui::DragFloat("##y", static_cast<float*>(m_YRef), DRAG_SPEED, std::numeric_limits<float>::lowest(), std::numeric_limits<float>::max());

			ImGui::PopItemWidth();
			ImGui::PopItemWidth();
		}

	private:
		float* m_YRef = nullptr;
	};

	class Vector2DSlot : public BaseSlot
	{
	public:
		Vector2DSlot(std::string_view label, double* xRef, double* yRef) : BaseSlot(label, xRef), m_YRef(yRef) {};
		~Vector2DSlot() {};

		virtual void Draw() const override {	
			ImGui::Text(m_Label.data());
			ImGui::SameLine();

			float elementWidth = ELEMENT_WIDTH(2.f);

			ImGui::PushItemWidth(elementWidth);
			ImGui::DragScalar("##x", ImGuiDataType_Double, static_cast<double*>(m_ValRef), DRAG_SPEED, std::numeric_limits<double*>::lowest(), std::numeric_limits<double*>::max());
			ImGui::SameLine();
			ImGui::PushItemWidth(elementWidth);
			ImGui::DragScalar("##y", ImGuiDataType_Double, static_cast<double*>(m_YRef), DRAG_SPEED, std::numeric_limits<double*>::lowest(), std::numeric_limits<double*>::max());

			ImGui::PopItemWidth();
			ImGui::PopItemWidth();
		}

	private:
		double* m_YRef = nullptr;
	};
}
