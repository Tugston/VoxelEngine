#include "Application.h"

//STND
#include <assert.h>
#include <ranges>

//ENGINE
#include "Core/Logger.h"
#include "Input/Input.h"
#include "Core/Layers/LayerStack.h"

//this cpp file is a mess, and will always be, using the find tool (ctrl-f) is advised

namespace Engine
{
	//instantiate static reference
	Application* Application::s_Instance = nullptr;

	Application::Application() :
		m_Window("Voxel Game")
	{
		s_Instance = this;
		InitializeEngineRootSystems();
	}

	Application::~Application()
	{
		glfwTerminate();
		LayerStack::Destroy();
	}

	void Application::Start()
	{
	}

	void Application::Tick()
	{
		CalculateDeltaTime();
		ProcessInput();

		m_Window.PollEvents();
		Draw(GetDeltaTime());
	}

	void Application::Draw(float deltaTime)
	{
		m_Window.Draw();

		DebugUI::Refresh();

		for (int i = 0; i < LayerStack::GetLayers().size(); i++)
		{
			LayerStack::GetLayers().at(i)->Draw();
		}
	
		DebugUI::Render();
		glfwSwapBuffers(m_Window.GetGLFWWindow());
	//	m_Window.Draw();
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
			m_DeltaTime *= 1000;
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
		InitializeCheck(DebugUI::Init(), "Debug UI");
	}

	void Application::ProcessInput() const
	{
		for (int i = LayerStack::GetLayers().size() - 1; i >= 0; i--)
		{
			LayerStack::GetLayers().at(i)->InputEvent();
		}
	}

	void Application::AddLayer(Layer* newLayer, bool isUI)
	{
		if (isUI)
			LayerStack::PushUILayer(newLayer);
		else
			LayerStack::PushSpaceLayer(newLayer);
	}

}
