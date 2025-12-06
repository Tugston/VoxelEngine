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
	template<double>
	struct TableType2 { using typeRef = Vector2DSlot; };
	template<float>
	struct TableType2 { using typeRef = Vector2FSlot; };
	template<double>
	struct TableType3 { using typeRef = Vector3DSlot; };
	template<float>
	struct TableType3 { using typeRef = Vector3FSlot; };

	template<typename t>
	class TransformTable3D {
	public:
	private:
		TableType3<t> m_LocationSlot;
		TableType3<t> m_RotationSlot;
		TableType3<t> m_ScaleSlot;
		Maths::Vector3<t>* m_TransformRef;
	};

	template<typename t>
	class TransformTable2D
	{


	private:
		TableType2<t> m_LocationSlot;
		TableType2<t> m_RotationSlot;
		TableType2<t> m_ScaleSlot;
		Maths::Vector2<t>* m_TransformRef;
	};
}
