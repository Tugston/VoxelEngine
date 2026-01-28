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

//ENGN
#include <Core/Cameras/PerspectiveCamera.h>

#define HEADING_HEIGHT	45.f

namespace Editor
{		
	ImGuiViewport* imguiViewport = nullptr;

	EditorApplication::EditorApplication() : m_CurrentMode(EditorMode::PanelFocus), Application("Viper Editor", Engine::Renderer::Renderer::RenderTarget::FrameBufferTexture)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_DockingEnable;
		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_ViewportsEnable;

		const bool success = ImGui_ImplGlfw_InitForOpenGL(Application::GetWindow()->GetGLFWWindow(), true) &&
			ImGui_ImplOpenGL3_Init("#version 410");

		if (success)
			LOG_MSG("Editor Successfully Initialized!");
		else
			LOG_CRIT("Editor Failed to Initialize!");

		//should maybe have some error stuff on this,
		//or at least above the init success stuff, but its not IMGUI related I guess, idk
		SetupWindowStyle();

		std::function<void()> quitClass = []() {QuitGame(); };
		m_HeadingPanel = std::make_unique<HeadingParentPanel>(GetWindowName(), std::make_unique<std::function<void()>>(quitClass));

		m_TestSlot = new FloatSlot("Test Float", &m_TestFloat);
		m_TransformTable = new TransformTable3D<float>(&m_TestTransform, &m_TestTransform, &m_TestTransform);

		m_EditorCamera = std::make_shared<Camera::PerspectiveCamera>(glm::vec3{0.f, 0.f, 0.f});
		SetViewTargetCamera(m_EditorCamera);

		//define the extern window
		imguiViewport = ImGui::GetMainViewport();
	};

	EditorApplication::~EditorApplication()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void EditorApplication::Start()
	{
		Application::Start();
		LOG_MSG("Editor Started!");

		m_TestObject = std::make_unique<GameObject3D>(m_CurrentScene);

		m_TestObject->AddComponent<Components::SpriteComponent>();
		Components::TransformComponent3D* transformComponent = m_TestObject->GetComponent<Components::TransformComponent3D>();
		Components::SpriteComponent* spriteComponent = m_TestObject->GetComponent<Components::SpriteComponent>();
		
		if (spriteComponent)
		{
			spriteComponent->planeMesh = std::make_shared<Utility::Mesh>(Utility::CreateCone());
			spriteComponent->planeMesh->indexCount = 6;
			spriteComponent->material.shader = new Shader("TestShader");
			spriteComponent->material.shader->Create();
		}

		if (transformComponent)
		{
			transformComponent->location = Maths::Vector3{ 0.f, 10.f, 0.f };
			transformComponent->rotation = Maths::Vector3{ 0.f, 0.f, 0.f };
			transformComponent->scale = Maths::Vector3{ 1.f, 1.f, 1.f };
		}

		Tick();
	}

	void EditorApplication::Tick()
	{
		while (m_Running)
		{
			Utility::Material* spriteMaterial = &m_TestObject->GetComponent<Components::SpriteComponent>()->material;

			if (spriteMaterial)
			{
				spriteMaterial->shader->Use();
				//spriteMaterial->shader->SetUniformVec3("uColor", m_Color);
				spriteMaterial->shader->SetUniformMat4("uProjection", m_EditorCamera->GetProjectionMatrix());
				spriteMaterial->shader->SetUniformMat4("uView", m_EditorCamera->GetViewMatrix());
			}
			
			//cycle between modes
			if (InputSystem::KeyTapped(EngineKeys::LCTRL))
				m_CurrentMode = static_cast<EditorMode>(static_cast<UINT8>(m_CurrentMode) + 1);
			else if (InputSystem::KeyTapped(EngineKeys::RCTRL))
				m_CurrentMode = static_cast<EditorMode>(static_cast<UINT8>(m_CurrentMode) - 1);

			CameraControl();

			Draw();
			Application::Tick();
		}
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

	void EditorApplication::Draw()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::DockSpaceOverViewport(1, ImGui::GetMainViewport());
		ImGui::PushStyleColor(ImGuiCol_WindowBg, PANEL_BACKGROUND_COLOR);

		ImGui::Begin("Test Window", nullptr, ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize);
		m_TransformTable->Draw();
		ImGui::End();

		ImGui::PopStyleColor();

		m_HeadingPanel->Draw();

		ImGui::Begin("Viewport");
		ImGui::Image((ImTextureID)this->GetRenderScreenTexture(), ImVec2{ 1280, 720 }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		ImGui::End();
	}

	void EditorApplication::CameraControl()
	{
		if (!(m_CurrentMode == EditorMode::ViewportFocus))
			return;
			
		if (InputSystem::KeyPressed(EngineKeys::RightClick))
			m_EditorCamera->ProcessRotation(InputSystem::GetMouseDelta(), false);

		//may adjust the controls to force right click pressing
		//may be a future change

		Logger::LogMessage(Logger::LogType::Message, "Camera Control Active");

		if (InputSystem::KeyPressed(EngineKeys::W))
			m_EditorCamera->ProcessLocation(EditorCamera::MoveDirection::Forward, GetDeltaTime());

		if (InputSystem::KeyPressed(EngineKeys::S))
			m_EditorCamera->ProcessLocation(EditorCamera::MoveDirection::Backwards, GetDeltaTime());

		if (InputSystem::KeyPressed(EngineKeys::A))
			m_EditorCamera->ProcessLocation(EditorCamera::MoveDirection::Left, GetDeltaTime());

		if (InputSystem::KeyPressed(EngineKeys::D))
			m_EditorCamera->ProcessLocation(EditorCamera::MoveDirection::Right, GetDeltaTime());
	}

	void EditorApplication::SetupWindowStyle()
	{
		const Window* window = GetWindow();
		if (window)
		{
			const Maths::Vector3<uint8_t> color{ 126, 186, 84 };
			window->SetWindowBorderColor(color);
			window->SetWindowHeadingColor(color);
		}
	}

}

