#include "Application.h"

//STND
#include <assert.h>

//ENGINE
#include "Core/Logger.h"
#include "Input/Input.h"

namespace Engine
{
	//instantiate static reference
	Application* Application::s_Instance = nullptr;

	Application::Application() :
		m_DeltaTime(0.f), m_PreviousTime(0), m_Window("Voxel Game")
	{
		s_Instance = this;
		InitializeEngineRootSystems();
	}

	Application::~Application()
	{
		glfwTerminate();
	}

	void Application::Start()
	{
	}

	void Application::Tick()
	{
		CalculateDeltaTime();

		if (InputSystem::KeyPressed(EngineKeys::ESC))
		{
			gameIsRunning = false;
		}

		m_Window.PollEvents();
		Draw(GetDeltaTime());
	}

	void Application::Draw(float deltaTime)
	{
		m_Window.Draw();
	}


	void Application::CalculateDeltaTime()
	{
		uint32_t currentTime = glfwGetTime();
		m_DeltaTime = (currentTime - m_PreviousTime) / 1000.f;
		m_PreviousTime = currentTime;
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
	}

}
