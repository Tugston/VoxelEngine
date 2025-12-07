/*
* File: Vector3Slot.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-11-22 (yyyy/mm/dd)
*
* Description: Generic imgui wrapper for displaying and modifying different vector 3 value types.
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
	class Vector3FSlot : public BaseSlot
	{
	public:
		Vector3FSlot(std::string_view label, float* xRef, float* yRef, float* zRef): BaseSlot(label, xRef), m_YRef(yRef), m_ZRef(zRef) {};
		~Vector3FSlot() {};

		virtual void Draw() const override {

			if (m_Label.size() > 0)
			{
				ImGui::Text(m_Label.data());
				ImGui::SameLine();
			}

			float elementWidth = ELEMENT_WIDTH(4.f);

			//prevents conflicts between vector3's
			ImGui::PushID(this);

			ImGui::PushItemWidth(elementWidth);
			ImGui::TextColored({ 1.f, 0.f, 0.f, 1.f }, "X");
			ImGui::SameLine();
			ImGui::DragFloat("##x", static_cast<float*>(m_ValRef), DRAG_SPEED, std::numeric_limits<float>::lowest(), std::numeric_limits<float>::max());
			
			ImGui::SameLine();
			ImGui::PushItemWidth(elementWidth);
			ImGui::TextColored({ 0.f, 1.f, 0.f, 1.f }, "Y");
			ImGui::SameLine();
			ImGui::DragFloat("##y", static_cast<float*>(m_YRef), DRAG_SPEED, std::numeric_limits<float>::lowest(), std::numeric_limits<float>::max());
			
			ImGui::SameLine();
			ImGui::PushItemWidth(elementWidth);
			ImGui::TextColored({ 0.f, 0.f, 1.f, 1.f }, "Z");
			ImGui::SameLine();
			ImGui::DragFloat("##z", static_cast<float*>(m_ZRef), DRAG_SPEED, std::numeric_limits<float>::lowest(), std::numeric_limits<float>::max());

			ImGui::PopItemWidth();
			ImGui::PopItemWidth();
			ImGui::PopItemWidth();

			ImGui::PopID();
		}

	private:
		float* m_YRef = nullptr;
		float* m_ZRef = nullptr;
	};

	class Vector3DSlot : public BaseSlot
	{
	public:
		Vector3DSlot(std::string_view label, double* xRef, double* yRef, double* zRef) : BaseSlot(label, xRef), m_YRef(yRef), m_ZRef(zRef) {};
		~Vector3DSlot() {};

		virtual void Draw() const override {	
			ImGui::Text(m_Label.data());
			ImGui::SameLine();

			float elementWidth = ELEMENT_WIDTH(3.f);

			//prevents conflicts between vector3's
			ImGui::PushID(this);

			ImGui::PushItemWidth(elementWidth);
			ImGui::DragScalar("X##x", ImGuiDataType_Double, static_cast<double*>(m_ValRef), DRAG_SPEED, std::numeric_limits<double*>::lowest(), std::numeric_limits<double*>::max());
			ImGui::SameLine();
			ImGui::PushItemWidth(elementWidth);
			ImGui::DragScalar("Y##y", ImGuiDataType_Double, static_cast<double*>(m_YRef), DRAG_SPEED, std::numeric_limits<double*>::lowest(), std::numeric_limits<double*>::max());
			ImGui::SameLine();
			ImGui::PushItemWidth(elementWidth);
			ImGui::DragScalar("Z##z", ImGuiDataType_Double, static_cast<double*>(m_ZRef), DRAG_SPEED, std::numeric_limits<double*>::lowest(), std::numeric_limits<double*>::max());

			ImGui::PopItemWidth();
			ImGui::PopItemWidth();
			ImGui::PopItemWidth();

			ImGui::PopID();
		}

	private:
		double* m_YRef = nullptr;
		double* m_ZRef = nullptr;
	};
}
