#include "Application.h"

//STND
#include <assert.h>

//VENDOR
#include <glfw/glfw3.h>
#include <glfw/glfw3native.h>

//ENGINE
#include "Core/Logger.h"
#include "Input/Input.h"

namespace Engine
{
	//instantiate static reference
	Application* Application::s_Instance = nullptr;

	Application::Application() : m_DeltaTime(0.f), m_PreviousTime(0)
	{
		InitializeEngineRootSystems();
		GeneralSetup();

		s_Instance = this;
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

		glfwPollEvents();
	}

	void Application::Draw(float deltaTime)
	{
		m_Window.get()->Draw();
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
					assert(false && ": Engine Root Initialization Aborted");
				}
			};

		InitializeCheck(Logger::Init(), "Logger");
		InitializeCheck(InputSystem::Init(), "Input System");
	}

	void Application::GeneralSetup()
	{
		//initialize glfw
		if (!glfwInit())
		{
			Logger::LogMessage(Logger::LogType::Critical, "GLFW Failed To Initialize!");
			assert(true && ": Engine General Setup Aborted");
		}

		m_Window = std::make_unique<Window>("My Window");
	}
}
