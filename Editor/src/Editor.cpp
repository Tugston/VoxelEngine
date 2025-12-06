/*
* File: Editor.cpp
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-11-12 (yyyy/mm/dd)
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#include "Editor.h"

#include <Core/Cameras/PerspectiveCamera.h>

namespace Editor
{		
	EditorApplication::EditorApplication()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_DockingEnable;
		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_ViewportsEnable;

		const bool success = ImGui_ImplGlfw_InitForOpenGL(Application::GetWindow()->GetGLFWWindow(), true) &&
			ImGui_ImplOpenGL3_Init("#version 410");


		if (success)
			LOG_MSG("Application Successfully Initialized!");
		else
			LOG_CRIT("Application Not Initialized!");

		m_TestSlot = new FloatSlot("Test Float", &m_TestFloat);
		m_Vec2TestSlot = new Vector2FSlot("2D Position", &m_TestFloat, &m_TestFloat);
		m_Vec3TestSlot = new Vector3DSlot("3D Position",  &m_TestDouble, &m_TestDouble, &m_TestDouble);

		m_Camera = new Camera::PerspectiveCamera();
	};

	EditorApplication::~EditorApplication()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void EditorApplication::Start()
	{
		LOG_MSG("Editor Started!");
		Application::Start();
		Tick();
	}

	void EditorApplication::Tick()
	{
		while (m_Running)
		{
			Draw();
			Application::Tick();
		}
	}

	void EditorApplication::Draw()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::DockSpaceOverViewport(1, ImGui::GetMainViewport());
		
		ImGui::Begin("Test Window", nullptr, ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize);
		m_TestSlot->Draw();
		m_Vec2TestSlot->Draw();
		m_Vec3TestSlot->Draw();
		ImGui::End();
	}
	
	void EditorApplication::SwapBuffer()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		GLFWwindow* backupContext = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backupContext);

		Application::SwapBuffer();
	}
}

