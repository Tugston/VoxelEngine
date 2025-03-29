#include "egpch.h"
#include "Application.h"

//ENGINE
#include "Core/Logger.h"
#include "Core/Layers/LayerStack.h"

//this cpp file is a mess, and will always be, using the find tool (ctrl-f) is advised

namespace Engine
{
	//instantiate static reference
	Application* Application::s_Instance = nullptr;

	Application::Application() :
		m_Window("Voxel Game"), m_CurrentScene(nullptr)
	{
		s_Instance = this;
		srand(time(NULL));
		InitializeEngineRootSystems();

		m_Renderer = new Renderer::RenderAPI(m_Window.GetBufferSize());
	}

	Application::~Application()
	{
		glfwTerminate();
		LayerStack::Destroy();
		Logger::LogMessage(Logger::LogType::Critical, "Application Stopped!");
	}

	void Application::Start()
	{
		Logger::LogMessage(Logger::LogType::Warning, "Started!");

		m_Renderer->Setup();

		//create a level for the engine to automatically use
		//can obviously be overwrote in the game app
		CreateLevel("Test Level");
	}

	void Application::Tick()
	{
		CalculateDeltaTime();
		ProcessInput();

		m_Window.PollEvents();
		Draw(GetDeltaTime());
	}

	void Application::CreateLevel(const std::string_view& levelName)
	{
		if (m_CurrentScene)
			m_CurrentScene.reset();

		m_CurrentScene = std::make_unique<Scene::Scene>(Scene::Scene(levelName));
	}

	//need to somehow save scenes and everything else, this is on the back burner for a while
	//just want to get the level structure setup so I can contain everything
	void Application::LoadLevel(const std::string_view& levelName)
	{
	}

	void Application::Draw(float deltaTime)
	{
		//previous frame reset
		m_Renderer->Clear();

		m_CurrentScene->CollectRenderData();

		m_Renderer->Render();
			
		m_Window.SwapBuffers();
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
		InitializeCheck(Debug::UI::Init(), "Debug UI");
	}

	void Application::ProcessInput() const
	{
		for (int i = LayerStack::GetLayers().size() - 1; i >= 0; i--)
		{
			LayerStack::GetLayers().at(i)->InputEvent();
		}
	}
}
