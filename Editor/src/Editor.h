/*
* File: Editor.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-11-12 (yyyy/mm/dd)
*
* Description: Main driver application for the editor to route all systems.
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

//EDITOR
#include "EditorCore.h"
#include "EditorMode.h"
#include "Panels/HeadingPanel/HeadingParentPanel.h"
#include "Globals/Slots/FloatSlot.h"
#include "Globals/Slots/Vector2Slot.h"
#include "Globals/Slots/Vector3Slot.h"
#include "Globals/Tables/TransformTables.h"
#include "Panels/SidePanels/MainDetailsPanel.h"

//ENGINE
#include <Core/EntryPoint.h>

//VENDOR
#include "../VENDOR/imgui/imgui.h"
#include "../VENDOR/imgui/imgui_impl_opengl3.h"
#include "../VENDOR/imgui/imgui_impl_glfw.h"

class GLFWWindow;
class Camera::PerspectiveCamera;

namespace Editor
{
	class FloatSlot;

	class EditorApplication : public Application
	{
	public:
		EditorApplication();
		~EditorApplication();	

		virtual void Start() override;
		virtual void Tick() override;
		virtual void SwapBuffer() override;

	private:
		//this draw is obviously not override, so no correlation to the engine's drawing
		//its just a container for imgui drawing
		void Draw();

		void CameraControl();

		void SetupWindowStyle();


	private:	
		void UpdateInputMode(EditorMode newMode);

	private:
		FloatSlot* m_TestSlot;
	

		std::unique_ptr<HeadingParentPanel> m_HeadingPanel;
		
		//not test
		std::shared_ptr<Camera::PerspectiveCamera> m_EditorCamera;
		EditorMode m_CurrentMode;

		MainDetailPanel& m_MainPanelInstance = MainDetailPanel::GetInstance();
		//not test

		std::unique_ptr<GameObject3D> m_TestObject;

		float m_TestFloat = 2.f;
		double m_TestDouble = 3.0;
		Maths::Vector3<float> m_TestTransform;


	};
}

Application* Engine::CreateApplication()
{
	LOG_MSG("Editor Application Created");
	return new Editor::EditorApplication;
}
