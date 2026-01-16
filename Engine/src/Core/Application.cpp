/*
* File: Application.cpp
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-02-17 (yyyy/mm/dd)
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#include "egpch.h"
#include "Application.h"

//ENGINE
#include "Core/Logger.h"
#include "Core/Layers/LayerStack.h"
#include "Core/RandNumGen.h"
#include "Maths/InternalMath.h"
#include "Scene/ECS/Systems/RenderSystems.h"
#include "Scene/ECS/Systems/ScriptSystem.h"

//this cpp file is a mess, and will always be, using the find tool (ctrl-f) is advised

namespace Engine
{
	using namespace Scene::ECS;

	//instantiate static reference
	Application* Application::s_Instance = nullptr;

	Application::Application() :
		m_Window("Voxel Game"), m_CurrentScene(nullptr)
	{
		s_Instance = this;
		InitializeEngineRootSystems();

		m_Renderer = std::make_unique<Renderer::Renderer>(m_Window.GetBufferSize(), Renderer::Renderer::RenderTarget::Window);

		//EVERYTHING PAST THIS POINT SHOULD BE VERIFIED TO BE WORKING

		LOG_WARN("Engine Successfully Started!");
		
		m_Window.SetFrameSize(m_Renderer->Resize(m_Camera.lock().get())); //send the resize function to the window for resize callback
		
		//setup a test level for the engine
		//can obviously be overridden later in the app
		CreateLevel("Test Level");
	}

	Application::~Application()
	{
		glfwTerminate();
		LayerStack::Destroy();
		LOG_MESSAGE("Application Stopped!");
	}

	void Application::Start()
	{		
		Systems::SysOnScriptConstruct(m_CurrentScene);
		Systems::SysOnScriptStart(m_CurrentScene);
	}

	void Application::Tick()
	{
		CalculateDeltaTime();
		ProcessInput();
		InputSystem::MouseIdleDetection(m_DeltaTime);
		InputSystem::SetPreviousMousePos(InputSystem::GetMousePos());

		Systems::SysOnScriptTick(m_CurrentScene, GetDeltaTime());

		m_Window.PollEvents();
		Draw(GetDeltaTime());
	}

	void Application::CreateLevel(std::string_view levelName)
	{
		if (m_CurrentScene)
			m_CurrentScene.reset();

		m_CurrentScene = std::make_unique<Scene::Scene>(Scene::Scene(levelName));
	}

	//need to somehow save scenes and everything else, this is on the back burner for a while
	//just want to get the level structure setup so I can contain everything
	void Application::LoadLevel(std::string_view levelName)
	{
	}

	void Application::Draw(float deltaTime)
	{
		m_Renderer->BeginRender(m_Camera.lock().get());
		Systems::SysRenderOpaqueMesh(m_CurrentScene, m_Renderer.get());
		m_Renderer->EndRender();
		
		SwapBuffer();
	}


	void Application::CalculateDeltaTime()
	{
		float currentTime = (float)glfwGetTime();
		m_DeltaTime = (currentTime - m_PreviousTime); //get delta time
		m_PreviousTime = currentTime;

		static unsigned int CurrentFrames = 0;
		CurrentFrames++;

		static double fpsTimer = currentTime;
		if (currentTime - fpsTimer >= 1)
		{
			m_FrameRate = CurrentFrames;
			CurrentFrames = 0;
			fpsTimer = currentTime;
		}
	}

	void Application::InitializeEngineRootSystems() const
	{
		//terminate the engine if a system failed to initialize
		auto InitializeCheck = [](bool status, std::string_view message)
		{
			if (status)
			{
				Logger::LogMessage(Logger::LogType::Message, std::string(message).append(" Initialized!"));
			}
			else
			{
				Logger::LogMessage(Logger::LogType::Critical, std::string(message).append(" Failed!"));
				EG_ASSERT(false && ": Engine Root Initialization Aborted");
			}
		};

		InitializeCheck(InputSystem::Init(), "Input System");
		InitializeCheck(LayerStack::Init(), "Layer Stack");
		//InitializeCheck(Debug::UI::Init(), "Debug UI");
		InitializeCheck(Utility::InitializeRandomGenerators(), "Random Number Generator");
	}

	void Application::ProcessInput() const
	{
		//engine layers have debug inputs, maybe the game layers need to somehow dispatch input into the layers?? idk
		//probably not though. But for sure this controls debug stuff and what not.
		for (auto layer : LayerStack::GetLayers())
			layer->InputEvent();
	}

}
