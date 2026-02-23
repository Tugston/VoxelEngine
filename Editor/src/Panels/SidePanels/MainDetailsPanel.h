/*
* File: MainDetailsPanel.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2026-01-29 (yyyy/mm/dd)
*
* Description: Panel that manages all the tables and selectors for the selected entities components
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

#include "../BasePanel.h"


namespace Editor
{
	//*************************************************************
	//THERE MAY ONLY BE ONE MAIN DETAILS PANEL NEXT TO THE VIEWPORT
	//*************************************************************

	template<typename t>
	class TransformTable3D;

	class MainDetailPanel : BasePanel
	{
	private:
		MainDetailPanel() : BasePanel("Details") {};
	public:
		static void Init();
		virtual void Draw(EditorMode currentMode) const override;

	private:
		//need to add a list of the tables needed
		static std::unique_ptr<TransformTable3D<float>> m_TransformTable;
		static Maths::Vector3<float> m_TestVec3;

		static MainDetailPanel* m_Instance;

	public:
		static MainDetailPanel& GetInstance()
		{
			static MainDetailPanel instance;
			return instance;
		}

		MainDetailPanel(const MainDetailPanel&) = delete;
		void operator=(const MainDetailPanel&) = delete;

	};
}
