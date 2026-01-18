/*
* File: TransformTables.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-12-05 (yyyy/mm/dd)
* 
* Description: Adds a full transform panel frame to the imgui window 
* 
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
* 
* See License in root directory for additional details.
*/
#pragma once

//EDTR
#include "../../EditorCore.h"
#include "../../Globals/Slots/Vector2Slot.h"
#include "../../Globals/Slots/Vector3Slot.h"

#include "Engine.h"

namespace Editor
{
	template<typename t>
	struct TableType2;
	template<typename t>
	struct TableType3;

	//Maths vec only deals with floats and doubles
	//so explicit double and float works
	template<>
	struct TableType2<double> { using typeRef = Vector2DSlot; };
	template<>
	struct TableType2<float> { using typeRef = Vector2FSlot; };
	template<>
	struct TableType3<double> { using typeRef = Vector3DSlot; };
	template<>
	struct TableType3<float> { using typeRef = Vector3FSlot; };

	template<typename t>
	class TransformTable3D {
	public:
		TransformTable3D(Maths::Vector3<t>* locRef, Maths::Vector3<t>* rotRef, Maths::Vector3<t>* scaleRef) :
			m_LocationSlot("", &locRef->x, &locRef->y, &locRef->z), m_RotationSlot("", &rotRef->x, &rotRef->y, &rotRef->z), m_ScaleSlot("", &scaleRef->x, &scaleRef->y, &scaleRef->z)
		{

		};

		~TransformTable3D() {};

		void Draw()
		{
			if (ImGui::BeginTable("Transform", 2, ImGuiTableFlags_SizingStretchProp | ImGuiTableFlags_BordersInnerV))
			{
				ImGui::TableSetupColumn("Labels", ImGuiTableColumnFlags_WidthFixed, LABEL_WIDTH);
				ImGui::TableSetupColumn("Content", ImGuiTableColumnFlags_WidthStretch);

				ImGui::TableNextRow();
				ImGui::TableNextColumn();

				ImGui::TextUnformatted("Location");
				ImGui::TableNextColumn();
				m_LocationSlot.Draw();

				ImGui::TableNextRow();
				ImGui::TableNextColumn();

				ImGui::TextUnformatted("Rotation");
				ImGui::TableNextColumn();
				m_RotationSlot.Draw();

				ImGui::TableNextRow();
				ImGui::TableNextColumn();

				ImGui::TextUnformatted("Scale");
				ImGui::TableNextColumn();
				m_ScaleSlot.Draw();

				ImGui::EndTable();
			}
		};

	private:
		using TransformSlot = TableType3<t>::typeRef;
		TransformSlot m_LocationSlot;
		TransformSlot m_RotationSlot;
		TransformSlot m_ScaleSlot;
	};

	template<typename t>
	class TransformTable2D
	{
	public:
		TransformTable2D(Maths::Vector2<t>* transformRef)
		{
		};

		~TransformTable2D() {};

		void Draw()
		{
		};

	private:
		using TransformSlot = TableType2<t>::typeRef;
		TransformSlot m_LocationSlot;
		TransformSlot m_RotationSlot;
		TransformSlot m_ScaleSlot;
		Maths::Vector2<t>* m_TransformRef;
	};
}
