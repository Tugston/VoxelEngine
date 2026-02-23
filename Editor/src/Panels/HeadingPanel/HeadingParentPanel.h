/*
* File: HeadingParentPanel.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2026-01-17 (yyyy/mm/dd)
*
* Description: The information and status bar at the top of editor
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

//STND
#include <functional>
#include <memory>

//ENGN
#include "../BasePanel.h"

namespace Editor
{
	class HeadingParentPanel : public BasePanel
	{
	public:
		HeadingParentPanel(std::string_view appName);
		~HeadingParentPanel();

		virtual void Draw(EditorMode currentMode) const override;

		void SetInputDisplayMask(const UINT8 index);

	private:
		void InputStatusBox(const char* number) const;

	private:
		std::string_view m_ProjectName;
		UINT8 m_InputModeMask = 0x00000001;
	};
}
