#include "Application.h"

//STND
#include <assert.h>

//VENDOR
#include <glfw/glfw3.h>
#include <glfw/glfw3native.h>

//ENGINE
#include "Core/Logger.h"
#include "Input/Input.h"

Engine::Application::Application() : m_DeltaTime(0.f), m_PreviousTime(0)
{
	InitializeEngineRootSystems();
	GeneralSetup();
}

Engine::Application::~Application()
{
	glfwTerminate();
}

void Engine::Application::Start()
{
}

void Engine::Application::Tick()
{
	CalculateDeltaTime();
}

void Engine::Application::Draw(float deltaTime)
{
	
}

void Engine::Application::CalculateDeltaTime()
{
	uint32_t currentTime = glfwGetTime();
	m_DeltaTime = (currentTime - m_PreviousTime) / 1000.f;
	m_PreviousTime = currentTime;
}

void Engine::Application::InitializeEngineRootSystems() const
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

void Engine::Application::GeneralSetup()
{
	//initialize glfw
	if (!glfwInit())
	{
		Logger::LogMessage(Logger::LogType::Critical, "GLFW Failed To Initialize!");
		assert(true && ": Engine General Setup Aborted");
	}

	m_Window = std::make_unique<Window>("My Window");
}
